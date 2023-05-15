#include <QString>

class DynamicSpotApp;
class MainWindowManager;
class QSystemTrayIcon;
class QMenu;
class QSplashScreen;
class HeLogger;
class ScheduleHost;
class SettingsWindow;

namespace DynamicSpot::VersionInfo
{
const int major = 0;
const int minor = 2;
const int patch = 2;
const QString versionString = "v0.2.2";
}

namespace DynamicSpot
{
extern DynamicSpotApp* theApp;
extern MainWindowManager* mainWindowManager;
extern QMenu* trayMenu;
extern QSystemTrayIcon* trayIcon;
extern QSplashScreen* splashScreen;
extern ScheduleHost* scheduleHost;
extern SettingsWindow* settingsWindow;
}
