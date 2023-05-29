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
	Q_PROPERTY(QString stateString READ stateString NOTIFY stateStringChanged CONSTANT)
public:
	enum class CountDownMode {SecondCountDown, DayCountDown};
	enum class States {ShowShort, ShowFull};
private:
	const int changeStateInterval {300000};
	const int secondCountDownHeartBeat {500};
	const int dayCountDownHeartBeat {60000};
	const QDateTime deadLine {QDate {2023, 6, 7}, QTime {9, 0 , 0}};
	const QString shortTextTemplate {"<span style=\"color: red; font-weight: bold\">%1</span>"};
	const QString secondCoundDownTemplate {"距离高考仅剩 <span style=\"color:red;font-weight:bold\">%1</span> 秒"};
	const QString dayCoundDownTemplate {"距离高考仅剩 <span style=\"color:red;font-weight:bold\">%1</span> 天"};
private:
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
	auto stateString() const {return m_stateString;}
	void setStateString(const States newState);
private slots:
	void updateAllTexts();
	void toggleState();
signals:
	void shortTextChanged();
	void fullTextChanged();
	void stateStringChanged();
};

