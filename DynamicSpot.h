#include <QString>

class DynamicSpotApp;
class MainWindowManager;
class QSystemTrayIcon;
class QMenu;
class QIcon;
class QSplashScreen;
class HeLogger;
class ScheduleHost;

namespace DynamicSpot::VersionInfo
{
const int major = 0;
const int minor = 2;
const int patch = 0;
const QString versionString = "v0.2.0";
}

namespace DynamicSpot
{
extern DynamicSpotApp* theApp;
extern MainWindowManager* mainWindowManager;
extern QMenu* trayMenu;
extern QSystemTrayIcon* trayIcon;
extern QSplashScreen* splashScreen;
extern HeLogger* logger;
extern ScheduleHost* scheduleHost;
}

namespace DynamicSpot::Icons
{
extern QIcon avatar;
}
