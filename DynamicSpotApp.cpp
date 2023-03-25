#include "DynamicSpotApp.h"
#include "DynamicSpot.h"
#include "HeLogger.h"
#include "MyMainWindow.h"
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
	logger->info("log test", "DynamicSpotApp");
	logger->warning("warning test");
	qCritical() << "error test";
}

void DynamicSpotApp::initSplashScreeen()
{
	using DynamicSpot::splashScreen;
	QPixmap pix(":/DynamicSpot/images/icons/avatar/avatar - 256.png");
	pix = pix.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	splashScreen = new QSplashScreen(pix, Qt::WindowStaysOnTopHint);
	connect(this, &DynamicSpotApp::allReady, this, &DynamicSpotApp::removeSplashScreen);
	splashScreen->show();

	m_timersplashScreen = new QTimer;
	m_timersplashScreen->setInterval(1000);
	m_timersplashScreen->setSingleShot(true);
	connect(m_timersplashScreen, &QTimer::timeout, this, &DynamicSpotApp::removeSplashScreen);
}

void DynamicSpotApp::initIcons()
{
	using namespace DynamicSpot::Icons;
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 32.png");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 48.png");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 64.png");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 96.png");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 128.png");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 144.png");
	avatar.addFile(":/DynamicSpot/images/icons/avatar/avatar - 256.png");
}

void DynamicSpotApp::initMainWindow()
{
	using DynamicSpot::mainWindow;
	mainWindow = new MyMainWindow;
	mainWindow->show();
}

void DynamicSpotApp::initTrayMenu()
{
	using DynamicSpot::trayMenu;
	trayMenu = new QMenu;
	trayMenu->addAction("退出", &DynamicSpotApp::quit);
}

void DynamicSpotApp::initTrayIcon()
{
	using DynamicSpot::trayIcon;
	trayIcon = new QSystemTrayIcon(DynamicSpot::Icons::avatar);
	trayIcon->setContextMenu(DynamicSpot::trayMenu);
	trayIcon->show();
}

void DynamicSpotApp::removeSplashScreen()
{
	using DynamicSpot::splashScreen;
	splashScreen->close();
	delete splashScreen;
	splashScreen = nullptr;
}
