#include "SloganProvider.h"
#include <QTimer>
#include <HeLogger.h>
#include <QRandomGenerator>

using Qt::Literals::operator""_s;

SloganProvider::SloganProvider(QObject *parent)
	: QObject{parent}
{
	auto tmr = new QTimer;
	tmr->setInterval(0);
	connect(tmr, &QTimer::timeout, this, &SloganProvider::init);
	connect(tmr, &QTimer::timeout, this, [tmr]() {delete tmr;});
	tmr->start();
}

QString SloganProvider::getSlogan() const
{
	auto logger = HeLogger::logger();
	if (m_sloganList.isEmpty())
	{
		logger->warning("标语列表为空, 显示默认标语", staticMetaObject.className());
		return "";
	}
	auto index = QRandomGenerator::global()->bounded(m_sloganList.size());
	return m_sloganList.at(index);
}

void SloganProvider::readFile()
{
	auto logger = HeLogger::logger();
	logger->info("正在读取标语文件...", staticMetaObject.className());
	if (!m_sloganFile->exists())
	{
		logger->warning("标语文件不存在, 显示默认标语", staticMetaObject.className());
		return;
	}
	if (!m_sloganFile->open(QFile::ReadOnly | QFile::Text))
	{
		logger->warning("无法打开标语文件, 请检查是否有相应权限", staticMetaObject.className());
		return;
	}
	m_sloganFile->open(QFile::ReadOnly | QFile::Text);
	while (!m_sloganFile->atEnd())
	{
		auto str = m_sloganFile->readLine();
		logger->info(u"读取到标语: %1"_s.arg(str));
		m_sloganList.append(str);
	}
}

void SloganProvider::init()
{
	m_sloganFile = new QFile(sloganFileName, this);
	readFile();
}
