#define BOOST_TYPEOF_EMULATION

#include <stdexcept>
#include <string>
#include <iostream>

#include "boost/log/utility/setup.hpp"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>





#ifdef BOOST_LOG 
#define LOG_TRACE(x) BOOST_LOG_TRIVIAL(trace) << x 
#define LOG_DEBUG(x) BOOST_LOG_TRIVIAL(debug) << x 
#define LOG_INFO(x) BOOST_LOG_TRIVIAL(info) << x 
#define LOG_WARNING(x) BOOST_LOG_TRIVIAL(warning) << x 
#define LOG_ERROR(x) BOOST_LOG_TRIVIAL(error) << x
#define LOG_FATAL(x) BOOST_LOG_TRIVIAL(fatal) << x 

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

#endif





class FileLoggerBoost {

	FileLoggerBoost() {
	
	}

};

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

	void log(std::string str);
	void setPattern(std::string pattern);
	void changeLevel(spdlog::level::level_enum lvl);
	void addConsoleLog();
	void addFileLog(int maxSize, int rotSize, std::string fileName, bool autoFlush);
	
#ifdef EXPRIMENTAL
	void setLoggerPattern(std::string loggerName, std::string pattern);
	void createConsoleLogger();
	void createFileLogger(std::string loggerName);
	//maxSize in mb
	void createFileLoggerRotated(std::string loggerName, int maxSize, int files);
	void createAsyncLogger(std::string loggerName, unsigned queueSize, unsigned backThread);
	void addFlushToLogger(std::string loggerName, spdlog::level::level_enum lvl);
	void addIntervalFlush(int sec) {
		spdlog::flush_every(std::chrono::seconds(sec));
	}
	void addLogger(std::string loggerName);
	std::shared_ptr<spdlog::logger> getLogger(std::string loggerName);
	void deleteLogger(std::string loggerName);
	std::shared_ptr<spdlog::logger> console();
	void deleteAllLoggers();
	~Logger();
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

#define LOG_TRACE(x) Logger.log(x)
#define LOG_DEBUG(x) Logger.log(x)
#define LOG_INFO(x) Logger.log(x)
#define LOG_WARNING(x) Logger.log(x)
#define LOG_ERROR(x) Logger.log(x)
#define LOG_FATAL(x) Logger.log(x)

#endif