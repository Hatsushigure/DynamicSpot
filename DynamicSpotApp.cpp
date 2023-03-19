#include "DynamicSpotApp.h"
#include "DynamicSpot.h"
#include "MyMainWindow.h"

DynamicSpotApp::DynamicSpotApp(int argc, char *argv[]) :
	QApplication(argc, argv)
{
	initMainWindow();
}

void DynamicSpotApp::initMainWindow()
{
	using DynamicSpot::mainWindow;
	mainWindow = new MyMainWindow;
	mainWindow->show();
}
