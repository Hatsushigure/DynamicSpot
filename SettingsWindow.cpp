#include "SettingsWindow.h"
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <DynamicSpot.h>
#include <spdlog/logger.h>

using Qt::Literals::operator""_s;

SettingsWindow::SettingsWindow(QObject *parent)
	: QObject{parent}
{

}

void SettingsWindow::initWindow()
{
	DynamicSpot::logger->debug("正在创建设置窗口...");
	if (m_engine == nullptr)
		m_engine = new QQmlEngine(this);
	if (m_settingsWindow != nullptr)
		return;
	DynamicSpot::logger->debug("正在加载 ui 文件 \"{}\"...", uiSource);
	auto component = new QQmlComponent(m_engine, QUrl(uiSource.data()), QQmlComponent::PreferSynchronous, this);
	DynamicSpot::logger->debug("文件已加载");
	m_settingsWindow = static_cast<QQuickWindow*>(component->create());
	m_settingsWindow->setIcon(QIcon(":/DynamicSpot/images/icons/dynamicspot-settings.svg"));
	connect(m_settingsWindow, &QQuickWindow::closing, this, [this]() {
		DynamicSpot::logger->debug("设置窗口关闭");
		delete m_settingsWindow;
		m_settingsWindow = nullptr;
	});
}

void SettingsWindow::show()
{
	initWindow();
	DynamicSpot::logger->debug("正在显示设置窗口...");
	m_settingsWindow->show();
	m_settingsWindow->raise();
}
