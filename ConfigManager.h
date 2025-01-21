#pragma once
#include <memory>
#include <string_view>
#include <QDateTime>

class QSettings;

namespace DynamicSpot
{
class ConfigManager
{
private:
	static constexpr std::string_view configFilename {"./settings.ini"};
private:
	std::shared_ptr<QSettings> m_qSettings{nullptr};
	int m_fileVersion {};
	QDateTime m_deadline {};
	bool m_enableSecondCountDown {};
public:
	ConfigManager();
public:
	auto fileVersion() const {return m_fileVersion;}	// Always returns current version instead of file version :P
	const auto& deadline() const {return m_deadline;}
	auto enableSecondCountDown() const {return m_enableSecondCountDown;}
public:
	void writeDefaultConfig();
private:
	void readConfigVersion();
	void readConfigV0();
	void readConfig() {readConfigV0();}
};
}
