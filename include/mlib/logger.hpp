
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <mlib/ilogger.hpp>
#include <mlib/convert.hpp>

namespace mlib
{

    class Logger : public ILogger
    {
    private:
        std::string file_name;

    public:
        Logger(const std::string& filename);
        void log(std::string msg);
    };
}

#undef LOG_INF
#undef LOG_DBG
#undef LOG_ERR

#define LOG_INF(msg) std::string("[INFO]  ") + std::string(msg)

#define LOG_DBG(msg)                                                                                                           \
    std::string("[DEBUG][") + std::string(__FILE__).erase(0, 1 + std::string(__FILE__).find_last_of("/\\")) + std::string(":") \
        + std::string(mlib::to_str(__LINE__)) + std::string("]  ") + std::string(msg)

#define LOG_ERR(msg)                                                                                                           \
    std::string("[ERROR][") + std::string(__FILE__).erase(0, 1 + std::string(__FILE__).find_last_of("/\\")) + std::string(":") \
        + std::string(mlib::to_str(__LINE__)) + std::string("]  ") + std::string(msg)

#endif
