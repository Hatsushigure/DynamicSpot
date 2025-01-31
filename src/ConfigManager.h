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
	bool m_enableSlogan {};
public:
	ConfigManager();
public:
	auto fileVersion() const {return m_fileVersion;}	// Always returns current version instead of file version :P
	const auto& deadline() const {return m_deadline;}
	auto enableSecondCountDown() const {return m_enableSecondCountDown;}
	auto enableSlogan() const {return m_enableSlogan;}
public:
	void writeDefaultConfig();
private:
	void writeCurrentConfig();
	void readConfigVersion();
	void readConfigV0();
	void readConfigV1();
	void readConfig() {readConfigV1();}
};
}
