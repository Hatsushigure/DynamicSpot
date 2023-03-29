#include "MyMainWindow.h"
#include "DynamicSpot.h"
#include "DynamicSpotApp.h"
#include "MyAutoColorHelper.h"
#include <QQuickItem>
#include <QTimer>

MyMainWindow::MyMainWindow(QWidget *parent) :
	QQuickWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	initView();
	initItem();
	initTimer();
	adjustGeometry();
}

void MyMainWindow::adjustGeometry()
{
	resize(m_container->width(), m_container->height());
	QScreen* scr = DynamicSpot::theApp->primaryScreen();
	move((scr->size().width() - width()) / 2, 0);
}

void MyMainWindow::adjustcolor()
{
	QRect geometry(m_container->mapToGlobal(QPointF(0, 0)).toPoint(), m_container->size().toSize());
	QColor col = MyAutoColorHelper::getColorFromGeometry(geometry, this->screen());
	QColor contrastColor = MyAutoColorHelper::getContrastColor(col);
	m_timeBanner->setProperty("textColor", contrastColor);
	m_countDown->setProperty("textColor", contrastColor);
}

void MyMainWindow::aprilFool()
{
	disconnect(m_timerAdjustColor, &QTimer::timeout, this, &MyMainWindow::adjustcolor);
}

void MyMainWindow::initView()
{
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setSource(uiSource);
	setClearColor(Qt::transparent);
}

void MyMainWindow::initItem()
{
	m_rootItem = rootObject();

	m_container = m_rootItem->findChild<QQuickItem*>("container");
	connect(m_container, &QQuickItem::widthChanged, this, &MyMainWindow::adjustGeometry);
	connect(m_container, &QQuickItem::heightChanged, this, &MyMainWindow::adjustGeometry);

	m_timeBanner = m_container->findChild<QQuickItem*>("timeBanner");
	m_countDown = m_container->findChild<QQuickItem*>("countDown");
}

void MyMainWindow::initTimer()
{
	m_timerAdjustColor = new QTimer(this);
	m_timerAdjustColor->setInterval(500);
	connect(m_timerAdjustColor, &QTimer::timeout, this, &MyMainWindow::adjustcolor);
	m_timerAdjustColor->start();
}
