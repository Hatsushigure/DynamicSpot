#include "DynamicSpotApp.h"
#include "DynamicSpot.h"
#include "HeLogger.h"
#include "MainWindowManager.h"
#include "ScheduleHost.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSplashScreen>
#include <QTimer>
#include <QQuickView>
#include "SettingsWindow.h"
#include <QFileDialog>
#include "ScheduleTestWidget.h"

DynamicSpotApp::DynamicSpotApp(int argc, char *argv[]) :
	QApplication(argc, argv)
{
	setOrganizationName("Hatsushigure");
	setApplicationName("DynamicSpot");
	HeLogger::logger()->info("成功初始化了 HeLogger. 程序版本: " + DynamicSpot::VersionInfo::versionString, "DynamicSpotApp");
	initSplashScreeen();
	HeLogger::logger()->info("初始化设置窗口...", staticMetaObject.className());
	DynamicSpot::settingsWindow = new SettingsWindow;
	HeLogger::logger()->info("设置窗口初始化成功", staticMetaObject.className());
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

void DynamicSpotApp::initSplashScreeen()
{
	using DynamicSpot::splashScreen;
	HeLogger::logger()->info("初始化启动窗口...", "DynamicSpotApp");
	QPixmap pix(":/DynamicSpot/images/icons/dynamicspot-logo-256.svg");
	pix = pix.scaled(QSize(128, 128), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	splashScreen = new QSplashScreen(pix, Qt::WindowStaysOnTopHint);
	connect(this, &DynamicSpotApp::allReady, this, &DynamicSpotApp::removeSplashScreen);
	splashScreen->show();
	if (!splashScreen->isVisible())
		HeLogger::logger()->warning("未成功显示启动窗口", "DynamicSpotApp");
	else
		HeLogger::logger()->info("成功显示了启动窗口", "DynamicSpotApp");

	m_timersplashScreen = new QTimer;
	m_timersplashScreen->setInterval(1000);
	m_timersplashScreen->setSingleShot(true);
	connect(m_timersplashScreen, &QTimer::timeout, this, &DynamicSpotApp::removeSplashScreen);
}

void DynamicSpotApp::initMainWindow()
{
	using DynamicSpot::mainWindowManager;
	HeLogger::logger()->info("初始化主窗口...", "DynamicSpotApp");
	mainWindowManager = new MainWindowManager;
	mainWindowManager->showWindow();
	mainWindowManager->window()->resize(1, 1);
	mainWindowManager->adjustGeometry();
	if (!mainWindowManager->window()->isVisible())
		HeLogger::logger()->error("无法显示主窗口", "DynamicSpotApp");
	else
		HeLogger::logger()->info("成功显示主窗口", "DynamicSpotApp");
}

void DynamicSpotApp::initScheduleHost()
{
	using DynamicSpot::scheduleHost;
	HeLogger::logger()->info("初始化时间表管理器...", "DynamicSpotApp");
	scheduleHost->readFromFile("./schedule.json");
	connect (scheduleHost, &ScheduleHost::currentIndexChanged, this, [this]() {
		if (scheduleHost->currentItem()->commandLine().isEmpty())
			return;
		auto proc = new QProcess;
		connect(proc, &QProcess::stateChanged, this, [proc]() {if (proc->state() == QProcess::NotRunning) delete proc;});
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
	menu4->addAction("缩略", DynamicSpot::mainWindowManager, &MainWindowManager::debug_setCountDownStateToShowShort);
	menu4->addAction("完整", DynamicSpot::mainWindowManager, &MainWindowManager::debug_setCountDownStateToShowFull);
	menu1->addAction("时间表测试", []() {
		HeLogger::logger()->warning("准备测试时间表, 即将清空当前时间表队列", staticMetaObject.className());
		DynamicSpot::scheduleHost->clearItems();
		auto w = new ScheduleTestWidget;
		w->setAttribute(Qt::WA_DeleteOnClose);
		w->show();
	});
	trayMenu->addAction("关于", DynamicSpot::settingsWindow, &SettingsWindow::show);
	trayMenu->addAction("选择时间表",this,  &DynamicSpotApp::selectScheduleFile);
	trayMenu->addAction("退出", &DynamicSpotApp::quit);
}

void DynamicSpotApp::initTrayIcon()
{
	using DynamicSpot::trayIcon;
	HeLogger::logger()->info("初始化托盘图标...", "DynamicSpotApp");
	trayIcon = new QSystemTrayIcon(QIcon(":/DynamicSpot/images/icons/dynamicspot-logo-256.svg"));
	trayIcon->setContextMenu(DynamicSpot::trayMenu);
	trayIcon->show();
	if (!trayIcon->isVisible())
	{
		HeLogger::logger()->fatal("无法显示托盘图标, 程序即将退出", "DynamicSpotApp");
		exit(-1);
	}
	else
		HeLogger::logger()->info("成功显示托盘图标", "DynamicSpotApp");
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
	using DynamicSpot::scheduleHost;
	if (scheduleHost == nullptr)
		return;
	auto fileName = QFileDialog::getOpenFileName(
				nullptr,
				"选择时间表文件",
				".",
				"Json 文件(*.json);;所有文件(*)"
				);
	if (QFile(scheduleHost->fileName()).exists())
		QFile::remove(scheduleHost->fileName());
	QFile::copy(fileName, scheduleHost->fileName());
	scheduleHost->readFromFile();
}
