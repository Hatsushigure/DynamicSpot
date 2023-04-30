#pragma once
#include <QObject>

class QQuickWindow;
class QQmlEngine;

class SettingsWindow : public QObject
{
	Q_OBJECT
private:
	const QString uiSource {"qrc:///DynamicSpot/qml/SettingsWindow.qml"};
private:
	QQuickWindow* m_settingsWindow {nullptr};
	QQmlEngine* m_engine {nullptr};
public:
	explicit SettingsWindow(QObject *parent = nullptr);
public:
	void initWindow();
public slots:
	void show();
signals:
};

