#include "DynamicSpotApp.h"
#include "DynamicSpot.h"
#include "HeLogger.h"
#include "MyMainWindow.h"
#include "MyAutoColorHelper.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSplashScreen>
#include <QTimer>

DynamicSpotApp::DynamicSpotApp(int argc, char *argv[]) :
	QApplication(argc, argv)
{
	setOrganizationName("Hatsushigure");
	setApplicationName("DynamicSpot");
	initLogger();
	initSplashScreeen();
	initIcons();
	initMainWindow();
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
	using DynamicSpot::logger;
	logger = new HeLogger;
	logger->info("成功初始化了 HeLogger. 程序版本: " + DynamicSpot::VersionInfo::versionString, "DynamicSpotApp");
}

void DynamicSpotApp::initSplashScreeen()
{
	using DynamicSpot::splashScreen;
	HeLogger::info("初始化启动窗口...", "DynamicSpotApp");
	QPixmap pix(":/DynamicSpot/images/icons/avatar/avatar - 256.png");
	pix = pix.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	splashScreen = new QSplashScreen(pix, Qt::WindowStaysOnTopHint);
	connect(this, &DynamicSpotApp::allReady, this, &DynamicSpotApp::removeSplashScreen);
	splashScreen->show();
	if (!splashScreen->isVisible())
		HeLogger::warning("未成功显示启动窗口", "DynamicSpotApp");
	else
		HeLogger::info("成功显示了启动窗口", "DynamicSpotApp");

	m_timersplashScreen = new QTimer;
	m_timersplashScreen->setInterval(1000);
	m_timersplashScreen->setSingleShot(true);
	connect(m_timersplashScreen, &QTimer::timeout, this, &DynamicSpotApp::removeSplashScreen);
}

void DynamicSpotApp::initIcons()
{
	using namespace DynamicSpot::Icons;
	HeLogger::info("初始化图标 \"avatar\"...", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 32.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 32.png", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 48.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 48.png", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 64.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 64.png", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 96.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 96.png", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 128.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 128.png", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 144.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 144.png", "DynamicSpotApp");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 256.png");
	HeLogger::info("加载了文件 :/DynamicSpot/images/icons/avatar/avatar - 256.png", "DynamicSpotApp");
	HeLogger::info("初始化了图标 \"avatar\"", "DynamicSpotApp");
}

void DynamicSpotApp::initMainWindow()
{
	using DynamicSpot::mainWindow;
	HeLogger::info("初始化主窗口...", "DynamicSpotApp");
	MyAutoColorHelper::setSampleCount(64);
	HeLogger::info("将采样点设置为 64 个", "DynamicSpotApp");
	mainWindow = new MyMainWindow;
	mainWindow->show();
	if (!mainWindow->isVisible())
		HeLogger::error("无法显示主窗口", "DynamicSpotApp");
	else
		HeLogger::info("成功显示主窗口", "DynamicSpotApp");
}

void DynamicSpotApp::initTrayMenu()
{
	using DynamicSpot::trayMenu;
	trayMenu = new QMenu;
	QMenu* menu1 = trayMenu->addMenu("调试");
	menu1->addAction("调试自动颜色", DynamicSpot::mainWindow, &MyMainWindow::startBackgroundTest);
	menu1->addAction("切换时间窗体状态", DynamicSpot::mainWindow, &MyMainWindow::toggleTimeBannerState);
	menu1->addAction("切换倒计时窗体状态", DynamicSpot::mainWindow, &MyMainWindow::toggleCountDownState);
	trayMenu->addAction("退出", &DynamicSpotApp::quit);
}

void DynamicSpotApp::initTrayIcon()
{
	using DynamicSpot::trayIcon;
	HeLogger::info("初始化托盘图标...", "DynamicSpotApp");
	trayIcon = new QSystemTrayIcon(DynamicSpot::Icons::avatar);
	trayIcon->setContextMenu(DynamicSpot::trayMenu);
	trayIcon->show();
	if (!trayIcon->isVisible())
	{
		HeLogger::fatal("无法显示托盘图标, 程序即将退出", "DynamicSpotApp");
		exit(-1);
	}
	else
		HeLogger::error("成功显示托盘图标", "DynamicSpotApp");
}

void DynamicSpotApp::removeSplashScreen()
{
	using DynamicSpot::splashScreen;
	splashScreen->close();
	delete splashScreen;
	splashScreen = nullptr;
}
