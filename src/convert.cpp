
#include "mlib/convert.hpp"

namespace mlib
{
    std::string to_str(bool t)
    {
        std::stringstream ss;
        ss << ((t == true) ? "true" : "false");
        return ss.str();
    }
}
