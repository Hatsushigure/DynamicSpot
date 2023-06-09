#include <QString>

class DynamicSpotApp;
class MainWindowManager;
class QSystemTrayIcon;
class QMenu;
class QSplashScreen;
class HeLogger;
class SettingsWindow;
class QSettings;
class CountDown;

namespace DynamicSpot::VersionInfo
{
const int major = 0;
const int minor = 3;
const int patch = 1;
const QString versionString = "v0.3.1";
}

namespace DynamicSpot
{
extern DynamicSpotApp* theApp;
extern MainWindowManager* mainWindowManager;
extern QMenu* trayMenu;
extern QSystemTrayIcon* trayIcon;
extern QSplashScreen* splashScreen;
extern SettingsWindow* settingsWindow;
extern QSettings* settings;
extern CountDown* countDown;
}
