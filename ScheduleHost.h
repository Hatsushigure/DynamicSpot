#pragma once
#include <QObject>
#include <QFile>
#include <QSet>
#include <QList>
#include "ScheduleItem.h"

class ScheduleHost : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
	Q_PROPERTY(ScheduleItem* currentItem READ currentItem NOTIFY currentItemChanged)
	friend class ScheduleTestWidget;
private:
	QList<ScheduleItem*> m_itemLst {};
	QSet<QTimer*> m_timerSet {};
	QString m_fileName {""};
	int m_currentIndex {-1};
public:
	explicit ScheduleHost(QObject *parent = nullptr);
public:
	QString fileName() const;
	void setFileName(const QString& newFileName);
	int currentIndex() const;
	ScheduleItem* currentItem() const;
public:
	void readFromFile();
	void readFromFile(const QString& fileName);
private:
	void updateCurrentIndex(QTimer* timer, const int index);
public slots:
	void clearItems();
signals:
	void currentIndexChanged();
	void currentItemChanged();
};

