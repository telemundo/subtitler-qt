#include <QApplication>
#include <QIcon>

#include "subtitler.h"
#include "fvupdater.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Pre-requisites for Fervor
    app.setApplicationName("Subtitler");
    app.setApplicationVersion(APP_VERSION);
    app.setOrganizationName("Telemundo Digital Media");
    app.setOrganizationDomain("com.telemundo.subtitler");

    // Set feed URL before doing anything else
    FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/pypt/fervor/master/sample/Appcast.xml");

    // Check for updates automatically
    FvUpdater::sharedUpdater()->CheckForUpdatesSilent();

    // Display main window
    Subtitler window;
    window.show();

    return app.exec();
}
