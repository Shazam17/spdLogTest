#pragma once
#include <iostream>
#include <map>
#include <vector>


#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>


#define debugInfo  __LINE__ + ' ' + __FILE__

#ifdef BOOST_LOG 
#define LOG_TRACE(x) BOOST_LOG_TRIVIAL(trace) << x << debugInfo
#define LOG_DEBUG(x) BOOST_LOG_TRIVIAL(debug) << x << debugInfo
#define LOG_INFO(x) BOOST_LOG_TRIVIAL(info) << x << debugInfo
#define LOG_WARNING(x) BOOST_LOG_TRIVIAL(warning) << x << debugInfo
#define LOG_ERROR(x) BOOST_LOG_TRIVIAL(error) << x << debugInfo
#define LOG_FATAL(x) BOOST_LOG_TRIVIAL(fatal) << x << debugInfo
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
#endif


#ifdef SPDLOG_H
#define LOG_TRACE(x) spdlog::trace(x + debugInfo)
#define LOG_DEBUG(x) spdlog::debug(x + debugInfo)
#define LOG_INFO(x) spdlog::info(x + debugInfo)
#define LOG_WARNING(x) spdlog::warn(x + debugInfo)
#define LOG_ERROR(x) spdlog::error(x + debugInfo)
#define LOG_FATAL(x) spdlog:critical(x + debugInfo)
#endif

class Logger {
private:
#ifdef SPDLOG_H
	std::map<std::string, std::shared_ptr<spdlog::logger>> loggers;
#endif

#ifdef BOOST_LOG
	boost::shared_ptr<logging::core> core;
	std::vector<boost::shared_ptr<sinks::sink>> store;
#endif

public:
#ifdef SPDLOG_H
	Logger(spdlog::level::level_enum lvl);
	Logger();
	void changeLevel(spdlog::level::level_enum lvl);
	void setPattern(std::string pattern);
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

#ifdef BOOST_LOG
	Logger();

#endif

};
