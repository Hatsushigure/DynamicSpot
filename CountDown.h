#pragma once
#include <QObject>
#include <QtQmlIntegration>
#include <QDateTime>

class CountDown : public QObject
{
	Q_OBJECT
	QML_NAMED_ELEMENT(CountDownBase)
	Q_PROPERTY(QString shortText READ shortText WRITE setShortText NOTIFY shortTextChanged)
	Q_PROPERTY(QString fullText READ fullText WRITE setFullText NOTIFY fullTextChanged);
	Q_PROPERTY(States state READ state NOTIFY stateChanged CONSTANT)
public:
	enum class CountDownMode {SecondCountDown, DayCountDown};
	enum class States {ShowShort, ShowFull};
	Q_ENUM(States)
private:
	const int changeStateInterval {300000};
	const int secondCountDownHeartBeat {500};
	const int dayCountDownHeartBeat {60000};
	const QString shortTextTemplate {"<span style=\"color: red; font-weight: bold\">%1</span>"};
	const QString secondCoundDownTemplate {"距离高考仅剩 <span style=\"color:red;font-weight:bold\">%1</span> 秒"};
	const QString dayCoundDownTemplate {"距离高考仅剩 <span style=\"color:red;font-weight:bold\">%1</span> 天"};
private:
	QDateTime m_deadline {};
	QString m_shortText {shortTextTemplate};
	QString m_fullText {dayCoundDownTemplate};
	QString m_stateString {"showShort"};
	CountDownMode m_countDownMode {CountDownMode::DayCountDown};
	States m_state {States::ShowShort};
	QTimer* m_timerChangeState {nullptr};
	QTimer* m_timerHeartBeat {nullptr};
public:
	explicit CountDown(QObject *parent = nullptr);
public:
	auto shortText() const {return m_shortText;}
	void setShortText(const QString& newShortText);
	auto fullText() const {return m_fullText;}
	void setFullText(const QString& newFullText);
	void setState(const States newState);
	auto state() const {return m_state;}
private slots:
	void updateAllTexts();
	void toggleState();
signals:
	void shortTextChanged();
	void fullTextChanged();
	void stateChanged();
};

