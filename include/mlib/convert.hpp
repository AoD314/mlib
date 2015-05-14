
#ifndef __CONVERT_HPP__
#define __CONVERT_HPP__

#include <string>
#include <sstream>
#include <iomanip>

namespace mlib
{
    //! Convert bool value to "true" or "false"
    std::string to_str(bool t);

    //! Convert Type to std::string
    template <typename T>
    std::string to_str(const T& t, int align = 0, int precision = 0, char c = ' ')
    {
        std::stringstream ss;
        ss << std::setiosflags(std::ios::fixed) << std::setprecision(precision) << std::setw(align) << std::setfill(c) << t;

        return ss.str();
    }



    //! Parse Type from std::string
    template <typename T>
    T from_str(const std::string& val, T defval = T())
    {
        std::istringstream iss(val);
        T t = T();
        bool result = iss >> t;
        if (!result)
            return defval;
        return t;
    }

    template<>
    std::string from_str<std::string>(const std::string& val, std::string defval);

}

#endif
