/**
 * @file
 * @copyright (C) 2012-2014 Phonations
 * @license http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */

#include <QtGlobal>
#include <QDate>
#include <QStringList>
#include <iostream>
#include <QDir>

#include "PhDebug.h"

PhDebug* PhDebug::_d = NULL;

// This function is called to create an instance of the class.
// Calling the constructor publicly is not allowed. The constructor
// is private and is only called by this Instance function.


void PhDebug::messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(type); Q_UNUSED(context);
	if(instance()->_logMask & (1 << instance()->_currentLogLevel)) {
		QString logMessage = "";

		// Display the date
		if(instance()->_displayDate) {
			logMessage += QDate::currentDate().toString("dd/MM/yyyy ");
		}

		// Display timestamp
		if (instance()->_displayTime) {
			logMessage += QTime::currentTime().toString("hh:mm:ss.zzz ");
		}

		// Display filename
		if (instance()->_displayFileName) {

			logMessage += QString(context.file).split("/").last() + "\t";
		}

		// Display function name
		if (instance()->_displayFunctionName) {
			logMessage += QString(context.function) + "\t";
		}

		// Display line number
		if (instance()->_displayLine) {
			logMessage += QString("@") + QString::number(context.line) + "\t";
		}

		logMessage += msg;

		if(instance()->_showConsole) {
			switch(type) {
			case QtDebugMsg:
				std::cout << logMessage.toStdString() << std::endl;
				break;
			case QtWarningMsg:
			case QtCriticalMsg:
			case QtFatalMsg:
				std::cerr << logMessage.toStdString() << std::endl;
				break;
			}
		}

		*instance()->_textLog << logMessage << endl;
	}
}

QString PhDebug::logLocation()
{
	return instance()->_logFileName;
}

void PhDebug::showConsole(bool show)
{
	instance()->_showConsole = show;
}

void PhDebug::setDisplay(bool date, bool time, bool fileName, bool functionName, bool line)
{
	instance()->_displayDate = date;
	instance()->_displayTime = time;
	instance()->_displayFileName = fileName;
	instance()->_displayFunctionName = functionName;
	instance()->_displayLine = line;
}

// Called if init() was forget
PhDebug* PhDebug::instance()
{
	if (!_d)   // Only allow one instance of class to be generated.
		_d = new PhDebug();
	return _d;
}

QDebug PhDebug::debug(const char *fileName, int lineNumber, const char *functionName, int messageLogLevel)
{
	instance()->_currentLogLevel = messageLogLevel;
	return QMessageLogger(fileName, lineNumber, functionName).debug();
}

QDebug PhDebug::error(const char *fileName, int lineNumber, const char *functionName)
{
	instance()->_currentLogLevel = 0;
	return QMessageLogger(fileName, lineNumber, functionName).critical();
}

PhDebug::PhDebug()
{
	qInstallMessageHandler(this->messageOutput);

#if defined(Q_OS_MAC)
	QString logDirPath = QDir::homePath() + "/Library/Logs/Phonations/";
#elif defined(Q_OS_WIN)
	QString logDirPath = QString(qgetenv("APPDATA")) + "/Phonations";
#else
#error Choose a folder for log
#endif

	QDir logDir(logDirPath);
	if(!logDir.exists()) {
		QDir().mkdir(logDirPath);
	}
	_logFileName = logDirPath + APP_NAME + ".log";
	QFile * f = new QFile(_logFileName);
	f->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
	f->write("\n\n");
	_textLog = new QTextStream(f);

	_displayDate = false;
	_displayTime = true;
	_displayFunctionName = true;
	_displayFileName = true;
	_displayLine = true;
	_showConsole = true;
	_logMask = 1;
}

void PhDebug::setLogMask(int mask)
{
	instance()->_logMask = mask;
}

int PhDebug::getLogMask()
{
	return instance()->_logMask;
}



