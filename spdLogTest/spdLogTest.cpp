#include "Logger.h"



struct Test {

	void runTrivialTests() {
		LOG_TRACE("Trace log");
		LOG_DEBUG("Debug log");
		LOG_INFO("Info log");
		LOG_FATAL("Fatal log");
		LOG_WARNING("Warning log");
		LOG_ERROR("Error log");
	}


};



int main() {

	BOOST_LOG_NAMED_SCOPE("main");
	Logger logger(logging::trivial::severity_level::trace);
	Test test;



	logger.setPattern("[%TimeStamp%][%Scope%][%LineID%] :  %Message%");

	logger.addConsoleLog();

	logger.addFileLog(5, 3, "smp.log", false);
	

	test.runTrivialTests();

}




