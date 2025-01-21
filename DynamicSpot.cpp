#include "DynamicSpot.h"

namespace DynamicSpot
{
std::shared_ptr<spdlog::logger> logger;
DynamicSpotApp* theApp;
std::shared_ptr<ConfigManager> configManager;
MainWindowManager *mainWindowManager;
QMenu* trayMenu;
QSystemTrayIcon* trayIcon;
QSplashScreen* splashScreen;
SettingsWindow* settingsWindow;
CountDown* countDown;
}
