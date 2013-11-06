QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Subtitler
VERSION  = 2.0
TEMPLATE = app

# Application icons
mac:ICON = subtitler.icns
win32:RC_FILE = subtitler.rc

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS   += mainwindow.ui

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Include the ccextractor library
SOURCES += lib/ccextractor/608.cpp \
           lib/ccextractor/608_helpers.cpp \
           lib/ccextractor/608_sami.cpp \
           lib/ccextractor/608_smptett.cpp \
           lib/ccextractor/608_srt.cpp \
           lib/ccextractor/708.cpp \
           lib/ccextractor/708_encoding.cpp \
           lib/ccextractor/activity.cpp \
           lib/ccextractor/asf_functions.cpp \
           lib/ccextractor/avc_functions.cpp \
           lib/ccextractor/cc_bitstream.cpp \
           lib/ccextractor/cc_decoders_common.cpp \
           lib/ccextractor/ccextractor.cpp \
           lib/ccextractor/constants.cpp \
           lib/ccextractor/encoding.cpp \
           lib/ccextractor/es_functions.cpp \
           lib/ccextractor/es_userdata.cpp \
           lib/ccextractor/file_functions.cpp \
           lib/ccextractor/general_loop.cpp \
           lib/ccextractor/gpacmp4/mp4.cpp \
           lib/ccextractor/myth.cpp \
           lib/ccextractor/output.cpp \
           lib/ccextractor/params.cpp \
           lib/ccextractor/params_dump.cpp \
           lib/ccextractor/sequencing.cpp \
           lib/ccextractor/stream_functions.cpp \
           lib/ccextractor/telxcc.cpp \
           lib/ccextractor/timing.cpp \
           lib/ccextractor/ts_functions.cpp \
           lib/ccextractor/utility.cpp \
           lib/ccextractor/xds.cpp

HEADERS += lib/ccextractor/608.h \
           lib/ccextractor/708.h \
           lib/ccextractor/bitstream.h \
           lib/ccextractor/ccextractor.h \
           lib/ccextractor/disable_warnings.h \
           lib/ccextractor/hamming.h \
           lib/ccextractor/inttypes.h \
           lib/ccextractor/stdint.h \
           lib/ccextractor/stdintmsc.h \
           lib/ccextractor/teletext.h

mac {
    INCLUDEPATH += "lib/ccextractor/gpacmp4/"

    SOURCES += lib/ccextractor/gpacmp4/av_parsers.c \
               lib/ccextractor/gpacmp4/avc_ext.c \
               lib/ccextractor/gpacmp4/avilib.c \
               lib/ccextractor/gpacmp4/base_encoding.c \
               lib/ccextractor/gpacmp4/bitstream.c \
               lib/ccextractor/gpacmp4/box_code_3gpp.c \
               lib/ccextractor/gpacmp4/box_code_apple.c \
               lib/ccextractor/gpacmp4/box_code_base.c \
               lib/ccextractor/gpacmp4/box_code_isma.c \
               lib/ccextractor/gpacmp4/box_code_meta.c \
               lib/ccextractor/gpacmp4/box_funcs.c \
               lib/ccextractor/gpacmp4/data_map.c \
               lib/ccextractor/gpacmp4/desc_private.c \
               lib/ccextractor/gpacmp4/descriptors.c \
               lib/ccextractor/gpacmp4/error.c \
               lib/ccextractor/gpacmp4/gpac_ogg.c \
               lib/ccextractor/gpacmp4/hinting.c \
               lib/ccextractor/gpacmp4/ipmpx_code.c \
               lib/ccextractor/gpacmp4/ipmpx_parse.c \
               lib/ccextractor/gpacmp4/isom_intern.c \
               lib/ccextractor/gpacmp4/isom_read.c \
               lib/ccextractor/gpacmp4/isom_store.c \
               lib/ccextractor/gpacmp4/isom_write.c \
               lib/ccextractor/gpacmp4/list.c \
               lib/ccextractor/gpacmp4/media.c \
               lib/ccextractor/gpacmp4/media_odf.c \
               lib/ccextractor/gpacmp4/meta.c \
               lib/ccextractor/gpacmp4/movie_fragments.c \
               lib/ccextractor/gpacmp4/odf_code.c \
               lib/ccextractor/gpacmp4/odf_codec.c \
               lib/ccextractor/gpacmp4/odf_command.c \
               lib/ccextractor/gpacmp4/os_divers.c \
               lib/ccextractor/gpacmp4/qos.c \
               lib/ccextractor/gpacmp4/sample_descs.c \
               lib/ccextractor/gpacmp4/slc.c \
               lib/ccextractor/gpacmp4/stbl_read.c \
               lib/ccextractor/gpacmp4/stbl_write.c \
               lib/ccextractor/gpacmp4/track.c \
               lib/ccextractor/gpacmp4/tx3g.c \
               lib/ccextractor/gpacmp4/url.c \
               lib/ccextractor/gpacmp4/utf.c

    HEADERS += lib/ccextractor/gpacmp4/gpac/avparse.h \
               lib/ccextractor/gpacmp4/gpac/base_coding.h \
               lib/ccextractor/gpacmp4/gpac/bitstream.h \
               lib/ccextractor/gpacmp4/gpac/configuration.h \
               lib/ccextractor/gpacmp4/gpac/constants.h \
               lib/ccextractor/gpacmp4/gpac/ietf.h \
               lib/ccextractor/gpacmp4/gpac/internal/avilib.h \
               lib/ccextractor/gpacmp4/gpac/internal/isomedia_dev.h \
               lib/ccextractor/gpacmp4/gpac/internal/media_dev.h \
               lib/ccextractor/gpacmp4/gpac/internal/odf_dev.h \
               lib/ccextractor/gpacmp4/gpac/internal/odf_parse_common.h \
               lib/ccextractor/gpacmp4/gpac/internal/ogg.h \
               lib/ccextractor/gpacmp4/gpac/isomedia.h \
               lib/ccextractor/gpacmp4/gpac/list.h \
               lib/ccextractor/gpacmp4/gpac/math.h \
               lib/ccextractor/gpacmp4/gpac/media_tools.h \
               lib/ccextractor/gpacmp4/gpac/mpeg4_odf.h \
               lib/ccextractor/gpacmp4/gpac/network.h \
               lib/ccextractor/gpacmp4/gpac/setup.h \
               lib/ccextractor/gpacmp4/gpac/sync_layer.h \
               lib/ccextractor/gpacmp4/gpac/tools.h \
               lib/ccextractor/gpacmp4/gpac/utf.h \
               lib/ccextractor/gpacmp4/gpac/version.h \
               lib/ccextractor/gpacmp4/targetver.h

    DEFINES += fopen64=fopen
    DEFINES += open64=open
    DEFINES += lseek64=lseek
}

# Include the Fervor library (autoupdater)
!include("lib/fervor/Fervor.pri") {
    error("Unable to include Fervor. Try running `git submodule update --init --recursive`")
}

# Debugging information
debug {
    message($$CONFIG)
}
