#include "EasterEggMouseArea.h"
#include "DynamicSpot.h"
#include <QTimer>
#include <spdlog/logger.h>

using DynamicSpot::EasterEggMouseArea;

EasterEggMouseArea::EasterEggMouseArea(QObject* parent)
	: QObject{parent}
{
	m_clickTimer = new QTimer(this);
	m_clickTimer->setInterval(timeLimit * 1000);
	m_clickTimer->setSingleShot(true);
	connect(m_clickTimer, &QTimer::timeout, this, &EasterEggMouseArea::restore);
}

void EasterEggMouseArea::setActivated(bool flag)
{
	if (flag == m_activated)
		return;
	m_activated = flag;
	emit activatedChanged();
}

void EasterEggMouseArea::click()
{
	if (activated())
		return;
	if (!m_activating)
	{
		m_activating = true;
		m_clickTimer->start();
	}
	m_clickCount++;
	DynamicSpot::logger->info("Easter egg mouse area got clicked {} time(s) in {} seconds", m_clickCount, timeLimit);
	if (m_clickCount < minClickCount)
		return;
	DynamicSpot::logger->info("Easter egg mouse area is activated");
	m_clickTimer->stop();
	m_activating = false;
	setActivated(true);
}

void EasterEggMouseArea::restore()
{
	DynamicSpot::logger->info("Restoring state of easter egg mouse area");
	m_activating = false;
	setActivated(false);
	m_clickCount = 0;
}
