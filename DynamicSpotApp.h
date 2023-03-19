#include <QApplication>

class DynamicSpotApp : public QApplication
{
private:
public:
	DynamicSpotApp(int argc, char *argv[]);
	~DynamicSpotApp();
private:
	void initMainWindow();
	void initTrayMenu();
	void initTrayIcon();
};
