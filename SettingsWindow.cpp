#include "SettingsWindow.h"
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include "HeLogger.h"

using Qt::Literals::operator""_s;

SettingsWindow::SettingsWindow(QObject *parent)
	: QObject{parent}
{

}

void SettingsWindow::initWindow()
{
	HeLogger::info("正在创建设置窗口...", staticMetaObject.className());
	if (m_engine == nullptr)
		m_engine = new QQmlEngine(this);
	if (m_settingsWindow != nullptr)
		return;
	HeLogger::info(u"正在加载 ui 文件 \"%1\"..."_s.arg(uiSource), staticMetaObject.className());
	auto component = new QQmlComponent(m_engine, uiSource, QQmlComponent::PreferSynchronous, this);
	HeLogger::info("文件已加载", staticMetaObject.className());
	m_settingsWindow = static_cast<QQuickWindow*>(component->create());
	m_settingsWindow->setIcon(QIcon(":/DynamicSpot/images/icons/dynamicspot-settings-256.svg"));
	connect(m_settingsWindow, &QQuickWindow::closing, this, [=]() {
		HeLogger::info("设置窗口关闭", staticMetaObject.className());
		delete m_settingsWindow;
		m_settingsWindow = nullptr;
	});
}

void SettingsWindow::show()
{
	initWindow();
	HeLogger::info("正在显示设置窗口...", staticMetaObject.className());
	m_settingsWindow->show();
	m_settingsWindow->raise();
}
