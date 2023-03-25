/************************************************************
 * HeLogger -- 氦 Logger(其实就是 Hatsushigure 的首尾字母啊)(划掉) *
 ************************************************************/
#pragma once
#include <QDebug>
#include <QFile>

class HeLogger
{
public:
	enum class LogType {Info, Warning, Error, Fatal};
private:
	static bool m_isInitialized;
	static QFile m_file;
public:
	HeLogger();
public:
	static void log(LogType type, const QString& msg, const QString& className = "Unknown");
	static void info(const QString& msg, const QString& className = "Unknown");
	static void warning(const QString& msg, const QString& className = "Unknown");
	static void error(const QString& msg, const QString& className = "Unknown");
	static void fatal(const QString& msg, const QString& className = "Unknown");
	static void qtLog(QtMsgType type, const QMessageLogContext&, const QString& msg);
};

