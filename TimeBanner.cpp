#include "TimeBanner.h"
#include "SloganProvider.h"
#include "HeLogger.h"
#include <QTimer>

TimeBanner::TimeBanner(QObject *parent)
	: QObject{parent}
{
	auto logger = HeLogger::logger();
	logger->info("正在初始化时间改变计时器, 周期为 500ms", staticMetaObject.className());
	m_timerChangeTime = new QTimer(this);
	m_timerChangeTime->setInterval(500);
	connect(m_timerChangeTime, &QTimer::timeout, this, &TimeBanner::updateTime);
	m_timerChangeTime->start();
	logger->info("时间改变计时器初始化完成", staticMetaObject.className());
	logger->info("正在初始化标语选择器...", staticMetaObject.className());
	m_sloganProvider = new SloganProvider(this);
	logger->info("标语选择器初始化完成", staticMetaObject.className());
}

void TimeBanner::setTimeText(const QString& newTimeText)
{
	if (newTimeText == m_timeText)
		return;
	m_timeText = newTimeText;
	emit timeTextChanged();
}

void TimeBanner::updateTime()
{
	auto curTime = QTime::currentTime();
	setTimeText(curTime.toString("HH:mm:ss"));
}
