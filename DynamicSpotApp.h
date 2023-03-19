#include <QApplication>

class DynamicSpotApp : public QApplication
{
private:
public:
	DynamicSpotApp(int argc, char *argv[]);
private:
	void initMainWindow();
};
