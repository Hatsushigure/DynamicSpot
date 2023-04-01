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

	double r = 0, g = 0, b = 0;
	for (auto& col : colorList)
	{
		r += (qRed(col) / m_sampleCount);
		g += (qGreen(col) / m_sampleCount);
		b += (qBlue(col) / m_sampleCount);
	}

	return QColor(r, g, b);
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
	if (col.hsvSaturationF() < 0.1)	//this means it is so close to gray that the hue may not be useful
		return QColor::fromHsvF(0.5, 1, 1);
	QColor newCol = reverseColor(col);
	double h = newCol.hsvHueF() < 0.5 ? newCol.hsvHueF() + 0.5 : newCol.hsvHueF() - 0.5;
	newCol.setHsvF(h, 1, 1);
	return newCol;
}

QColor MyAutoColorHelper::getContrastColor1(const QColor& col)
{
	QColor newCol(col);
	newCol.setRed(newCol.redF() < 0.5 ? 1 : 0);
	newCol.setGreen(newCol.greenF() < 0.5 ? 1 : 0);
	newCol.setBlue(newCol.blueF() < 0.5 ? 1 : 0);
	return newCol;
}
