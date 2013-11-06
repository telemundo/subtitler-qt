/* CCExtractor, cfsmp3 at gmail
Credits: See CHANGES.TXT
License: GPL 2.0
*/
#include <stdio.h>
#include "ccextractor.h"
#include <sys/types.h>
#include <sys/stat.h>

void xds_cea608_test();

extern unsigned char *filebuffer;
extern int bytesinbuffer; // Number of bytes we actually have on buffer

// PTS timing related stuff
LLONG min_pts, max_pts, sync_pts;
LLONG fts_now; // Time stamp of current file (w/ fts_offset, w/o fts_global)
LLONG fts_offset; // Time before first sync_pts
LLONG fts_fc_offset; // Time before first GOP
LLONG fts_max; // Remember the maximum fts that we saw in current file
LLONG fts_global=0; // Duration of previous files (-ve mode), see c1global

// global TS PCR value, moved from telxcc. TODO: Rename, see if how to relates to fts_global
uint32_t global_timestamp = 0, min_global_timestamp=0;
int global_timestamp_inited=0;

// Count 608 (per field) and 708 blocks since last set_fts() call
int cb_field1, cb_field2, cb_708;
int saw_caption_block;

int pts_set; //0 = No, 1 = received, 2 = min_pts set

unsigned pts_big_change;

int MPEG_CLOCK_FREQ = 90000; // This "constant" is part of the standard

// Stuff common to both loops
unsigned char *buffer = NULL;
LLONG past; /* Position in file, if in sync same as ftell()  */
unsigned char *pesheaderbuf = NULL;
LLONG inputsize;
LLONG total_inputsize=0, total_past=0; // Only in binary concat mode

int last_reported_progress;
int processed_enough; // If 1, we have enough lines, time, etc. 

int live_stream=0; /* -1 -> Not a complete file but a live stream, without timeout
                       0 -> A regular file 
                      >0 -> Live stream with a timeout of this value in seconds */
 
// Small buffer to help us with the initial sync
unsigned char startbytes[STARTBYTESLENGTH]; 
unsigned int startbytes_pos;
int startbytes_avail;

/* Stats */
int stat_numuserheaders;
int stat_dvdccheaders;
int stat_scte20ccheaders;
int stat_replay5000headers;
int stat_replay4000headers;
int stat_dishheaders;
int stat_hdtv;
int stat_divicom;
unsigned total_frames_count;
unsigned total_pulldownfields;
unsigned total_pulldownframes;
int cc_stats[4];
int false_pict_header;
int resets_708=0;

/* GOP-based timing */
struct gop_time_code gop_time, first_gop_time, printed_gop;
int saw_gop_header=0;
int frames_since_last_gop=0;
LLONG fts_at_gop_start=0;

/* Time info for timed-transcript */
LLONG ts_start_of_xds=-1; // Time at which we switched to XDS mode, =-1 hasn't happened yet
int timestamps_on_transcript=0; /* Write time info on transcripts? */
uint64_t utc_refvalue=UINT64_MAX;  /* _UI64_MAX means don't use UNIX, 0 = use current system time as reference, +1 use a specific reference */

int max_gop_length=0; // (Maximum) length of a group of pictures
int last_gop_length=0; // Length of the previous group of pictures
int frames_since_ref_time=0;

int gop_rollover=0;
// int hex_mode=HEX_NONE; // Are we processing an hex file?

/* Detect gaps in caption stream - only used for dvr-ms/NTSC. */
int CaptionGap=0;

/* Parameters */
#ifdef _WIN32
int buffer_input = 1; // In Windows buffering seems to help
#else
int buffer_input = 0; // In linux, not so much.
#endif
stream_mode_enum stream_mode = SM_ELEMENTARY_OR_NOT_FOUND; // Data parse mode: 0=elementary, 1=transport, 2=program stream, 3=ASF container
stream_mode_enum auto_stream = SM_AUTODETECT;
int use_gop_as_pts = 0; // Use GOP instead of PTS timing (0=do as needed, 1=always, -1=never)
int fix_padding = 0; // Replace 0000 with 8080 in HDTV (needed for some cards)
int rawmode = 0; // Broadcast or DVD
// See -d from http://www.geocities.com/mcpoodle43/SCC_TOOLS/DOCS/SCC_TOOLS.HTML#CCExtract
int extract = 1; // Extract 1st, 2nd or both fields
int cc_channel = 1; // Channel we want to dump in srt mode
LLONG debug_mask=DMT_GENERIC_NOTICES; // dbg_print will use this mask to print or ignore different types
LLONG debug_mask_on_debug=0; // If we're using temp_debug to enable/disable debug "live", this is the mask when temp_debug=1
int investigate_packets = 0; // Look for captions in all packets when everything else fails
int messages_target=1; // 0 = nowhere (quiet), 1=stdout, 2=stderr
int cc_to_stdout=0; // If 1, captions go to stdout instead of file
int nosync=0; // Disable syncing
int fullbin=0; // Disable pruning of padding cc blocks
LLONG subs_delay=0; // ms to delay (or advance) subs
int trim_subs=0; // "    Remove spaces at sides?    "
struct boundary_time extraction_start, extraction_end; // Segment we actually process
struct boundary_time startcreditsnotbefore, startcreditsnotafter; // Where to insert start credits, if possible
struct boundary_time startcreditsforatleast, startcreditsforatmost; // How long to display them?
struct boundary_time endcreditsforatleast, endcreditsforatmost;
int startcredits_displayed=0, end_credits_displayed=0;
LLONG last_displayed_subs_ms=0; // When did the last subs end?
LLONG screens_to_process=-1; // How many screenfuls we want?
char *basefilename=NULL; // Input filename without the extension
char **inputfile=NULL; // List of files to process
int export_xds=0; // Export XDS to transcript?
int line_terminator_lf=0; // 0 = CRLF, 1=LF
int noautotimeref=0; // Do NOT set time automatically?
int autodash=0; // Add dashes (-) before each speaker automatically?

datasource input_source=DS_FILE; // Files, stdin or network
const char *extension; // Output extension
int current_file=-1; // If current_file!=1, we are processing *inputfile[current_file]
int direct_rollup=0; // Write roll-up captions directly instead of line by line?
int num_input_files=0; // How many?
int do_cea708=0; // Process 708 data?
int cea708services[63]; // [] -> 1 for services to be processed

int nofontcolor=0; // 1 = don't put <font color> tags 
int notypesetting=0; // 1 = Don't put <i>, <u>, etc typesetting tags
output_format write_format=OF_SRT; // 0=Raw, 1=srt, 2=SMI
output_date_format date_format=ODF_NONE; 
encoding_type encoding = ENC_UTF_8;
int usepicorder = 0; // Force the use of pic_order_cnt_lsb in AVC/H.264 data streams
int auto_myth = 2; // Use myth-tv mpeg code? 0=no, 1=yes, 2=auto
int wtvconvertfix = 0; // Fix broken Windows 7 conversion
int sentence_cap =0 ; // FIX CASE? = Fix case?
char *sentence_cap_file=NULL; // Extra words file?
int binary_concat=1; // Disabled by -ve or --videoedited
int norollup=0; // If 1, write one line at a time
int forced_ru=0; // 0=Disabled, 1, 2 or 3=max lines in roll-up mode
int gui_mode_reports=0; // If 1, output in stderr progress updates so the GUI can grab them
int no_progress_bar=0; // If 1, suppress the output of the progress to stdout
char *output_filename=NULL;
char *out_elementarystream_filename=NULL;
unsigned ts_forced_program=0; // Specific program to process in TS files, if ts_forced_program_selected==1
unsigned ts_forced_program_selected=0; 
unsigned ucla_settings=0; // Enables convenient settings for UCLA's project.
char millis_separator=',';

// Case arrays
char **spell_lower=NULL;
char **spell_correct=NULL;
int spell_words=0;
int spell_capacity=0;

/* Credit stuff */
char *start_credits_text=NULL;
char *end_credits_text=NULL;

/* Hauppauge support */
unsigned hauppauge_warning_shown=0; // Did we detect a possible Hauppauge capture and told the user already?
unsigned hauppauge_mode=0; // If 1, use PID=1003, process specially and so on
unsigned teletext_warning_shown=0; // Did we detect a possible PAL (with teletext subs) and told the user already?
unsigned telext_mode=TXT_AUTO_NOT_YET_FOUND; // 0=Disabled, 1 = Not found, 2=Found

/* Levenshtein's parameters, for string comparison */
int levdistmincnt=2, levdistmaxpct=10; // Means 2 fails or less is "the same", 10% or less is also "the same"	

/* Networking */
in_addr_t udpaddr = 0;
unsigned udpport=0; // Non-zero => Listen for UDP packets on this port, no files.
struct sockaddr_in servaddr, cliaddr; 

/* MP4 related stuff */
unsigned mp4vidtrack=0; // Process the video track even if a CC dedicated track exists.

struct s_write wbout1, wbout2; // Output structures
struct s_write *wbxdsout=NULL; // Pointer, so it can share the same output file 

/* File handles */
FILE *fh_out_elementarystream;
int infd=-1; // descriptor number to input. Set to -1 to indicate no file is open.
char *basefilename_for_stdin=(char *) "stdin"; // Default name for output files if input is stdin
char *basefilename_for_network=(char *) "network"; // Default name for output files if input is network
int PIDs_seen[65536];
struct PMT_entry *PIDs_programs[65536];

int temp_debug=0; // This is a convenience variable used to enable/disable debug on variable conditions. Find references to understand.

int main_telxcc (int argc, char *argv[]);
LLONG process_raw_with_field (void);
