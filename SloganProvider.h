#pragma once
#include <QObject>
#include <QtQmlIntegration>

class QFile;

class SloganProvider : public QObject
{
	Q_OBJECT
	QML_ELEMENT
private:
	const QString sloganFileName {"./slogans.txt"};
private:
	QFile* m_sloganFile {};
	QList<QString> m_sloganList;
public:
	SloganProvider(QObject *parent = nullptr);
public:
	Q_INVOKABLE QString getSlogan() const;
private:
	void readFile();
private slots:
	void init();
};
