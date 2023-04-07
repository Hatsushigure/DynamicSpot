#include <QQuickWidget>
#include <QDate>

class QQuickView;

class MyMainWindow : public QWidget
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
	QWidget* m_viewWidget;
	int m_daysLeft;
public:
	explicit MyMainWindow(QWidget *parent = nullptr);
public:
	int daysLeft() const;
	void setDaysLeft(int newDaysLeft);
private:
	void initView();
	void initItem();
	void initTimer();
public slots:
	void adjustGeometry();
	void adjustcolor();
	void updatedaysLeft();
	void updateCountDownText();
	void startBackgroundTest();
signals:
	void daysLeftChanged();
};
