#define BOOST_TYPEOF_EMULATION

#include <stdexcept>
#include <string>
#include <iostream>
#include <map>

#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
//
//
//#include "boost/log/utility/setup.hpp"
//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
//#include <boost/log/utility/setup/file.hpp>
//#include <boost/log/utility/setup/common_attributes.hpp>
//#include <boost/log/sources/severity_logger.hpp>
//#include <boost/log/sources/record_ostream.hpp>
//
//

#define debugInfo(x) << "LINE : "  <<  __LINE__ <<" MESSAGE :" << x<< '\n' << "FILENAME :" << __FILE__ 

#ifdef BOOST_LOG 
#define LOG_TRACE(x) BOOST_LOG_TRIVIAL(trace)  debugInfo(x)
#define LOG_DEBUG(x) BOOST_LOG_TRIVIAL(debug) debugInfo(x)
#define LOG_INFO(x) BOOST_LOG_TRIVIAL(info) debugInfo(x)
#define LOG_WARNING(x) BOOST_LOG_TRIVIAL(warning) debugInfo(x)
#define LOG_ERROR(x) BOOST_LOG_TRIVIAL(error) debugInfo(x)
#define LOG_FATAL(x) BOOST_LOG_TRIVIAL(fatal) debugInfo(x)

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

#endif

class Logger {
private:
	std::string pattern;
#ifdef SPDLOG_H
	std::map<std::string, std::shared_ptr<spdlog::logger>> loggers;
#endif

#ifdef BOOST_LOG
	
#endif


#ifdef SPDLOG_H
public:
	Logger(spdlog::level::level_enum lvl);
	Logger();

	void setPattern(std::string pattern);
	void changeLevel(spdlog::level::level_enum lvl);
	
	void addFileLog(int maxSize, int rotSize, std::string fileName, bool autoFlush);
	void deleteConsoleLogger();

	void logTrace(std::string str);
	void logDebug(std::string str);
	void logInfo(std::string str);
	void logFatal(std::string str);
	void logError(std::string str);
	void logWarn(std::string str);

	void deleteLogger(std::string loggerName);
	void deleteAllLoggers();
	~Logger();
private:
	void addConsoleLog();
#ifdef EXPRIMENTAL
	void setLoggerPattern(std::string loggerName, std::string pattern);
	void createConsoleLogger();
	void createFileLogger(std::string loggerName);
	//maxSize in mb
	void createFileLoggerRotated(std::string loggerName, int maxSize, int files);
	void createAsyncLogger(std::string loggerName, unsigned queueSize, unsigned backThread);
	void addFlushToLogger(std::string loggerName, spdlog::level::level_enum lvl);
	void addIntervalFlush(int sec);
	void addLogger(std::string loggerName);
	std::shared_ptr<spdlog::logger> getLogger(std::string loggerName);
	std::shared_ptr<spdlog::logger> console();
#endif
#endif

#ifdef BOOST_LOG
public:
	Logger(logging::trivial::severity_level lvl);
	void setPattern(std::string pattern);
	void addConsoleLog();
	void addFileLog(int maxSize, int rotSize, std::string fileName, bool autoFlush);


#ifdef EXPIRIMENTAL
	void addFileLogger(std::string loggerName);
	~Logger();
#endif

#endif
};


#ifdef SPDLOG_H

#define LOG_TRACE(x) logger.logTrace(x)
#define LOG_DEBUG(x) logger.logDebug(x)
#define LOG_INFO(x) logger.logInfo(x)
#define LOG_WARNING(x) logger.logWarn(x)
#define LOG_ERROR(x) logger.logError(x)
#define LOG_FATAL(x) logger.logFatal(x)

#endif