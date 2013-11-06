#include "subtitler.h"
#include "ui_subtitler.h"

Subtitler::Subtitler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Subtitler)
{
    ui->setupUi(this);

    // Link the "check for updates manually" button with the autoupdater
    //connect(ui->updateButton, SIGNAL(clicked()),
    //        FvUpdater::sharedUpdater(), SLOT(CheckForUpdatesNotSilent()));
    //ui->label->setText(tr("Version %1").arg(QApplication::applicationVersion()));
}

Subtitler::~Subtitler()
{
    delete ui;
}
