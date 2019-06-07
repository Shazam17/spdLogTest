#include <iostream>
#include <fstream>
#include <map>

#include "spdlog/spdlog.h"
#include "spdlog/async.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h" 
#include "spdlog/sinks/stdout_color_sinks.h"



class Logger {
private:
	
	std::map<std::string , std::shared_ptr<spdlog::logger>> loggers;


	inline class multiSinkLogger {

	};

public:
	Logger(spdlog::level::level_enum lvl) {
		createConsoleLogger();
		spdlog::set_level(lvl);
	}

	Logger() {
		createConsoleLogger();
		spdlog::set_level(spdlog::level::off);
	}

	
	void changeLevel(spdlog::level::level_enum lvl) {
		spdlog::set_level(lvl);
	}

	void setPattern(std::string str) {
		spdlog::set_pattern(str);
	}

	void deleteLogger(std::string loggerName) {
		spdlog::drop(loggerName);
	}

	void deleteAllLoggers() {
		spdlog::drop_all();
	}

	void createConsoleLogger() {
		auto console = spdlog::stdout_color_mt("console");
		loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>("console", console));
		console->info("ConsoleLogger init");
	}

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
	

	//maxSize in mb
	void createFileLoggerRotated(std::string loggerName, int maxSize  , int files) {
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






	void addLogger(std::string loggerName) {
		try 
		{
			loggers.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(loggerName, spdlog::get(loggerName)));
		}
		catch(const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}


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

	protected:
	std::shared_ptr<spdlog::logger> console() {
		auto logger = loggers.find("console");
		return logger->second;
	}
};


int main(){ 

	Logger logger(spdlog::level::debug);
	


	logger.createFileLogger("fileLogger");
	logger.createAsyncLogger("asyncLogger", 8192, 1);
	logger.createFileLoggerRotated("fileRotated" ,5 ,3);



	logger.getLogger("fileLogger")->error("error");

}
