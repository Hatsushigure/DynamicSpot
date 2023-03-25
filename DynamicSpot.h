class DynamicSpotApp;
class MyMainWindow;
class QSystemTrayIcon;
class QMenu;
class QIcon;
class QSplashScreen;
class HeLogger;

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
