#include "ScheduleItem.h"

ScheduleItem::ScheduleItem()
{

}

ScheduleItem::ScheduleItem(const QTime& time,
						   const QString& title,
						   const QString& subtitle,
						   const QString& iconFileName,
						   const int durationSeconds,
						   const QString& commandLine
						   ) :
	m_time(time),
	m_title(title),
	m_subtitle(subtitle),
	m_iconFileName(iconFileName),
	m_durationSeconds(durationSeconds),
	m_commandLine(commandLine)
{
}

QTime ScheduleItem::time() const
{
	return m_time;
}

void ScheduleItem::setTime(const QTime& newTime)
{
	m_time = newTime;
}

QString ScheduleItem::title() const
{
	return m_title;
}

void ScheduleItem::setTitle(const QString& newTitle)
{
	if (m_title == newTitle)
		return;
	m_title = newTitle;
	emit titleChanged();
}

QString ScheduleItem::subtitle() const
{
	return m_subtitle;
}

void ScheduleItem::setSubtitle(const QString& newSubtitle)
{
	if (m_subtitle == newSubtitle)
		return;
	m_subtitle = newSubtitle;
	emit subtitleChanged();
}

QString ScheduleItem::iconFileName() const
{
	return m_iconFileName;
}

void ScheduleItem::setIconFileName(const QString& newIconFileName)
{
	if (m_iconFileName == newIconFileName)
		return;
	m_iconFileName = newIconFileName;
	emit iconFileNameChanged();
}

int ScheduleItem::durationSeconds() const
{
	return m_durationSeconds;
}

void ScheduleItem::setDurationSeconds(const int newDurationSeconds)
{
	if (m_durationSeconds == newDurationSeconds)
		return;
	m_durationSeconds = newDurationSeconds;
	emit durationSecondsChanged();
}

QString ScheduleItem::commandLine() const
{
	return m_commandLine;
}

void ScheduleItem::setCommandLine(const QString& newCommandLine)
{
	if (m_commandLine == newCommandLine)
		return;
	m_commandLine = newCommandLine;
	emit commandLineChanged();
}
