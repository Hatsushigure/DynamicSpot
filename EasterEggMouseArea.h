#pragma once
#include <QObject>
#include <QtQmlIntegration>

class QTimer;

namespace DynamicSpot
{
class EasterEggMouseArea : public QObject
{
	Q_OBJECT
	QML_NAMED_ELEMENT(EasterEggMouseAreaBase)
	Q_PROPERTY(bool activated READ activated NOTIFY activatedChanged)
private:
	static constexpr auto timeLimit {1};
	static constexpr auto minClickCount {5};
private:
	bool m_activated {false};
	bool m_activating {false};
	int m_clickCount {0};
	QTimer* m_clickTimer {};
public:
	explicit EasterEggMouseArea(QObject* parent = nullptr);
public:
	auto activated() const {return m_activated;}
private:
	void setActivated(bool flag);
signals:
	void activatedChanged();
public slots:
	void click();
	void restore();
};
}
