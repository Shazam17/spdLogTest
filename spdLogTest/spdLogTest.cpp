#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h" 
#include <fstream>

#define DEBUGLOG


/*
	spdlog::info("Welcome to spdlog");

	spdlog::error("Some error message with arg: {}", 1);

	spdlog::warn("Easy padding in numbers like {:08d}", 12);
	spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	spdlog::info("Support for floats {:03.2f}", 1.23456);
	spdlog::info("Positional args are {1} {0}..", "too", "supported");
	spdlog::info("{:<10}", "left aligned");



	// change log pattern
	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");


	SPDLOG_TRACE("Some trace message with param {}", {});
	SPDLOG_DEBUG("Some debug message");

	std::cout << "Hello World!\n";

	*/


class Logger {
private:
	

public:
	Logger(spdlog::level::level_enum lvl) {
		spdlog::set_level(lvl);
	}

	Logger() {
		spdlog::set_level(spdlog::level::off);
	}

	void changeLevel(spdlog::level::level_enum lvl) {
		spdlog::set_level(lvl);
	}

	void setPattern(std::string str) {
		spdlog::set_pattern(str);
	}

	void debug(std::string str) {
		spdlog::debug(str.c_str());
	}

	template<typename T>
	void error(std::string str, T arg) {
		spdlog::error(str, arg);
	}

	template<typename T>
	void warn(std::string str, T arg) {
		spdlog::warn(str , arg);
	}

	template<typename T>
	void critical(std::string str, T arg) {
		spdlog::critical(str.c_str(), arg);
	}

	void info(std::string str) {
		spdlog::info(str);
	}

	void createFile(std::string filePath, std::string fileName) {
		std::ofstream file(filePath + fileName);
		file.close();
	}
	
	void createFileLogger(std::string loggerName) {
		createFile("logs/" , "basic.txt");
		try {
			auto my_logger = spdlog::basic_logger_mt(loggerName, "logs/basic.txt");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}


	void createFileLoggerRotated(std::string loggerName) {
		createFile("logs/", "rotating.txt");

		try
		{
			//3 files 5 mb max size
			auto file_logger = spdlog::rotating_logger_mt("file_logger", "log/rotating", 1024 * 1024 * 5, 3);
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}

};


int main(){ 

	Logger logger(spdlog::level::debug);


	logger.info("hello");


	logger.debug("degug test");
	
	logger.critical("fatal error {}", 4);
	logger.createFileLogger("basicLogger");
}
