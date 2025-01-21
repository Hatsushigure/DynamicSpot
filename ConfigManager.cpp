#include "ConfigManager.h"
#include "DynamicSpot.h"
#include <QSettings>
#include <spdlog/logger.h>

using DynamicSpot::ConfigManager;

ConfigManager::ConfigManager()
{
	auto logger = DynamicSpot::logger;

	m_qSettings = std::make_shared<QSettings>(configFilename.data(), QSettings::IniFormat);
	readConfigVersion();
	switch (m_fileVersion)
	{
	case 0:
		readConfigV0();
		break;
	case 1:
		readConfig();
		break;
	default:
		logger->error("Config file version greater than current. I will clear everything and go back to default");
		writeDefaultConfig();
		break;
	}
}

void ConfigManager::writeDefaultConfig()
{
	namespace keys = DynamicSpot::SettingsKey;
	namespace vals = DynamicSpot::DefaultSettings;

	DynamicSpot::logger->info("Resetting to default config...");

	m_qSettings->clear();
	m_qSettings->setValue(keys::version, DynamicSpot::VersionInfo::configVer);
	m_qSettings->setValue(keys::deadline, vals::deadline.data());
	m_qSettings->setValue(keys::enableSecondCountDown, vals::enableSecondCountDown);

	m_fileVersion = DynamicSpot::VersionInfo::configVer;
	m_deadline = QDateTime::fromString(vals::deadline.data(), "yyyy-MM-dd_HH-mm-ss");
	m_enableSecondCountDown = vals::enableSecondCountDown;
}

void ConfigManager::writeCurrentConfig()
{
	namespace keys = DynamicSpot::SettingsKey;

	DynamicSpot::logger->info("Writing current config...");

	m_qSettings->clear();
	m_qSettings->setValue(keys::version, m_fileVersion);
	m_qSettings->setValue(keys::deadline, m_deadline.toString("yyyy-MM-dd_HH-mm-ss"));
	m_qSettings->setValue(keys::enableSecondCountDown, m_enableSecondCountDown);
	m_qSettings->setValue(keys::enableSlogan, m_enableSlogan);
}

void ConfigManager::readConfigVersion()
{
	auto logger = DynamicSpot::logger;
	namespace keys = DynamicSpot::SettingsKey;

	logger->debug("Reading config version...");

	auto convertSuccess = false;
	if (!m_qSettings->contains(keys::version))
	{
		logger->warn("Config version not specified or newly installed");
		logger->debug("Maybe will add some action when first use");
		m_qSettings->setValue(keys::version, DynamicSpot::VersionInfo::configVer);
	}
	auto fileVer = m_qSettings->value(keys::version).toInt(&convertSuccess);
	if (!convertSuccess)
	{
		logger->error("Config version is NaN! Suppose using the right version.");
	}
	logger->info("Config version: {}", fileVer);
	m_fileVersion = fileVer;
}

void ConfigManager::readConfigV0()
{
	auto logger = DynamicSpot::logger;
	namespace keys = DynamicSpot::SettingsKey;
	namespace vals = DynamicSpot::DefaultSettings;

	logger->debug("Reading config (v0)");

	// Deadline
	if (!m_qSettings->contains(keys::deadline))
	{
		logger->warn("Deadline not specified, using default");
		m_qSettings->setValue(keys::deadline, vals::deadline.data());
	}
	auto deadlineStr = m_qSettings->value(keys::deadline).toString();
	auto deadline = QDateTime::fromString(deadlineStr, "yyyy-MM-dd_HH-mm-ss");
	if (!deadline.isValid())
	{
		logger->warn("Deadline is not a valid datetime, resetting to default");
		m_qSettings->setValue(keys::deadline, vals::deadline.data());
		deadline = QDateTime::fromString(vals::deadline.data(), "yyyy-MM-dd_HH-mm-ss");
	}
	logger->info("Deadline is {}", deadline.toString("yyyy/MM/dd HH:mm::ss").toStdString());
	m_deadline = deadline;

	// EnableSecondCountDown
	if (!m_qSettings->contains(keys::enableSecondCountDownV0))
	{
		logger->warn("EnableSecondCountDown is not specified, using default");
		m_qSettings->setValue(keys::enableSecondCountDownV0, vals::enableSecondCountDown);
	}
	auto enableSecondCountDown = m_qSettings->value(keys::enableSecondCountDownV0).toBool();
	logger->info("EnableSecondCountDown is {}", enableSecondCountDown);
	m_enableSecondCountDown = enableSecondCountDown;

	// Add undefined values
	logger->info("EnableSlogan set to {}", vals::enableSlogan);
	m_qSettings->setValue(keys::enableSlogan, vals::enableSlogan);

	// Update config version
	m_qSettings->setValue(keys::version, DynamicSpot::VersionInfo::configVer);
	m_fileVersion = DynamicSpot::VersionInfo::configVer;

	// Update format
	logger->info("Updating config version to current ({})", DynamicSpot::VersionInfo::configVer);
	writeCurrentConfig();
}

void ConfigManager::readConfigV1()
{
	auto logger = DynamicSpot::logger;
	namespace keys = DynamicSpot::SettingsKey;
	namespace vals = DynamicSpot::DefaultSettings;

	logger->debug("Reading config (v1)");

	// Deadline
	if (!m_qSettings->contains(keys::deadline))
	{
		logger->warn("Deadline not specified, using default");
		m_qSettings->setValue(keys::deadline, vals::deadline.data());
	}
	auto deadlineStr = m_qSettings->value(keys::deadline).toString();
	auto deadline = QDateTime::fromString(deadlineStr, "yyyy-MM-dd_HH-mm-ss");
	if (!deadline.isValid())
	{
		logger->warn("Deadline is not a valid datetime, resetting to default");
		m_qSettings->setValue(keys::deadline, vals::deadline.data());
		deadline = QDateTime::fromString(vals::deadline.data(), "yyyy-MM-dd_HH-mm-ss");
	}
	logger->info("Deadline is {}", deadline.toString("yyyy/MM/dd HH:mm::ss").toStdString());
	m_deadline = deadline;

	// EnableSecondCountDown
	if (!m_qSettings->contains(keys::enableSecondCountDown))
	{
		logger->warn("EnableSecondCountDown is not specified, using default");
		m_qSettings->setValue(keys::enableSecondCountDown, vals::enableSecondCountDown);
	}
	auto enableSecondCountDown = m_qSettings->value(keys::enableSecondCountDown).toBool();
	logger->info("EnableSecondCountDown is {}", enableSecondCountDown);
	m_enableSecondCountDown = enableSecondCountDown;

	// EnableSlogan
	if (!m_qSettings->contains(keys::enableSlogan))
	{
		logger->warn("EnableSlogan is not specified, using default");
		m_qSettings->setValue(keys::enableSlogan, vals::enableSlogan);
	}
	auto enableSlogan = m_qSettings->value(keys::enableSlogan).toBool();
	logger->info("EnableSlogan is {}", enableSlogan);
	m_enableSlogan = enableSlogan;
}
