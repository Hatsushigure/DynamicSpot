#pragma once
#include <QQuickPaintedItem>
#include <QtQmlIntegration>

class QSvgRenderer;

class HeSvgItem : public QQuickPaintedItem
{
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
	Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ aspectRatioMode WRITE setAspectRatioMode NOTIFY aspectRatioModeChanged)
private:
	QSvgRenderer* m_renderer;
	QString m_source;
	Qt::AspectRatioMode m_aspectRatioMode {Qt::IgnoreAspectRatio};

public:
	HeSvgItem();
public:
	QString source() const {return m_source;}
	void setSource(const QString& newSource);
	Qt::AspectRatioMode aspectRatioMode() const {return m_aspectRatioMode;}
	void setAspectRatioMode(Qt::AspectRatioMode newAspectRatioMode);
public:
	void paint(QPainter *painter);
private slots:
	void onSourceChanged();
	void onAspectRatioChanged();
signals:
	void sourceChanged();
	void aspectRatioModeChanged();
};

