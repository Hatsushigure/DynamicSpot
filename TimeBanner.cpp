#include "TimeBanner.h"
#include "SloganProvider.h"
#include "HeLogger.h"
#include <QTimer>
#include <QRandomGenerator>

using Qt::StringLiterals::operator""_s;

TimeBanner::TimeBanner(QObject *parent)
	: QObject{parent}
{
	auto logger = HeLogger::logger();
	logger->info("正在初始化时间横幅", staticMetaObject.className());

	logger->info("正在初始化计时器...", staticMetaObject.className());
	m_timerHeartBeat = new QTimer(this);
	m_timerHeartBeat->setInterval(heartBeeatInterval);
	connect(m_timerHeartBeat, &QTimer::timeout, this, &TimeBanner::updateTime);

	m_timerSloganDuration = new QTimer(this);
	m_timerSloganDuration->setInterval(sloganDuration);
	connect(m_timerSloganDuration, &QTimer::timeout, this, &TimeBanner::showTime);

	m_timerTimeDuration = new QTimer(this);
	m_timerTimeDuration->setInterval(QRandomGenerator::global()->bounded(10, 21) * 1000 * 60);
	connect(m_timerTimeDuration, &QTimer::timeout, this, &TimeBanner::showSlogan);
	logger->info("计时器初始化完成", staticMetaObject.className());

	logger->info("正在初始化标语选择器...", staticMetaObject.className());
	m_sloganProvider = new SloganProvider(this);
	logger->info("标语选择器初始化完成", staticMetaObject.className());

	logger->info("正在启动计时器...", staticMetaObject.className());
	m_timerHeartBeat->start();
	m_timerTimeDuration->start();

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

void TimeBanner::setSloganText(const QString& newSloganText)
{
	if (m_sloganText == newSloganText)
		return;
	m_sloganText = newSloganText;
	emit sloganTextChanged();
}

void TimeBanner::updateTime()
{
	auto curTime = QTime::currentTime();
	setTimeText(curTime.toString("HH:mm:ss"));
}

void TimeBanner::showSlogan()
{
	m_timerTimeDuration->stop();
	auto str = m_sloganProvider->getSlogan();
	if (str != "")
		setSloganText(str);
	setStateString(States::ShowSlogan);
	m_timerSloganDuration->start();
}

void TimeBanner::showTime()
{
	m_timerSloganDuration->stop();
	setStateString(States::ShowTime);
	m_timerTimeDuration->setInterval(QRandomGenerator::global()->bounded(10, 21) * 1000 * 60);
	m_timerTimeDuration->start();
}
