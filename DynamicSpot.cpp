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
ScheduleHost* scheduleHost;
SettingsWindow* settingsWindow;
}

namespace DynamicSpot::Icons
{
QIcon avatar;
}
