#include <QQuickWidget>

class MyMainWindow : public QQuickWidget
{
private:
	const QString uiSource = "qrc:/DynamicSpot/MyMainWindow.qml";
private:
	QQuickItem* m_rootItem;
	QQuickItem* m_container;
	QQuickItem* m_timeBanner;
	QQuickItem* m_countDown;
	QTimer* m_timerAdjustColor;
public:
	explicit MyMainWindow(QWidget *parent = nullptr);
private:
	void initView();
	void initItem();
	void initTimer();
public slots:
	void adjustGeometry();
	void adjustcolor();
	void startBackgroundTest();
};
