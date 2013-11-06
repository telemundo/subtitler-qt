#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Link the "check for updates manually" button with the autoupdater
    //connect(ui->updateButton, SIGNAL(clicked()),
    //        FvUpdater::sharedUpdater(), SLOT(CheckForUpdatesNotSilent()));
    //ui->label->setText(tr("Version %1").arg(QApplication::applicationVersion()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
