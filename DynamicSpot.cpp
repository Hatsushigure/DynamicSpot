#include "DynamicSpot.h"
#include <QIcon>

namespace DynamicSpot
{
DynamicSpotApp* theApp;
MainWindowManager *mainWindowManager;
QMenu* trayMenu;
QSystemTrayIcon* trayIcon;
QSplashScreen* splashScreen;
HeLogger* logger;
}

namespace DynamicSpot::Icons
{
QIcon avatar;
}
