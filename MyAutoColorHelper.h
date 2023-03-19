#pragma once
#include <QColor>
#include <QImage>

class QWidget;
class QScreen;

class MyAutoColorHelper
{
private:
	const static int defaultSampleCount = 16;
private:
	static int m_sampleCount;
public:
	MyAutoColorHelper() = default;
public:
	static int sampleCount();
	static void setSampleCount(const int val);
public:
	static QColor getColorFromPixmap(const QPixmap& target);
	static QColor getColorFromImage(const QImage& target);
	static QColor getColorFromGeometry(const QRect& globalGometry, QScreen* screen);
	static QColor getColorFromWidget(const QWidget* target);
	static QColor reverseColor(const QColor& color);
};

