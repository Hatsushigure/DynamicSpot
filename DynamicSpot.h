#include <QString>

class DynamicSpotApp;
class MainWindowManager;
class QSystemTrayIcon;
class QMenu;
class QIcon;
class QSplashScreen;
class HeLogger;

namespace DynamicSpot::VersionInfo
{
const int major = 0;
const int minor = 1;
const int patch = 2;
const QString versionString = "v0.1.2";
}

namespace DynamicSpot
{
extern DynamicSpotApp* theApp;
extern MainWindowManager* mainWindowManager;
extern QMenu* trayMenu;
extern QSystemTrayIcon* trayIcon;
extern QSplashScreen* splashScreen;
extern HeLogger* logger;
}

namespace DynamicSpot::Icons
{
extern QIcon avatar;
}
