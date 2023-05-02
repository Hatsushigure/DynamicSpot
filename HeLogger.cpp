#include "HeLogger.h"
#include <QDir>

HeLogger* HeLogger::m_logger {nullptr};

HeLogger::HeLogger()
{
	QDir dir(".");
	if (!dir.exists("./logs"))
		dir.mkdir("./logs");
	QString fileName = QString("./logs/%1.log").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss"));
	m_file.setFileName(fileName);
	m_file.open(QFile::Append | QFile::Unbuffered | QFile::Text);
	if (!m_file.isOpen())
	{
		qFatal("无法打开日志文件，请确认该目录是否具有读写权限或将本软件移动至其他目录");
	}
	m_stderrFile.open(stderr, QFile::WriteOnly | QFile::Unbuffered | QFile::Text);
	qInstallMessageHandler(HeLogger::qtLog);
	info("成功初始化了 HeLogger!", "HeLogger");
}

HeLogger* HeLogger::logger()
{
	if (m_logger == nullptr)
		m_logger = new HeLogger;
	return m_logger;
}

void HeLogger::log(LogType type, const QString& msg, const QString& className)
{
	using Qt::StringLiterals::operator""_s;
	if (m_logger == nullptr)
		return;
	QString typeString;
	switch (type)
	{
	case LogType::Info:
		typeString = "Info";
		break;
	case LogType::Warning:
		typeString = "Warning";
		break;
	case LogType::Error:
		typeString = "Error";
		break;
	case LogType::Fatal:
		typeString = "Fatal";
		break;
	}

	QString strToWrite = u"%1 [%2/%3] %4"_s
						 .arg(QTime::currentTime().toString("HH:mm:ss.zzz"),
							  typeString,
							  className,
							  msg);
	if (!strToWrite.endsWith('\n'))
		strToWrite.append('\n');
	m_file.write(strToWrite.toUtf8());
	m_stderrFile.write(strToWrite.toLocal8Bit());
}

void HeLogger::info(const QString& msg, const QString& className)
{
	log(LogType::Info, msg, className);
}

void HeLogger::warning(const QString& msg, const QString& className)
{
	log(LogType::Warning, msg, className);
}

void HeLogger::error(const QString& msg, const QString& className)
{
	log(LogType::Error, msg, className);
}

void HeLogger::fatal(const QString& msg, const QString& className)
{
	log(LogType::Fatal, msg, className);
}

void HeLogger::qtLog(QtMsgType type, const QMessageLogContext&, const QString& msg)
{
	switch(type)
	{
	case QtDebugMsg:
	case QtInfoMsg:
		logger()->info(msg);
		break;
	case QtWarningMsg:
		logger()->warning(msg);
		break;
	case QtCriticalMsg:
		logger()->error(msg);
		break;
	case QtFatalMsg:
		logger()->fatal(msg);
		break;
	}
}
