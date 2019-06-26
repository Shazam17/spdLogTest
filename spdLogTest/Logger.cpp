#include "Logger.h"


#ifdef SPDLOG_H
Logger::Logger(spdlog::level::level_enum lvl) {
	createConsoleLogger();
	spdlog::set_level(lvl);
}

Logger::Logger() {
	createConsoleLogger();
	spdlog::set_level(spdlog::level::off);
}
void log(std::string str) {
	for (auto& item : loggers){
		
	}
}
void addConsoleLog() {
	auto console = spdlog::stdout_color_mt("console");
	loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>("console", console));
	console->info("ConsoleLogger init");
}
void addFileLog(std::string loggerName) {
	auto fileLogger = spdlog::basic_logger_mt(loggerName, "logs/" + loggerName + ".txt");
	loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(loggerName, fileLogger));
	fileLogger->info("init");
}
void Logger::setPattern(std::string pattern) {
	spdlog::set_pattern(pattern);
}

void Logger::changeLevel(spdlog::level::level_enum lvl) {
	spdlog::set_level(lvl);
}
#ifdef EXPIRIMENTAL
void Logger::setLoggerPattern(std::string loggerName, std::string pattern) {
	auto logger = getLogger(loggerName);
	logger->set_pattern(pattern);
}
void Logger::createConsoleLogger() {
	auto console = spdlog::stdout_color_mt("console");
	loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>("console", console));
	console->info("ConsoleLogger init");
}
void Logger::createFileLogger(std::string loggerName) {
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
void Logger::createFileLoggerRotated(std::string loggerName, int maxSize, int files) {
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
void Logger::createAsyncLogger(std::string loggerName, unsigned queueSize, unsigned backThread) {
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
void Logger::addFlushToLogger(std::string loggerName, spdlog::level::level_enum lvl) {
	auto logger = getLogger(loggerName);
	logger->flush_on(lvl);
}
void Logger::addIntervalFlush(int sec) {
	spdlog::flush_every(std::chrono::seconds(sec));
}
void Logger::addLogger(std::string loggerName) {
	try
	{
		loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(loggerName, spdlog::get(loggerName)));
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log initialization failed: " << ex.what() << std::endl;
	}
}
std::shared_ptr<spdlog::logger> Logger::getLogger(std::string loggerName) {
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
void Logger::deleteLogger(std::string loggerName) {
	loggers.erase(loggerName);
	spdlog::drop(loggerName);
}
std::shared_ptr<spdlog::logger> Logger::console() {
	auto logger = loggers.find("console");
	return logger->second;
}
void Logger::deleteAllLoggers() {
	spdlog::drop_all();
}
~Logger::Logger() {
	deleteAllLoggers();
}
#endif
#endif


#ifdef BOOST_LOG
Logger(logging::trivial::severity_level lvl) {
	boost::log::core::get()->set_filter(
		boost::log::trivial::severity >= lvl
	);
}
void setPattern(std::string pattern) {
	this->pattern = pattern;
}

void addConsoleLog() {
	boost::log::add_console_log(
		std::cout,
		boost::log::keywords::format = this->pattern,
		boost::log::keywords::auto_flush = true
	);
}

void addFileLog(int maxSize, int rotSize, std::string fileName, bool autoFlush) {
	boost::log::add_file_log(
		boost::log::keywords::file_name = fileName,
		boost::log::keywords::rotation_size = rotSize * 1024 * 1024,
		boost::log::keywords::max_size = maxSize * 1024 * 1024,
		boost::log::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0),
		boost::log::keywords::format = this->pattern,
		boost::log::keywords::auto_flush = autoFlush
	);

}
	


#endif
