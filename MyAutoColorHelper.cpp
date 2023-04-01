#include "MyAutoColorHelper.h"
#include <QWidget>
#include <QScreen>
#include <QRandomGenerator>

int MyAutoColorHelper::m_sampleCount = defaultSampleCount;

int MyAutoColorHelper::sampleCount()
{
	return m_sampleCount;
}

void MyAutoColorHelper::setSampleCount(const int val)
{
	m_sampleCount = val;
}

QColor MyAutoColorHelper::getColorFromPixmap(const QPixmap& target)
{
	return getColorFromImage(target.toImage());
}

QColor MyAutoColorHelper::getColorFromImage(const QImage& target)
{
	QList<QPoint> pntList;
	pntList.resize(m_sampleCount);
	for (auto& pnt : pntList)
	{
		pnt.setX(QRandomGenerator::global()->bounded(target.width()));
		pnt.setY(QRandomGenerator::global()->bounded(target.height()));
	}

	QList<QRgb> colorList;
	colorList.resize(m_sampleCount);
	for (int i = 0; i < m_sampleCount; i++)
		colorList[i] = target.pixel(pntList[i]);

	long long r = 0, g = 0, b = 0;
	for (const auto& col : colorList)
	{
		r += qRed(col);
		g += qGreen(col);
		b += qBlue(col);
	}
	r /= m_sampleCount;
	g /= m_sampleCount;
	b /= m_sampleCount;

	return QColor::fromRgb(r, g, b);
}

QColor MyAutoColorHelper::getColorFromGeometry(const QRect& globalGometry, QScreen* screen)
{
	QPixmap pix = screen->grabWindow(WId(), globalGometry.x(), globalGometry.y(), globalGometry.width(), globalGometry.height());
	return getColorFromPixmap(pix);
}

QColor MyAutoColorHelper::getColorFromWidget(const QWidget* target)
{
	QRect geometry = target->geometry();
	geometry.moveTopLeft(target->mapToGlobal(geometry.topLeft()));
	QScreen* scr = target->screen();
	return getColorFromGeometry(geometry, scr);
}

QColor MyAutoColorHelper::reverseColor(const QColor& color)
{
	double r =	color.redF();
	double g = color.greenF();
	double b = color.blueF();
	return QColor(1 - r, 1 - g, 1 - b);
}

QColor MyAutoColorHelper::getContrastColor(const QColor& col)
{
	if (col.valueF() < 0.3 || col.hsvSaturationF() < 0.3)
		return QColor::fromHsvF(0.5, 1, 1);
	double h = col.hsvHueF() < 0.5 ? col.hsvHueF() + 0.5 : col.hsvHueF() - 0.5;
	return QColor::fromHsvF(h, 1, 1);
}

QColor MyAutoColorHelper::getContrastColor1(const QColor& col)
{
	double r = col.redF() < 0.5 ? 1 : 0;
	double g = col.greenF() < 0.5 ? 1 : 0;
	double b = col.blueF() < 0.5 ? 1 : 0;
	return QColor::fromRgbF(r, g, b);
}
