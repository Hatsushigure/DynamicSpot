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
	initView();
	initItem();
	initTimer();
	adjustGeometry();
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
}

void MyMainWindow::adjustGeometry()
{
	resize(m_container->width(), m_container->height());
	QScreen* scr = DynamicSpot::theApp->primaryScreen();
	move((scr->size().width() - width()) / 2, 0);
}

void MyMainWindow::adjustcolor()
{
	QRect geometry(m_container->mapToGlobal(QPointF(0, 0)).toPoint(), m_container->size().toSize());
	auto col = MyAutoColorHelper::getColorFromGeometry(geometry, this->screen());
	HeLogger::info(QString("获取到颜色: hsv(%1, %2, %3)")
				   .arg(col.hsvHueF())
				   .arg(col.hsvSaturationF())
				   .arg(col.valueF()),
				   "MyMainWindow");
	auto contrastColor = MyAutoColorHelper::getContrastColor(col);
	m_rootItem->setProperty("textColor", contrastColor);
}

void MyMainWindow::startBackgroundTest()
{
	QColorDialog* dialog = new QColorDialog;
	dialog->setOptions(QColorDialog::ShowAlphaChannel | QColorDialog::NoButtons);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	dialog->setAttribute(Qt::WA_QuitOnClose, false);
	connect(dialog, &QColorDialog::currentColorChanged, this, &MyMainWindow::setClearColor);
	dialog->show();
}
