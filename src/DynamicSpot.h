#include <string_view>
#include <memory>

class DynamicSpotApp;
class MainWindowManager;
class QSystemTrayIcon;
class QMenu;
class QSplashScreen;
class HeLogger;
class SettingsWindow;
class CountDown;

namespace DynamicSpot
{
class ConfigManager;
}

namespace spdlog
{
class logger;
}

namespace DynamicSpot::VersionInfo
{
constexpr auto major {0};
constexpr auto minor {4};
constexpr auto patch {0};
constexpr std::string_view versionString {"dev-v0.4.0"};
constexpr auto configVer {1};
}

namespace DynamicSpot::SettingsKey
{
constexpr std::string_view version {"version"};
constexpr std::string_view enableSecondCountDownV0 {"enableSecondCountDown"};
constexpr std::string_view enableSecondCountDown {"Function/enableSecondCountDown"};
constexpr std::string_view deadline {"deadline"};
constexpr std::string_view enableSlogan {"Function/enableSlogan"};
}

namespace DynamicSpot::DefaultSettings
{
constexpr auto enableSecondCountDown {false};
const std::string_view deadline {"2025-06-07_09-00-00"};
constexpr auto enableSlogan {true};
}

namespace DynamicSpot
{
extern std::shared_ptr<spdlog::logger> logger;
extern DynamicSpotApp* theApp;
extern std::shared_ptr<ConfigManager> configManager;
extern MainWindowManager* mainWindowManager;
extern QMenu* trayMenu;
extern QSystemTrayIcon* trayIcon;
extern QSplashScreen* splashScreen;
extern SettingsWindow* settingsWindow;
extern CountDown* countDown;
}
