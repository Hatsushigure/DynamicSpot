#include "HeSvgItem.h"
#include <QSvgRenderer>
#include <QPainter>

HeSvgItem::HeSvgItem()
{
	m_renderer = new QSvgRenderer(this);
	connect(this, &HeSvgItem::sourceChanged, this, &HeSvgItem::onSourceChanged);
	connect(this, &HeSvgItem::aspectRatioModeChanged, this, &HeSvgItem::onAspectRatioChanged);
}

void HeSvgItem::paint(QPainter* painter)
{
	m_renderer->render(painter);
}

void HeSvgItem::onSourceChanged()
{
	m_renderer->load(source());
	update();
}

void HeSvgItem::onAspectRatioChanged()
{
	m_renderer->setAspectRatioMode(aspectRatioMode());
	update();
}

void HeSvgItem::setSource(const QString& newSource)
{
	if (m_source == newSource)
		return;
	m_source = newSource;
	emit sourceChanged();
}

void HeSvgItem::setAspectRatioMode(Qt::AspectRatioMode newAspectRatioMode)
{
	if (m_aspectRatioMode == newAspectRatioMode)
		return;
	m_aspectRatioMode = newAspectRatioMode;
	emit aspectRatioModeChanged();
}
