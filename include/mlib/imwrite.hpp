
#ifndef __imwrite_hpp__
#define __imwrite_hpp__

#include "mlib/image.hpp"

/// \todo TODO: implement write using webp(lossless by default)

namespace mlib
{
    void write (std::string filename, Image img, unsigned char compress = 101);
}

#endif
