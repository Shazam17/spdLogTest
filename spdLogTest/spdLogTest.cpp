#include "Logger.h"







int main() {

	Logger logger();
	
	//logger.addFileLogger("someFile.log");


	typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
	boost::shared_ptr< file_sink > sink(new file_sink(
		keywords::file_name = "file.log",                       // file name pattern
		keywords::target_file_name = "%Y%m%d_%H%M%S_%5N.log",   // file name pattern
		keywords::rotation_size = 16384                         // rotation size, in characters
	));



}




