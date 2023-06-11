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
constexpr auto major = 0;
constexpr auto minor = 3;
constexpr auto patch = 1;
constexpr auto versionString {"v0.3.1"};
}

namespace DynamicSpot::SettingsKey
{
constexpr auto enableSecondCountDown {"enableSecondCountDown"};
constexpr auto deadline {"deadline"};
}

namespace DynamicSpot::DefaultSettings
{
constexpr auto enableSecondCountDown {false};
const auto deadline {"2024-06-07_09-00-00"};
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
