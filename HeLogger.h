/**************************************************************
 * HeLogger -- 氦 Logger(其实就是 Hatsushigure 的首尾字母啊)(划掉) *
 **************************************************************/
#pragma once
#include <QDebug>
#include <QFile>

class HeLogger
{
public:
	enum class LogType {Info, Warning, Error, Fatal};
private:
	static HeLogger* m_logger;
	QFile m_file;
	QFile m_stderrFile;
private:
	HeLogger();
public:
	static HeLogger* logger();
public:
	void log(LogType type, const QString& msg, const QString& className = "Unknown");
	void info(const QString& msg, const QString& className = "Unknown");
	void warning(const QString& msg, const QString& className = "Unknown");
	void error(const QString& msg, const QString& className = "Unknown");
	void fatal(const QString& msg, const QString& className = "Unknown");
public:
	static void qtLog(QtMsgType type, const QMessageLogContext&, const QString& msg);
};

