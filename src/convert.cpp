
#include "mlib/convert.hpp"

namespace mlib
{
    std::string to_str(bool t)
    {
        std::stringstream ss;
        ss << ((t == true) ? "true" : "false");
        return ss.str();
    }

    template<>
    std::string from_str<std::string>(const std::string& val, std::string defval)
    {
        if (val.empty())
            return defval;
        else
            return val;
    }

}
