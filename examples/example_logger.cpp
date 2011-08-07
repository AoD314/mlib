
#include "mlib/logger.hpp"
#include "mlib/datetime.hpp"

int main(int /*argc*/, const char ** /*argv*/)
{
	mlib::Logger logger("/tmp/my_log_file.txt");

	logger.log(LOG_INFO ("first message" ));
	logger.log(LOG_DEBUG("new message #1"));

	return 0;
}
