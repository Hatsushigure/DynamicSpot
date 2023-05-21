#include "TimeBanner.h"
#include "SloganProvider.h"
#include "HeLogger.h"

TimeBanner::TimeBanner(QObject *parent)
	: QObject{parent}
{
	auto logger = HeLogger::logger();
	logger->info("正在初始化标语选择器...", staticMetaObject.className());
	m_sloganProvider = new SloganProvider(this);
	logger->info("标语选择器初始化完成", staticMetaObject.className());
}
