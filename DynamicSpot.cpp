#include "DynamicSpot.h"

namespace DynamicSpot
{
std::shared_ptr<spdlog::logger> logger;
DynamicSpotApp* theApp;
MainWindowManager *mainWindowManager;
QMenu* trayMenu;
QSystemTrayIcon* trayIcon;
QSplashScreen* splashScreen;
SettingsWindow* settingsWindow;
QSettings* settings;
CountDown* countDown;
}
