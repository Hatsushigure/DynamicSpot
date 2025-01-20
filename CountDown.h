#pragma once
#include <QObject>
#include <QtQmlIntegration>
#include <QDateTime>
#include <string_view>

class CountDown : public QObject
{
	Q_OBJECT
	QML_NAMED_ELEMENT(CountDownBase)
	Q_PROPERTY(QString shortText READ shortText WRITE setShortText NOTIFY shortTextChanged)
	Q_PROPERTY(QString fullText READ fullText WRITE setFullText NOTIFY fullTextChanged);
	Q_PROPERTY(States state READ state NOTIFY stateChanged CONSTANT)
	Q_PROPERTY(int uiPadding READ uiPadding CONSTANT)
public:
	enum class CountDownMode {SecondCountDown, DayCountDown};
	enum class States {ShowShort, ShowFull};
	Q_ENUM(States)
private:
	static constexpr auto changeStateInterval {300000};
	static constexpr auto secondCountDownHeartBeat {500};
	static constexpr auto dayCountDownHeartBeat {60000};
	static constexpr auto uiPaddingVal {8};
	static constexpr std::string_view shortTextTemplate {"<span style=\"color: red; font-weight: bold\">{}</span>"};
	static constexpr std::string_view secondCoundDownTemplate {"距离高考仅剩 <span style=\"color:red;font-weight:bold\">{}</span> 秒"};
	static constexpr std::string_view dayCoundDownTemplate {"距离高考仅剩 <span style=\"color:red;font-weight:bold\">{}</span> 天"};
private:
	QDateTime m_deadline {};
	QString m_shortText {""};
	QString m_fullText {""};
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
	auto uiPadding() const {return uiPaddingVal;}
private slots:
	void updateAllTexts();
	void toggleState();
signals:
	void shortTextChanged();
	void fullTextChanged();
	void stateChanged();
};

