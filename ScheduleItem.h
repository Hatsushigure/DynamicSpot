#pragma once
#include <QObject>
#include <QTime>
#include <QtQmlIntegration>

class ScheduleItem : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)
	Q_PROPERTY(QString iconFileName READ iconFileName WRITE setIconFileName NOTIFY iconFileNameChanged)
	Q_PROPERTY(int durationSeconds READ durationSeconds WRITE setDurationSeconds NOTIFY durationSecondsChanged)
	Q_PROPERTY(QString commandLine READ commandLine WRITE setCommandLine NOTIFY commandLineChanged)
private:
	QTime m_time {};
	QString m_title {"No Title"};
	QString m_subtitle {""};
	QString m_iconFileName {"qrc:/DynamicSpot/images/icons/colored/info.svg"};
	int m_durationSeconds {10};
	QString m_commandLine {""};

public:
	ScheduleItem();
	ScheduleItem(const QTime& time,
				 const QString& title,
				 const QString& subtitle,
				 const QString& iconFileName,
				 const int durationSeconds,
				 const QString& commandLine
				 );
public:
	QTime time() const;
	void setTime(const QTime& newTime);
	QString title() const;
	void setTitle(const QString& newTitle);
	QString subtitle() const;
	void setSubtitle(const QString& newSubtitle);
	QString iconFileName() const;
	void setIconFileName(const QString& newIconFileName);
	int durationSeconds() const;
	void setDurationSeconds(const int newDurationSeconds);
	QString commandLine() const;
	void setCommandLine(const QString& newCommandLine);

signals:
	void titleChanged();
	void subtitleChanged();
	void iconFileNameChanged();
	void durationSecondsChanged();
	void commandLineChanged();
};
