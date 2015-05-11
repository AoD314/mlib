#ifndef __FORMATTER_HPP__
#define __FORMATTER_HPP__

#include <string>
#include <sstream>
#include <iomanip>

namespace mlib
{

class Print
{
    public:
        //! Formating size to std::string
        static std::string size(int64_t byte);
        static std::string size_in_byte(int64_t byte);
        static std::string size_in_kbyte(int64_t byte);
        static std::string size_in_mbyte(int64_t byte);
        static std::string size_in_gbyte(int64_t byte);
        static std::string size_in_tbyte(int64_t byte);



        //! Formating time to std::string
        static std::string time(int64_t msec);
        static std::string time_in_ms(int64_t sec);
        static std::string time_in_s(int64_t sec);
        static std::string time_in_m(int64_t sec);
        static std::string time_in_h(int64_t sec);

        //! Formating percent to std::string
        static std::string percent(int64_t i, int64_t total);

};

}





#endif
