#pragma once
#include <QObject>
#include <QtQmlIntegration>
#include "ScheduleHost.h"

class ScheduleHost;
class SloganProvider;

class TimeBanner : public QObject
{
	Q_OBJECT
	QML_NAMED_ELEMENT(TimeBannerBase)
	Q_PROPERTY(ScheduleHost* scheduleHost READ scheduleHost CONSTANT)
	Q_PROPERTY(SloganProvider* sloganProvider READ sloganProvider CONSTANT)
	Q_PROPERTY(QString timeText READ timeText WRITE setTimeText NOTIFY timeTextChanged)
	Q_PROPERTY(QString stateString READ stateString NOTIFY stateStringChanged CONSTANT);
public:
	enum class States {ShowSlogan, ShowSchedule, ShowTime};
private:
	const int heartBeeatInterval {500};
	const int sloganDuration {60 * 1000};
private:
	SloganProvider* m_sloganProvider {nullptr};
	QString m_timeText {""};
	QTimer* m_timerHeartBeat {nullptr};
	QTimer* m_timerSloganDuration {nullptr};
	States m_state {States::ShowTime};
	QString m_stateString {"showTime"};
public:
	explicit TimeBanner(QObject *parent = nullptr);
public:
	auto scheduleHost() const {return ScheduleHost::instance();}
	auto sloganProvider() const {return m_sloganProvider;}
	void setTimeText(const QString& newTimeText);
	auto timeText() const {return m_timeText;}
	auto stateString() const {return m_stateString;}
	void setStateString(const States newState);
private slots:
	void updateTime();
public slots:
	void showSlogan();
	void showTime();
	void showSchedule();
signals:
	void timeTextChanged();
	void stateStringChanged();
};
