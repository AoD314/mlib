
#include "mlib/safe_call.hpp"
#include "mlib/exception.hpp"

extern "C" {
#undef UINT64_C
#define UINT64_C(val) val##LL
#include <libavutil/error.h>
}

namespace mlib
{
    void ffmpeg_safe_call(int err, const std::string& file, unsigned long line)
    {
        if (err == 0)
            return;

        size_t size = 2048;
        char* message = new char[size];
        int ret = av_strerror(err, message, size);

        delete[] message;

        if (ret != 0)
        {
            return;
        }

        throw mlib::Exception(message, file, line);
    }
}
