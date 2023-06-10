#include "ScheduleTestWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <DynamicSpot.h>
#include "ScheduleHost.h"
#include "ScheduleItem.h"

ScheduleTestWidget::ScheduleTestWidget()
	: QWidget{nullptr}
{
	initUi();
	initConnection();
}

void ScheduleTestWidget::initUi()
{
	m_layout = new QGridLayout(this);
	m_layout->setContentsMargins(16, 16, 16, 16);
	m_layout->setHorizontalSpacing(4);
	m_layout->setVerticalSpacing(8);

	m_lblIconFileName = new QLabel("图标路径", this);
	m_layout->addWidget(m_lblIconFileName, 0, 0);

	m_lineEditIconFileName = new QLineEdit("qrc:///DynamicSpot/images/icons/dynamicspot-logo.svg", this);
	m_layout->addWidget(m_lineEditIconFileName, 0, 1);

	m_lblTitle = new QLabel("标题", this);
	m_layout->addWidget(m_lblTitle, 1, 0);

	m_lineEditTitle = new QLineEdit(this);
	m_layout->addWidget(m_lineEditTitle, 1, 1);

	m_lblSubtitle = new QLabel("副标题", this);
	m_layout->addWidget(m_lblSubtitle, 2, 0);

	m_lineEditSubtitle = new QLineEdit(this);
	m_layout->addWidget(m_lineEditSubtitle, 2, 1);

	m_lblCommandline = new QLabel("命令行", this);
	m_layout->addWidget(m_lblCommandline, 3, 0);

	m_lineEditCommandline = new QLineEdit(this);
	m_layout->addWidget(m_lineEditCommandline, 3, 1);

	m_lblDurationSeconds = new QLabel("持续时长", this);
	m_layout->addWidget(m_lblDurationSeconds, 4, 0);

	m_spinDurationSeconds = new QSpinBox(this);
	m_spinDurationSeconds->setMinimum(1);
	m_spinDurationSeconds->setMaximum(20);
	m_layout->addWidget(m_spinDurationSeconds, 4, 1);

	m_btnEmit = new QPushButton("发送", this);
	m_layout->addWidget(m_btnEmit, 5, 0, 1, 2, Qt::AlignHCenter);
}

void ScheduleTestWidget::initConnection()
{
	connect(m_btnEmit, &QPushButton::clicked, this, &ScheduleTestWidget::emitScheduleItem);
}

void ScheduleTestWidget::emitScheduleItem()
{
	auto scheduleHost = ScheduleHost::instance();
	scheduleHost->m_itemLst.push_front(new ScheduleItem(
										   QTime(),
										   m_lineEditTitle->text(),
										   m_lineEditSubtitle->text(),
										   m_lineEditIconFileName->text(),
										   m_spinDurationSeconds->value(),
										   m_lineEditCommandline->text()
										   ));
	scheduleHost->m_currentIndex = 0;
	emit scheduleHost->currentItemChanged();
	emit scheduleHost->currentIndexChanged();
}

