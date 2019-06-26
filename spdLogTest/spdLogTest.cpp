#include "Logger.h"



struct Test
{
	static void runTrivialTests(Logger logger) {
		LOG_TRACE("Trace log");
		LOG_DEBUG("Debug log");
		LOG_INFO("Info log");
		LOG_FATAL("Fatal log");
		LOG_WARNING("Warning log");
		LOG_ERROR("Error log");
	}
};



int main()
{

	
	Logger logger(spdlog::level::debug);



	logger.setPattern("[%D] %v");



	logger.addFileLog(5, 3, "smp2.log", false);
	

	Test::runTrivialTests(logger);

}




