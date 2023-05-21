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
private:
	SloganProvider* m_sloganProvider {nullptr};
public:
	explicit TimeBanner(QObject *parent = nullptr);
public:
	ScheduleHost* scheduleHost() const {return ScheduleHost::instance();}
	SloganProvider* sloganProvider() const {return m_sloganProvider;}
};
