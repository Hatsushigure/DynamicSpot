#include <QApplication>

class DynamicSpotApp : public QApplication
{
	Q_OBJECT
private:
	bool m_allReady;
	QTimer* m_timersplashScreen;
public:
	DynamicSpotApp(int argc, char *argv[]);
	~DynamicSpotApp();
private:
	void initLogger();
	void initSplashScreeen();
	void initIcons();
	void initMainWindow();
	void initTrayMenu();
	void initTrayIcon();
private:
	void removeSplashScreen();
signals:
	void allReady();
};
