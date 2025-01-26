#include "DynamicSpotApp.h"
#include "DynamicSpot.h"
#include "MainWindowManager.h"
#include "ScheduleHost.h"
#include "SettingsWindow.h"
#include "ScheduleTestWidget.h"
#include "CountDown.h"
#include "ConfigManager.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSplashScreen>
#include <QTimer>
#include <QQuickView>
#include <QFileDialog>
#include <format>
#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/stopwatch.h>


DynamicSpotApp::DynamicSpotApp(int argc, char *argv[]) :
	QApplication(argc, argv)
{
	setOrganizationName("Hatsushigure");
	setApplicationName("DynamicSpot");
	initLogger();
	DynamicSpot::logger->info("启动 DynamicSpot... 程序版本: {}", DynamicSpot::VersionInfo::versionString);
	initSplashScreeen();
	initConfig();
	DynamicSpot::logger->debug("初始化设置窗口...");
	DynamicSpot::settingsWindow = new SettingsWindow;
	DynamicSpot::logger->debug("设置窗口初始化成功");
	initMainWindow();
	initScheduleHost();
	initTrayMenu();
	initTrayIcon();
	m_timersplashScreen->start();
}

DynamicSpotApp::~DynamicSpotApp()
{
	delete DynamicSpot::trayIcon;
	delete DynamicSpot::trayMenu;
}

void DynamicSpotApp::initLogger()
{
	auto currentDateTime = QDateTime::currentDateTime();
	auto logFilename = std::format("logs/{}.log", currentDateTime.toString("yyyy-MM-dd_HH-mm-ss").toStdString());
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilename);
	fileSink->set_level(spdlog::level::info);
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_level(spdlog::level::debug);
	auto logger = std::shared_ptr<spdlog::logger>(new spdlog::logger("DynamicSpotLogger", {consoleSink, fileSink}));
	logger->set_level(spdlog::level::debug);
	spdlog::register_logger(logger);
	spdlog::flush_every(std::chrono::seconds(5));
	DynamicSpot::logger = logger;
}

void DynamicSpotApp::initSplashScreeen()
{
	using DynamicSpot::splashScreen;
	DynamicSpot::logger->debug("初始化启动窗口...", "DynamicSpotApp");
	QPixmap pix(":/DynamicSpot/images/icons/dynamicspot-logo@256px.png");
	pix = pix.scaled(QSize(128, 128), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	splashScreen = new QSplashScreen(pix, Qt::WindowStaysOnTopHint);
	connect(this, &DynamicSpotApp::allReady, this, &DynamicSpotApp::removeSplashScreen);
	splashScreen->show();
	if (!splashScreen->isVisible())
		DynamicSpot::logger->error("未成功显示启动窗口");
	else
		DynamicSpot::logger->debug("成功显示了启动窗口", "DynamicSpotApp");

	m_timersplashScreen = new QTimer;
	m_timersplashScreen->setInterval(1000);
	m_timersplashScreen->setSingleShot(true);
	connect(m_timersplashScreen, &QTimer::timeout, this, &DynamicSpotApp::removeSplashScreen);
}

void DynamicSpotApp::initConfig()
{
	using DynamicSpot::configManager;
	using DynamicSpot::ConfigManager;

	DynamicSpot::logger->debug("Initializing config...");
	configManager = std::make_shared<ConfigManager>();
	DynamicSpot::logger->debug("Config initialized");
}

void DynamicSpotApp::initMainWindow()
{
	using DynamicSpot::mainWindowManager;
	DynamicSpot::logger->debug("初始化主窗口...");
	mainWindowManager = new MainWindowManager;
	mainWindowManager->showWindow();
	mainWindowManager->window()->resize(1, 1);
	mainWindowManager->adjustGeometry();
	if (!mainWindowManager->window()->isVisible())
	{
		DynamicSpot::logger->critical("无法显示主窗口");
		exit(-1);
	}
	else
		DynamicSpot::logger->debug("成功显示主窗口", "DynamicSpotApp");
}

void DynamicSpotApp::initScheduleHost()
{
	auto scheduleHost = ScheduleHost::instance();
	DynamicSpot::logger->debug("初始化时间表管理器...");
	scheduleHost->readFromFile("./schedule.json");
	connect (scheduleHost, &ScheduleHost::currentIndexChanged, [scheduleHost]() {
		if (scheduleHost->currentItem()->commandLine().isEmpty())
			return;
		auto proc = new QProcess;
		connect(proc, &QProcess::stateChanged, [proc]() {if (proc->state() == QProcess::NotRunning) delete proc;});
		proc->startCommand(scheduleHost->currentItem()->commandLine());
	});
}

void DynamicSpotApp::initTrayMenu()
{
	using DynamicSpot::trayMenu;
	trayMenu = new QMenu;
	auto menu1 = trayMenu->addMenu("调试");
	auto menu2 = menu1->addMenu("设置状态");
	auto menu3 = menu2->addMenu("时间横幅");
	menu3->addAction("显示时间", DynamicSpot::mainWindowManager, &MainWindowManager::debug_setTimeBannerStateToShowTime);
	menu3->addAction("显示标语", DynamicSpot::mainWindowManager, &MainWindowManager::debug_setTimeBannerStateToShowSlogan);
	menu3->addAction("显示时间表", DynamicSpot::mainWindowManager, &MainWindowManager::debug_setTimeBannerStateToShowSchedule);
	auto menu4 = menu2->addMenu("倒计时");
	menu4->addAction("缩略", []() {
		if (DynamicSpot::countDown == nullptr)
			return;
                DynamicSpot::countDown->setState(CountDown::States::ShowShort);
	});
	menu4->addAction("完整", []() {
		if (DynamicSpot::countDown == nullptr)
			return;
                DynamicSpot::countDown->setState(CountDown::States::ShowFull);

	});
	menu1->addAction("时间表测试", []() {
		DynamicSpot::logger->warn("准备测试时间表, 即将清空当前时间表队列");
		ScheduleHost::instance()->clearItems();
		auto w = new ScheduleTestWidget;
		w->setAttribute(Qt::WA_DeleteOnClose);
		w->show();
	});
	trayMenu->addAction("关于", DynamicSpot::settingsWindow, &SettingsWindow::show);
	trayMenu->addAction("选择时间表", this,  &DynamicSpotApp::selectScheduleFile);
	trayMenu->addAction("退出", &DynamicSpotApp::quit);
}

void DynamicSpotApp::initTrayIcon()
{
	using DynamicSpot::trayIcon;
	DynamicSpot::logger->debug("初始化托盘图标...");
	trayIcon = new QSystemTrayIcon(QIcon(":/DynamicSpot/images/icons/dynamicspot-logo@256px.png"));
	trayIcon->setContextMenu(DynamicSpot::trayMenu);
	trayIcon->show();
	if (!trayIcon->isVisible())
	{
		DynamicSpot::logger->critical("无法显示托盘图标, 程序即将退出", "DynamicSpotApp");
		exit(-1);
	}
	else
		DynamicSpot::logger->debug("成功显示托盘图标", "DynamicSpotApp");
}

void DynamicSpotApp::removeSplashScreen()
{
	using DynamicSpot::splashScreen;
	splashScreen->close();
	delete splashScreen;
	splashScreen = nullptr;
}

void DynamicSpotApp::selectScheduleFile()
{
	auto scheduleHost = ScheduleHost::instance();
	if (scheduleHost == nullptr)
		return;
	auto fileName = QFileDialog::getOpenFileName(
						nullptr,
						"选择时间表文件",
						".",
						"Json 文件(*.json);;所有文件(*)"
						);
	if (fileName == scheduleHost->fileName())
	{
		scheduleHost->readFromFile();
		return;
	}
	if (QFile(scheduleHost->fileName()).exists())
		QFile::remove(scheduleHost->fileName());
	QFile::copy(fileName, scheduleHost->fileName());
	scheduleHost->readFromFile();
}
