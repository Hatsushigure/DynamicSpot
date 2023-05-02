#pragma once
#include <QWidget>

class QLineEdit;
class QSpinBox;
class QLabel;
class QPushButton;
class QGridLayout;

class ScheduleTestWidget : public QWidget
{
	Q_OBJECT
private:
	QLineEdit* m_lineEditIconFileName {nullptr};
	QLabel* m_lblIconFileName {nullptr};
	QLineEdit* m_lineEditTitle {nullptr};
	QLabel* m_lblTitle {nullptr};
	QLineEdit* m_lineEditSubtitle {nullptr};
	QLabel* m_lblSubtitle {nullptr};
	QSpinBox* m_spinDurationSeconds {nullptr};
	QLabel* m_lblDurationSeconds {nullptr};
	QPushButton* m_btnEmit {nullptr};
	QGridLayout* m_layout {nullptr};
public:
	ScheduleTestWidget();
private:
	void initUi();
	void initConnection();
private slots:
	void emitScheduleItem();
signals:
};

