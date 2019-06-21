#include <iostream>
#include <fstream>
#include <map>

//
//#include "spdlog/spdlog.h" 
//#include "spdlog/async.h"
//
//#include "spdlog/sinks/basic_file_sink.h"
//#include "spdlog/sinks/rotating_file_sink.h" 
//#include "spdlog/sinks/stdout_color_sinks.h"
//

#define BOOST_TYPEOF_EMULATION



#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
	
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
#endif

public:

#ifdef SPDLOG_H
	Logger(spdlog::level::level_enum lvl) {
		createConsoleLogger();
		spdlog::set_level(lvl);
	}

	Logger() {
		createConsoleLogger();
		spdlog::set_level(spdlog::level::off);
	}
#endif

#ifdef BOOST_LOG
	Logger(logging::trivial::severity_level lvl) {
		core = logging::core::get();

		logging::core::get()->set_filter( 
			logging::trivial::severity >= lvl
		);

		logging::add_file_log
		(
			keywords::file_name = "sample_%N.log", 
			keywords::rotation_size = 10 * 1024 * 1024, 
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), 
			keywords::format = "[%TimeStamp%]: %Message%"                                 
		);

	}
	Logger() {

	}

#endif


#ifdef SPDLOG_H
	void changeLevel(spdlog::level::level_enum lvl) {
		spdlog::set_level(lvl);
	}
#endif

#ifdef SPDLOG_H
	void setPattern(std::string pattern) {
		spdlog::set_pattern(pattern);
	}
#endif


#ifdef SPDLOG_H
	void setLoggerPattern(std::string loggerName, std::string pattern) {
		auto logger = getLogger(loggerName);
		logger->set_pattern(pattern);
	}
#endif

#ifdef SPDLOG_H
	void createConsoleLogger() {
		auto console = spdlog::stdout_color_mt("console");
		loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>("console", console));
		console->info("ConsoleLogger init");
	}
#endif

#ifdef SPDLOG_H
	void createFileLogger(std::string loggerName) {
		try
		{
			auto fileLogger = spdlog::basic_logger_mt(loggerName, "logs/" + loggerName + ".txt");
			loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(loggerName, fileLogger));
			fileLogger->info("init");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}
#endif

#ifdef SPDLOG_H
	//maxSize in mb
	void createFileLoggerRotated(std::string loggerName, int maxSize, int files) {
		try
		{
			//3 files 5 mb max size
			auto fileLoggerR = spdlog::rotating_logger_mt(loggerName, "logs/" + loggerName + ".txt", 1024 * 1024 * maxSize, files);
			fileLoggerR->info("init");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}
#endif

#ifdef SPDLOG_H
	void createAsyncLogger(std::string loggerName, unsigned queueSize, unsigned backThread) {
		try
		{
			spdlog::init_thread_pool(queueSize, backThread);
			auto fileAsync = spdlog::basic_logger_mt<spdlog::async_factory>(loggerName, "logs/" + loggerName + ".txt");
			fileAsync->info("Async logger init");
			loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(loggerName, fileAsync));
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}

	}
#endif

#ifdef SPDLOG_H
	void addFlushToLogger(std::string loggerName, spdlog::level::level_enum lvl) {
		auto logger = getLogger(loggerName);
		logger->flush_on(lvl);
	}
#endif
	//in seconds	
#ifdef SPDLOG_H
	void addIntervalFlush(int s) {
		spdlog::flush_every(std::chrono::seconds(s));
	}
#endif

#ifdef SPDLOG_H
	void addLogger(std::string loggerName) {
		try
		{
			loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(loggerName, spdlog::get(loggerName)));
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}

#endif

#ifdef SPDLOG_H
	std::shared_ptr<spdlog::logger> getLogger(std::string loggerName) {
		try {
			auto logger = loggers.find(loggerName);
			if (logger != loggers.end()) {
				return logger->second;
			}
			else {
				console()->error("logger isnt exist");
				//throw exception
				return nullptr;
			}
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}
#endif

#ifdef SPDLOG_H
	void deleteLogger(std::string loggerName) {
		loggers.erase(loggerName);
		spdlog::drop(loggerName);
	}
#endif

#ifdef SPDLOG_H
	void deleteAllLoggers() {
		spdlog::drop_all();
	}
	#endif
protected:
#ifdef SPDLOG_H
	std::shared_ptr<spdlog::logger> console() {
		auto logger = loggers.find("console");
		return logger->second;
	}
#endif
};


int main(){ 

	


	Logger logger();


	
}
