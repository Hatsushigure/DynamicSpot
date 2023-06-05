#include "CountDown.h"
#include "HeLogger.h"
#include <QSettings>
#include "DynamicSpot.h"

using Qt::StringLiterals::operator""_s;

CountDown::CountDown(QObject *parent)
	: QObject{parent}
{
	auto logger = HeLogger::logger();
	logger->info("正在初始化倒计时窗体", staticMetaObject.className());

	if (DynamicSpot::settings->value("enableSecondCountDown").toBool())
	{
		logger->info("检测到启用了精确到秒的倒计时");
		m_countDownMode = CountDownMode::SecondCountDown;
	}

	updateAllTexts();

	logger->info(u"正在初始化状态切换计时器, 周期 %1ms"_s.arg(QString::number(changeStateInterval)), staticMetaObject.className());
	m_timerChangeState = new QTimer(this);
	m_timerChangeState->setInterval(changeStateInterval);
	connect(m_timerChangeState, &QTimer::timeout, this, &CountDown::toggleState);
	logger->info("状态切换计时器初始化完成", staticMetaObject.className());

	auto heartBeatInterval = m_countDownMode == CountDownMode::DayCountDown ? dayCountDownHeartBeat : secondCountDownHeartBeat;
	logger->info(u"正在初始化 timerHeartBeat, 周期 %1ms"_s.arg(heartBeatInterval), staticMetaObject.className());
	m_timerHeartBeat = new QTimer(this);
	m_timerHeartBeat->setInterval(heartBeatInterval);
	connect(m_timerHeartBeat, &QTimer::timeout, this, &CountDown::updateAllTexts);
	logger->info("timerHeartBeat 初始化完成", staticMetaObject.className());

	logger->info("正在启动计时器...", staticMetaObject.className());
	m_timerHeartBeat->start();
	m_timerChangeState->start();

	DynamicSpot::countDown = this;
	logger->info("倒计时窗体初始化完成", staticMetaObject.className());
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

void CountDown::setStateString(const States newState)
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
	emit stateStringChanged();
}

void CountDown::updateAllTexts()
{
	auto curDateTime = QDateTime::currentDateTime();
	setShortText(shortTextTemplate.arg(curDateTime.daysTo(deadLine)));
	switch (m_countDownMode)
	{
	case CountDownMode::DayCountDown:
		setFullText(dayCoundDownTemplate.arg(curDateTime.daysTo(deadLine)));
		break;
	case CountDownMode::SecondCountDown:
		setFullText(secondCoundDownTemplate.arg(curDateTime.secsTo(deadLine)));
		break;
	}
}

void CountDown::toggleState()
{
	if (m_state == States::ShowFull)
		setStateString(States::ShowShort);
	else
		setStateString(States::ShowFull);
}
