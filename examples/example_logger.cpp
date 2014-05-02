
#include "mlib/logger.hpp"
#include "mlib/datetime.hpp"

int main(int /*argc*/, const char** /*argv*/)
{
    mlib::Logger logger("my_log_file.txt");

    logger.log(LOG_INF("first message"));
    logger.log(LOG_DBG("new message #1"));
    logger.log(LOG_ERR("new message #2"));

    return 0;
}
