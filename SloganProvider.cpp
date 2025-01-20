#include "SloganProvider.h"
#include <QTimer>
#include <QRandomGenerator>
#include "DynamicSpot.h"
#include <spdlog/logger.h>

using Qt::Literals::operator""_s;

SloganProvider::SloganProvider(QObject *parent)
	: QObject{parent}
{
	// auto tmr = new QTimer;
	// tmr->setInterval(0);
	// connect(tmr, &QTimer::timeout, this, &SloganProvider::init);
	// connect(tmr, &QTimer::timeout, this, [tmr]() {delete tmr;});
	// tmr->start();
	init();
}

QString SloganProvider::getSlogan() const
{
	auto logger = DynamicSpot::logger;
	if (m_sloganList.isEmpty())
	{
		logger->warn("标语列表为空, 显示默认标语");
		return "";
	}
	auto index = QRandomGenerator::global()->bounded(m_sloganList.size());
	auto str = m_sloganList.at(index);
	logger->info("选择了标语: {}", str.toStdString());
	return str;
}

void SloganProvider::readFile()
{
	auto logger = DynamicSpot::logger;
	logger->debug("正在读取标语文件...");
	if (!m_sloganFile->exists())
	{
		logger->warn("标语文件不存在, 显示默认标语");
		return;
	}
	if (!m_sloganFile->open(QFile::ReadOnly | QFile::Text))
	{
		logger->error("无法打开标语文件, 请检查是否有相应权限");
		return;
	}
	m_sloganFile->open(QFile::ReadOnly | QFile::Text);
	while (!m_sloganFile->atEnd())
	{
		auto str = m_sloganFile->readLine();
		logger->info("读取到标语: {}", str.toStdString());
		m_sloganList.append(str);
	}
	m_sloganFile->close();
}

void SloganProvider::init()
{
	m_sloganFile = new QFile(sloganFileName, this);
	readFile();
}
