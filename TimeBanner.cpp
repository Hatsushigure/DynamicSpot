#include "TimeBanner.h"
#include "SloganProvider.h"
#include "ConfigManager.h"
#include <QTimer>
#include <QRandomGenerator>
#include "DynamicSpot.h"
#include <spdlog/logger.h>

TimeBanner::TimeBanner(QObject *parent)
	: QObject{parent}
{
	auto logger = DynamicSpot::logger;
	logger->debug("正在初始化时间横幅");

	logger->debug("正在初始化计时器...");
	m_timerHeartBeat = new QTimer(this);
	m_timerHeartBeat->setInterval(heartBeeatInterval);
	connect(m_timerHeartBeat, &QTimer::timeout, this, &TimeBanner::updateTime);

	m_timerSloganDuration = new QTimer(this);
	m_timerSloganDuration->setInterval(sloganDuration);
	connect(m_timerSloganDuration, &QTimer::timeout, this, &TimeBanner::showTime);

	m_timerTimeDuration = new QTimer(this);
	m_timerTimeDuration->setInterval(QRandomGenerator::global()->bounded(10, 21) * 1000 * 60);
	connect(m_timerTimeDuration, &QTimer::timeout, this, &TimeBanner::showSlogan);

	m_timerScheduleDuration = new QTimer(this);
	m_timerScheduleDuration->setSingleShot(true);
	connect(m_timerScheduleDuration, &QTimer::timeout, this, &TimeBanner::showTime);
	logger->debug("计时器初始化完成");

	logger->debug("正在初始化标语选择器...");
	m_sloganProvider = new SloganProvider(this);
	logger->debug("标语选择器初始化完成");

	logger->debug("正在初始化 Schedule Host...");
	connect(scheduleHost(), &ScheduleHost::currentIndexChanged, this, &TimeBanner::showSchedule);
	logger->debug("Schedule Host 初始化完成");

	logger->debug("正在启动计时器...");
	m_timerHeartBeat->start();
	m_timerTimeDuration->start();

	logger->debug("时间横幅初始化完成");
}

void TimeBanner::setTimeText(const QString& newTimeText)
{
	if (newTimeText == m_timeText)
		return;
	m_timeText = newTimeText;
	emit timeTextChanged();
}

void TimeBanner::setState(const States newState)
{
	if (newState == m_state)
		return;
	m_state = newState;
	emit stateChanged();
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
	if (!DynamicSpot::configManager->enableSlogan())
	{
		DynamicSpot::logger->debug("Slogan is disabled, doing nothing");
		return;
	}
	m_timerTimeDuration->stop();
	auto str = m_sloganProvider->getSlogan();
	if (str != "")
		setSloganText(str);
	setState(States::ShowSlogan);
	m_timerSloganDuration->start();
}

void TimeBanner::showTime()
{
	m_timerSloganDuration->stop();
	setState(States::ShowTime);
	m_timerTimeDuration->setInterval(QRandomGenerator::global()->bounded(10, 21) * 1000 * 60);
	m_timerTimeDuration->start();
}

void TimeBanner::showSchedule()
{
	m_timerTimeDuration->stop();
	m_timerSloganDuration->stop();
	setState(States::ShowSchedule);
	m_timerScheduleDuration->start(scheduleHost()->currentItem()->durationSeconds() * 1000);
}
