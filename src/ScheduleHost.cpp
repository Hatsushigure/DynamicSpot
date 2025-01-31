#include "ScheduleHost.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include "DynamicSpot.h"
#include<spdlog/logger.h>

ScheduleHost* ScheduleHost::s_instance {nullptr};

QString ScheduleHost::fileName() const
{
	return m_fileName;
}

void ScheduleHost::setFileName(const QString& newFileName)
{
	m_fileName = newFileName;
}

ScheduleItem* ScheduleHost::currentItem() const
{
	if (m_currentIndex < 0)
		return nullptr;
	return m_itemLst.at(m_currentIndex);
}

void ScheduleHost::readFromFile()
{
	auto logger = DynamicSpot::logger;
	clearItems();

	if (m_fileName.isEmpty())
	{
		logger->warn("未指定文件名, 跳过读取");
		return;
	}
	QFile tmpFile(m_fileName);
	tmpFile.open(QFile::ReadOnly);
	if (!tmpFile.isOpen())
	{
		logger->error("无法打开文件, 请检查文件是否存在以及是否有相应权限");
		return;
	}

	QJsonParseError err;
	auto jsonDoc = QJsonDocument::fromJson(tmpFile.readAll(), &err);
	tmpFile.close();
	if (err.error != QJsonParseError::NoError)
	{
		logger->error("解读 Json 时出现错误: {}", err.errorString().toStdString());
		return;
	}
	while (true)
	{
		if (!jsonDoc.isObject())
			break;
		auto obj = jsonDoc.object();
		if (!obj.contains("items"))
			break;
		auto itemsVar = obj.value("items");
		if (!itemsVar.isArray())
			break;
		auto items = itemsVar.toArray();
		for (const auto& var : items)
		{
			if (!var.isObject())
			{
				logger->error("Json 格式不正确, 跳过解析");
				return;
			}
			auto itemObj = var.toObject();
			auto item = new ScheduleItem(QTime::fromString(itemObj.value("time").toString("00:00:00"), "HH:mm:ss"),
							  itemObj.value("title").toString("No Title"),
							  itemObj.value("subtitle").toString(""),
                              itemObj.value("iconFileName").toString("qrc:/images/icons/colored/info.svg"),
							  itemObj.value("durationSeconds").toInt(10),
							  itemObj.value("commandLine").toString("")
							  );
			logger->info("读取到时间表项: \n\t时间: {}\n\t标题: {}",
							   item->time().toString("HH:mm:ss").toStdString(),
							   item->title().toStdString()
						   );
			m_itemLst.push_back(item);
		}

		std::sort(m_itemLst.begin(), m_itemLst.end(), [](const ScheduleItem* a, const ScheduleItem* b) {
			return a->time().msecsSinceStartOfDay() < b->time().msecsSinceStartOfDay();
		});

		logger->debug("正在启动时间表计时器...");
		for (int i = 0; i < m_itemLst.count(); i++)
		{
			auto duration = m_itemLst.at(i)->time().msecsSinceStartOfDay() - QTime::currentTime().msecsSinceStartOfDay();
			if (duration <= 0)
				continue;
			auto tmr = new QTimer;
			m_timerSet.insert(tmr);
			tmr->setTimerType(Qt::VeryCoarseTimer);
			tmr->setSingleShot(true);
			tmr->setInterval(duration);
			connect(tmr, &QTimer::timeout, this, [tmr, i, this]() {
				updateCurrentIndex(tmr, i);
			});
			tmr->start();
		}
		return;
	}
	logger->error("Json 格式不正确, 跳过解析");
	return;
}

void ScheduleHost::readFromFile(const QString& fileName)
{
	setFileName(fileName);
	readFromFile();
}

void ScheduleHost::updateCurrentIndex(QTimer* timer, const int index)
{
	m_timerSet.erase(m_timerSet.find(timer));
	delete timer;
	m_currentIndex = index;
	emit currentIndexChanged();
	emit currentItemChanged();
	DynamicSpot::logger->info("时间表项 {} 已触发", currentItem()->title().toStdString());
}

ScheduleHost* ScheduleHost::instance()
{
	if (s_instance == nullptr)
		s_instance = new ScheduleHost;
	return s_instance;
}

void ScheduleHost::clearItems()
{
	for (auto it = m_timerSet.begin(); it != m_timerSet.end(); it++)
		delete (*it);
	m_timerSet.clear();
	for (auto item : m_itemLst)
		delete item;
	m_itemLst.clear();
	m_currentIndex = -1;
}
