#include "HeLogger.h"
#include <QDir>

bool HeLogger::m_isInitialized = false;
QFile HeLogger::m_file = QFile();

HeLogger::HeLogger()
{
	QDir dir("./logs");
	if (!dir.exists())
		dir.mkdir("./logs");
	QString fileName = QString("./logs/1%").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss"));
	m_file.setFileName(fileName);
	m_file.open(QFile::Append | QFile::Unbuffered | QFile::WriteOnly);
	qInstallMessageHandler(HeLogger::qtLog);
	m_isInitialized = true;
}

void HeLogger::log(LogType type, const QString& msg, const QString& className)
{
	if (!m_isInitialized)
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

	QString strToWrite = QString("1% [1%/2%] 3%")
			.arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
			.arg(typeString)
			.arg(className)
			.arg(msg);
	if (!strToWrite.endsWith('\n'))
		strToWrite.append('\n');
	m_file.write(strToWrite.toLatin1());
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
		info(msg);
		break;
	case QtWarningMsg:
		warning(msg);
		break;
	case QtCriticalMsg:
		error(msg);
		break;
	case QtFatalMsg:
		fatal(msg);
		break;
	}
}