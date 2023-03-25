#include "DynamicSpot.h"
#include <QIcon>

namespace DynamicSpot
{
DynamicSpotApp* theApp;
MyMainWindow *mainWindow;
QMenu* trayMenu;
QSystemTrayIcon* trayIcon;
QSplashScreen* splashScreen;
HeLogger* logger;
}

namespace DynamicSpot::Icons
{
QIcon avatar;
}
