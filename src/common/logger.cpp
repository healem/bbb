/*
 * Logger.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: healem
 */

#include "logger.h"
#include <cstdio>
#include <cstdarg>

Logger* Logger::mpThis = NULL;

Logger::Logger()
{
}

Logger::~Logger()
{
	closelog();
}

Logger* Logger::getLogger()
{
	if(mpThis == NULL)
	{
		mpThis = new Logger();
		openlog(NULL, 0, LOG_LOCAL1);
	}

	return mpThis;
}

void Logger::Log(int priority, const char *fileName, std::string lineNo, const char *level, ...)
{
	char msg[256];
	va_list logmsg;
	va_start(logmsg, level);
	const char *format = va_arg(logmsg, const char*);
	vsprintf(msg, format, logmsg);
	std::string file(fileName);
	std::string l(level);
	std::string message = l + file + "[" + lineNo + "]:" + msg;
	syslog(priority, "%s", message.c_str());
}

