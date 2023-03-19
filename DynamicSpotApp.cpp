#include "DynamicSpotApp.h"
#include "DynamicSpot.h"
#include "MyMainWindow.h"
#include <QSystemTrayIcon>
#include <QMenu>

DynamicSpotApp::DynamicSpotApp(int argc, char *argv[]) :
	QApplication(argc, argv)
{
	setOrganizationName("Hatsushigure");
	setApplicationName("DynamicSpot");
	initMainWindow();
	initTrayMenu();
	initTrayIcon();
}

DynamicSpotApp::~DynamicSpotApp()
{
	delete DynamicSpot::trayMenu;
	delete DynamicSpot::trayMenu;
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
	QIcon ico;
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 32.png");
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 48.png");
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 64.png");
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 96.png");
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 128.png");
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 144.png");
	ico.addFile(":/DynamicSpot/images/icons/avatar/avatar - 256.png");
	trayIcon = new QSystemTrayIcon(ico);
	trayIcon->setContextMenu(DynamicSpot::trayMenu);
	trayIcon->show();
}
