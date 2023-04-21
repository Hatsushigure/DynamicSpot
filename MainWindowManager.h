#include <QDate>
#include <QObject>

class QQuickView;
class QQuickItem;

class MainWindowManager : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int daysLeft READ daysLeft WRITE setDaysLeft NOTIFY daysLeftChanged)
private:
	const QString uiSource = "qrc:/DynamicSpot/MyMainWindow.qml";
	const QDate deadline = QDate(2023, 6,7);
private:
	QQuickItem* m_rootItem;
	QQuickItem* m_container;
	QQuickItem* m_timeBanner;
	QQuickItem* m_countDown;
	QTimer* m_timerAdjustColor;
	QTimer* m_timerUpdateDate;
	QQuickView* m_view;
	int m_daysLeft;
public:
	explicit MainWindowManager(QObject *parent = nullptr);
public:
	int daysLeft() const;
	void setDaysLeft(int newDaysLeft);
	QQuickView* window();
private:
	void initView();
	void initItem();
	void initTimer();
public slots:
	void adjustGeometry();
	void adjustcolor();
	void updatedaysLeft();
	void updateCountDownText();
	void showWindow();
	void debug_backgroundColor();
	void debug_setTimeBannerStateToShowTime();
	void debug_setTimeBannerStateToShowSlogan();
	void debug_setTimeBannerStateToShowSchedule();
	void debug_setCountDownStateToShowShort();
	void debug_setCountDownStateToShowFull();
signals:
	void daysLeftChanged();
};
