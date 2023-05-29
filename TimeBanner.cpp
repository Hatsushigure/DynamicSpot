#include "TimeBanner.h"
#include "SloganProvider.h"
#include "HeLogger.h"
#include <QTimer>

using Qt::StringLiterals::operator""_s;

TimeBanner::TimeBanner(QObject *parent)
	: QObject{parent}
{
	auto logger = HeLogger::logger();
	logger->info("正在初始化时间横幅", staticMetaObject.className());

	logger->info(u"正在初始化 timerHeartBeat, 周期 %1ms"_s.arg(QString::number(heartBeeatInterval)), staticMetaObject.className());
	m_timerHeartBeat = new QTimer(this);
	m_timerHeartBeat->setInterval(heartBeeatInterval);
	connect(m_timerHeartBeat, &QTimer::timeout, this, &TimeBanner::updateTime);
	logger->info("timerHeartBeat 初始化完成", staticMetaObject.className());

	logger->info(u"正在初始化 timerSloganDuration, 周期 %1ms"_s.arg(QString::number(sloganDuration)), staticMetaObject.className());
	m_timerSloganDuration = new QTimer(this);
	m_timerSloganDuration->setInterval(sloganDuration);
	//connect(m_timerSloganDuration, &QTimer::timeout, this, &TimeBanner::updateTime);
	logger->info("timerHeartBeat 初始化完成", staticMetaObject.className());

	logger->info("正在初始化标语选择器...", staticMetaObject.className());
	m_sloganProvider = new SloganProvider(this);
	logger->info("标语选择器初始化完成", staticMetaObject.className());

	logger->info("正在启动计时器...", staticMetaObject.className());
	m_timerHeartBeat->start();

	logger->info("时间横幅初始化完成", staticMetaObject.className());
}

void TimeBanner::setTimeText(const QString& newTimeText)
{
	if (newTimeText == m_timeText)
		return;
	m_timeText = newTimeText;
	emit timeTextChanged();
}

void TimeBanner::setStateString(const States newState)
{
	if (newState == m_state)
		return;
	m_state = newState;
	switch (newState)
	{
	case States::ShowSlogan:
		m_stateString = "showSlogan";
		break;
	case States::ShowSchedule:
		m_stateString = "showSchedule";
		break;
	case States::ShowTime:
		m_stateString = "showTime";
		break;
	}
	emit stateStringChanged();
}

void TimeBanner::updateTime()
{
	auto curTime = QTime::currentTime();
	setTimeText(curTime.toString("HH:mm:ss"));
}
