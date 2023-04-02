#include <QString>

class DynamicSpotApp;
class MyMainWindow;
class QSystemTrayIcon;
class QMenu;
class QIcon;
class QSplashScreen;
class HeLogger;

namespace DynamicSpot::VersionInfo
{
const int major = 0;
const int minor = 1;
const int patch = 1;
const QString versionString = "v0.1.1";
}

namespace DynamicSpot
{
extern DynamicSpotApp* theApp;
extern MyMainWindow* mainWindow;
extern QMenu* trayMenu;
extern QSystemTrayIcon* trayIcon;
extern QSplashScreen* splashScreen;
extern HeLogger* logger;
}

namespace DynamicSpot::Icons
{
extern QIcon avatar;
}
