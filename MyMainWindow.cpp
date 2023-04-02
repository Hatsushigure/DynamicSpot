#include "MyMainWindow.h"
#include "DynamicSpot.h"
#include "DynamicSpotApp.h"
#include "HeLogger.h"
#include "MyAutoColorHelper.h"
#include "HeLogger.h"
#include <QQuickItem>
#include <QTimer>
#include <QColorDialog>

MyMainWindow::MyMainWindow(QWidget *parent) :
	QQuickWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	setFocusPolicy(Qt::NoFocus);
	initView();
	initItem();
	initTimer();
	adjustGeometry();
	connect(this, &MyMainWindow::daysLeftChanged, this, &MyMainWindow::updateCountDownText);
}

int MyMainWindow::daysLeft() const
{
	return m_daysLeft;
}

void MyMainWindow::setDaysLeft(int newDaysLeft)
{
	if (m_daysLeft == newDaysLeft)
		return;
	m_daysLeft = newDaysLeft;
	emit daysLeftChanged();
}

void MyMainWindow::initView()
{
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setSource(uiSource);
	HeLogger::info("加载了 ui 文件 " + uiSource, "MyMainWindow");
	setClearColor(Qt::transparent);
}

void MyMainWindow::initItem()
{
	m_rootItem = rootObject();

	m_container = m_rootItem->findChild<QQuickItem*>("container");
	connect(m_container, &QQuickItem::widthChanged, this, &MyMainWindow::adjustGeometry);
	connect(m_container, &QQuickItem::heightChanged, this, &MyMainWindow::adjustGeometry);

	m_timeBanner = m_container->findChild<QQuickItem*>("timeBanner");
	m_countDown = m_container->findChild<QQuickItem*>("countDown");
}

void MyMainWindow::initTimer()
{
	m_timerAdjustColor = new QTimer(this);
	m_timerAdjustColor->setInterval(500);
	connect(m_timerAdjustColor, &QTimer::timeout, this, &MyMainWindow::adjustcolor);
	m_timerAdjustColor->start();
	HeLogger::info("启动了切换颜色计时器, 周期 500 毫秒", "MyMainWindow");

	m_timerUpdateDate = new QTimer(this);
	m_timerUpdateDate->setInterval(10000);
	connect(m_timerUpdateDate, &QTimer::timeout, this, &MyMainWindow::updatedaysLeft);
	m_timerUpdateDate->start();
	HeLogger::info("启动了更新日期计时器, 周期 10000 毫秒", "MyMainWindow");
}

void MyMainWindow::adjustGeometry()
{
	if (m_container->width() > width() + 10)
		resize(m_container->width() + 10, height());
	if (m_container->height() > height() + 10)
		resize(width(), m_container->height() + 10);
	QScreen* scr = DynamicSpot::theApp->primaryScreen();
	move((scr->size().width() - width()) / 2, 0);
}

void MyMainWindow::adjustcolor()
{
	using Qt::StringLiterals::operator""_s;
	QRect geometry(m_container->mapToGlobal(QPointF(0, 0)).toPoint(), m_container->size().toSize());
	auto col = MyAutoColorHelper::getColorFromGeometry(geometry, this->screen());
	auto contrastColor = MyAutoColorHelper::getContrastColor(col);
	m_rootItem->setProperty("textColor", contrastColor);
}

void MyMainWindow::updatedaysLeft()
{
	setDaysLeft(deadline.toJulianDay() - QDate::currentDate().toJulianDay());
}

void MyMainWindow::updateCountDownText()
{
	using Qt::StringLiterals::operator""_s;
	HeLogger::info("检测到日期变化, 正在更新倒计时天数", "MyMainWindow");
	m_countDown->setProperty("shortText", u"<span style=\"color: red; font-weight: bold\">%1</span>"_s.arg(QString::number(daysLeft())));
	m_countDown->setProperty("fullText", u"距离高考仅剩 <span style=\"color: red; font-weight: bold\">%1</span> 天"_s.arg(QString::number(daysLeft())));
}

void MyMainWindow::startBackgroundTest()
{
	HeLogger::info("触发了调试自动颜色选项", "MyMainWindow");
	QColorDialog* dialog = new QColorDialog;
	dialog->setOptions(QColorDialog::ShowAlphaChannel | QColorDialog::NoButtons);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	dialog->setAttribute(Qt::WA_QuitOnClose, false);
	connect(dialog, &QColorDialog::currentColorChanged, this, &MyMainWindow::setClearColor);
	dialog->show();
	HeLogger::info("显示颜色对话框", "MyMainWindow");
}
