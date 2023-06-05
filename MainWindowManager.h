#include <QDate>
#include <QObject>

class QQuickView;
class QQuickItem;
class TimeBanner;

class MainWindowManager : public QObject
{
	Q_OBJECT
private:
	const QString uiSource = "qrc:/DynamicSpot/qml/MyMainWindow.qml";
private:
	QQuickItem* m_rootItem;
	QQuickItem* m_container;
	TimeBanner* m_timeBanner;
	QQuickItem* m_countDown;
	QQuickView* m_view;
	int m_daysLeft;
public:
	explicit MainWindowManager(QObject *parent = nullptr);
public:
	QQuickView* window();
private:
	void initView();
	void initItem();
public slots:
	void adjustGeometry();
	void showWindow();
	void debug_setTimeBannerStateToShowTime();
	void debug_setTimeBannerStateToShowSlogan();
	void debug_setTimeBannerStateToShowSchedule();
};
