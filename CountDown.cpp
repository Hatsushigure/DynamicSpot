#include "CountDown.h"
#include <QSettings>
#include <format>
#include <spdlog/logger.h>
#include "DynamicSpot.h"

CountDown::CountDown(QObject *parent)
	: QObject{parent}
{
	auto logger = DynamicSpot::logger;
	logger->debug("正在初始化倒计时窗体");

	if (DynamicSpot::settings->value(DynamicSpot::SettingsKey::enableSecondCountDown).toBool())
	{
		logger->info("检测到启用了精确到秒的倒计时");
		m_countDownMode = CountDownMode::SecondCountDown;
	}
	auto deadlineString = DynamicSpot::settings->value(DynamicSpot::SettingsKey::deadline).toString();
	m_deadline = QDateTime::fromString(deadlineString, "yyyy-MM-dd_HH-mm-ss");

	updateAllTexts();

	logger->info("正在初始化状态切换计时器, 周期 {}ms", changeStateInterval);
	m_timerChangeState = new QTimer(this);
	m_timerChangeState->setInterval(changeStateInterval);
	connect(m_timerChangeState, &QTimer::timeout, this, &CountDown::toggleState);
	logger->debug("状态切换计时器初始化完成", staticMetaObject.className());

	auto heartBeatInterval = m_countDownMode == CountDownMode::DayCountDown ? dayCountDownHeartBeat : secondCountDownHeartBeat;
	logger->info("正在初始化 timerHeartBeat, 周期 {}ms", heartBeatInterval);
	m_timerHeartBeat = new QTimer(this);
	m_timerHeartBeat->setInterval(heartBeatInterval);
	connect(m_timerHeartBeat, &QTimer::timeout, this, &CountDown::updateAllTexts);
	logger->debug("timerHeartBeat 初始化完成", staticMetaObject.className());

	logger->debug("正在启动计时器...", staticMetaObject.className());
	m_timerHeartBeat->start();
	m_timerChangeState->start();

	DynamicSpot::countDown = this;
	logger->debug("倒计时窗体初始化完成", staticMetaObject.className());
}

void CountDown::setShortText(const QString& newShortText)
{
	if (m_shortText == newShortText)
		return;
	m_shortText = newShortText;
	emit shortTextChanged();
}

void CountDown::setFullText(const QString& newFullText)
{
	if (newFullText == m_fullText)
		return;
	m_fullText = newFullText;
	emit fullTextChanged();
}

void CountDown::setState(const States newState)
{
	if (newState == m_state)
		return;
	m_state = newState;
	switch (newState)
	{
	case States::ShowShort:
		m_stateString = "showShort";
		break;
	case States::ShowFull:
		m_stateString = "showFull";
		break;
	}
	emit stateChanged();
}

void CountDown::updateAllTexts()
{
	auto curDateTime = QDateTime::currentDateTime();
	setShortText(std::format(shortTextTemplate, curDateTime.daysTo(m_deadline)).c_str());
	switch (m_countDownMode)
	{
	case CountDownMode::DayCountDown:
		setFullText(std::format(dayCoundDownTemplate, curDateTime.daysTo(m_deadline)).c_str());
		break;
	case CountDownMode::SecondCountDown:
		setFullText(std::format(secondCoundDownTemplate, curDateTime.secsTo(m_deadline)).c_str());
		break;
	}
}

void CountDown::toggleState()
{
	if (m_state == States::ShowFull)
		setState(States::ShowShort);
	else
		setState(States::ShowFull);
}
