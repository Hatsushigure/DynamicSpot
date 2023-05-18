#include "MainWindowManager.h"
#include "DynamicSpot.h"
#include "DynamicSpotApp.h"
#include "HeLogger.h"
#include "ScheduleHost.h"
#include <QQuickItem>
#include <QTimer>
#include <QQuickView>

MainWindowManager::MainWindowManager(QObject *parent) :
	QObject(parent)
{
	initView();
	initItem();
	initTimer();
	updateDaysLeft();
}

int MainWindowManager::daysLeft() const
{
	return m_daysLeft;
}

void MainWindowManager::setDaysLeft(int newDaysLeft)
{
	if (m_daysLeft == newDaysLeft)
		return;
	m_daysLeft = newDaysLeft;
	emit daysLeftChanged();
}

QQuickView* MainWindowManager::window()
{
	return m_view;
}

void MainWindowManager::initView()
{
	QQuickView::setDefaultAlphaBuffer(true);
	HeLogger::logger()->info("为全局 QQuickView 开启了 Alpha 通道", "MainWindowManager");
	m_view = new QQuickView;
	m_view->setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowTransparentForInput | Qt::Tool);
	m_view->setColor(Qt::transparent);
	m_view->setResizeMode(QQuickView::SizeRootObjectToView);
	m_view->setSource(uiSource);
	HeLogger::logger()->info("加载了 ui 文件 " + uiSource, "MainWindowManager");
}

void MainWindowManager::initItem()
{
	m_rootItem = m_view->rootObject();

	m_container = m_rootItem->findChild<QQuickItem*>("container");
	connect(m_container, &QQuickItem::widthChanged, this, &MainWindowManager::adjustGeometry);
	connect(m_container, &QQuickItem::heightChanged, this, &MainWindowManager::adjustGeometry);

	m_timeBanner = m_container->findChild<QQuickItem*>("timeBanner");
	m_countDown = m_container->findChild<QQuickItem*>("countDown");

	DynamicSpot::scheduleHost = m_timeBanner->findChild<ScheduleHost*>("scheduleHost");
}

void MainWindowManager::initTimer()
{
	m_timerUpdateDate = new QTimer(this);
	m_timerUpdateDate->setInterval(10000);
	connect(m_timerUpdateDate, &QTimer::timeout, this, &MainWindowManager::updateDaysLeft);
	connect(this, &MainWindowManager::daysLeftChanged, this, &MainWindowManager::updateCountDownText);
	m_timerUpdateDate->start();
	HeLogger::logger()->info("启动了更新日期计时器, 周期 10000 毫秒", "MainWindowManager");
}

void MainWindowManager::adjustGeometry()
{
	if (m_container->width() > m_view->width() + 10)
		m_view->setWidth(m_container->width() + 10);
	if (m_container->height() > m_view->height() + 10)
		m_view->setHeight(m_container->height() + 10);
	QScreen* scr = DynamicSpot::theApp->primaryScreen();
	m_view->setPosition((scr->size().width() - m_view->width()) / 2, 0);
}

void MainWindowManager::updateDaysLeft()
{
	setDaysLeft(deadline.toJulianDay() - QDate::currentDate().toJulianDay());
}

void MainWindowManager::updateCountDownText()
{
	using Qt::StringLiterals::operator""_s;
	HeLogger::logger()->info("检测到日期变化, 正在更新倒计时天数", "MainWindowManager");
	m_countDown->setProperty("shortText", u"<span style=\"color: red; font-weight: bold\">%1</span>"_s.arg(QString::number(daysLeft())));
	m_countDown->setProperty("fullText", u"距离高考仅剩 <span style=\"color: red; font-weight: bold\">%1</span> 天"_s.arg(QString::number(daysLeft())));
}

void MainWindowManager::showWindow()
{
	m_view->show();
}

void MainWindowManager::debug_setTimeBannerStateToShowTime()
{
	if (m_timeBanner == nullptr)
		return;
	m_timeBanner->setState("showTime");
}

void MainWindowManager::debug_setTimeBannerStateToShowSlogan()
{
	if (m_timeBanner == nullptr)
		return;
	QMetaObject::invokeMethod(m_timeBanner, "showSlogan");
	//m_timeBanner->setState("showSlogan");

}

void MainWindowManager::debug_setTimeBannerStateToShowSchedule()
{
	if (m_timeBanner == nullptr)
		return;
	m_timeBanner->setState("showSchedule");

}

void MainWindowManager::debug_setCountDownStateToShowShort()
{
	if (m_countDown == nullptr)
		return;
	m_countDown->setState("showShort");
}

void MainWindowManager::debug_setCountDownStateToShowFull()
{
	if (m_countDown == nullptr)
		return;
	m_countDown->setState("showFull");

}
