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
private:
	SloganProvider* m_sloganProvider {nullptr};
	QString m_timeText {""};
	QTimer* m_timerChangeTime {nullptr};
public:
	explicit TimeBanner(QObject *parent = nullptr);
public:
	ScheduleHost* scheduleHost() const {return ScheduleHost::instance();}
	SloganProvider* sloganProvider() const {return m_sloganProvider;}
	void setTimeText(const QString& newTimeText);
	QString timeText() const {return m_timeText;}
private slots:
	void updateTime();
signals:
	void timeTextChanged();
};
