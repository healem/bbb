/*
 * Logger.h
 *
 *  Created on: Mar 23, 2015
 *      Author: healem
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <syslog.h>

#define MAKE_STRING(x) MAKE_STRING2(x)
#define MAKE_STRING2(x) #x
#define LINE_STRING MAKE_STRING(__LINE__)

#define DEBUG(...) Logger::getLogger()->Log(LOG_DEBUG, __FILE__,LINE_STRING, "[DEBUG]", __VA_ARGS__)
#define INFO(...) Logger::getLogger()->Log(LOG_INFO, __FILE__,LINE_STRING, "[INFO]", __VA_ARGS__)
#define WARN(...) Logger::getLogger()->Log(LOG_WARNING, __FILE__,LINE_STRING, "[WARN]", __VA_ARGS__)
#define ERROR(...) Logger::getLogger()->Log(LOG_ERR, __FILE__,LINE_STRING, "[ERROR]", __VA_ARGS__)
#define FATAL(...) Logger::getLogger()->Log(LOG_CRIT, __FILE__,LINE_STRING, "[FATAL]", __VA_ARGS__)

class Logger {
public:
	virtual ~Logger();
	void Log(int priority, const char *fileName, std::string lineNo, const char *level, ...);
	std::string getString(const char *text);
	static Logger* getLogger();
private:
	Logger();
	Logger(const Logger&){};
	Logger& operator=(const Logger& ){ return *this;};
	static Logger* mpThis;
};

#endif /* LOGGER_H_ */
