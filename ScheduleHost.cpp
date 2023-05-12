#include "ScheduleHost.h"
#include "HeLogger.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

using Qt::Literals::operator""_s;

ScheduleHost::ScheduleHost(QObject *parent)
	: QObject{parent}
{
}

QString ScheduleHost::fileName() const
{
	return m_fileName;
}

void ScheduleHost::setFileName(const QString& newFileName)
{
	m_fileName = newFileName;
}

int ScheduleHost::currentIndex() const
{
	return m_currentIndex;
}

ScheduleItem* ScheduleHost::currentItem() const
{
	if (m_currentIndex < 0)
		return nullptr;
	return m_itemLst.at(m_currentIndex);
}

void ScheduleHost::readFromFile()
{
	clearItems();

	if (m_fileName.isEmpty())
	{
		HeLogger::logger()->warning("未指定文件名, 跳过读取", "ScheduleHost");
		return;
	}
	QFile tmpFile(m_fileName);
	tmpFile.open(QFile::ReadOnly);
	if (!tmpFile.isOpen())
	{
		HeLogger::logger()->error("无法打开文件, 请检查文件是否存在以及是否有相应权限", "ScheduleHost");
		return;
	}

	QJsonParseError err;
	auto jsonDoc = QJsonDocument::fromJson(tmpFile.readAll(), &err);
	tmpFile.close();
	if (err.error != QJsonParseError::NoError)
	{
		HeLogger::logger()->error(u"解读 Json 时出现错误: %1"_s.arg(err.errorString()), "ScheduleHost");
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
				HeLogger::logger()->error("Json 格式不正确, 跳过解析", "ScheduleHost");
				return;
			}
			auto itemObj = var.toObject();
			auto item = new ScheduleItem(QTime::fromString(itemObj.value("time").toString("00:00:00"), "HH:mm:ss"),
							  itemObj.value("title").toString("No Title"),
							  itemObj.value("subtitle").toString(""),
							  itemObj.value("iconFileName").toString("qrc:///DynamicSpot/images/icons/colored/info-256.svg"),
							  itemObj.value("durationSeconds").toInt(10),
							  itemObj.value("commandLine").toString("")
							  );
			HeLogger::logger()->info(u"读取到时间表项: 时间: %1\n\t\t\t\t\t\t\t\t标题: %2"_s.arg(
							   item->time().toString("HH:mm:ss"),
							   item->title()
							   ),
						   "ScheduleHost"
						   );
			m_itemLst.push_back(item);
		}

		std::sort(m_itemLst.begin(), m_itemLst.end(), [](const ScheduleItem* a, const ScheduleItem* b) {
			return a->time().msecsSinceStartOfDay() < b->time().msecsSinceStartOfDay();
		});

		HeLogger::logger()->info("正在启动时间表计时器...", "ScheduleHost");
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
	HeLogger::logger()->error("Json 格式不正确, 跳过解析", "ScheduleHost");
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
	HeLogger::logger()->info(u"时间表项 %1 已触发"_s.arg(currentItem()->title()), "ScheduleHost");
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
