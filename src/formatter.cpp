#include "mlib/formatter.hpp"
#include "mlib/convert.hpp"

std::string mlib::Print::size(int64_t byte)
{
    if (byte < 0) byte = 0;

    if (byte < 1024)
    {
        return to_str(byte) + " byte";
    }

    double kb = static_cast<double>(byte) / 1024.0;
    if (kb < 1024.0)
    {
        return to_str(kb, 0, 3) + " Kb";
    }

    double mb = static_cast<double>(byte) / (1024.0 * 1024.0);
    if (mb < 1024.0)
    {
        return to_str(mb, 0, 3) + " Mb";
    }

    double gb = static_cast<double>(byte) / (1024.0 * 1024.0 * 1024.0);
    if (gb < 1024.0)
    {
        return to_str(gb, 0, 3) + " Gb";
    }

    double tb = static_cast<double>(byte) / (1024.0 * 1024.0 * 1024.0 * 1024.0);
    return to_str(tb, 0, 4) + " Tb";
}

std::string mlib::Print::time(int64_t msec)
{
    if (msec < 0) msec = 0;
    uint32_t sec = static_cast<uint32_t>(msec / 1000);
    msec -= sec * 1000;
    uint32_t min = sec / 60;
    sec -= min * 60;
    uint32_t h = min / 60;
    min -= h * 60;

    return to_str(h) + ":" + to_str(min, 2, 0, '0') + ":" + to_str(sec, 2, 0, '0') + "." + to_str(msec, 3, 0, '0');
}

std::string mlib::Print::percent(int64_t i, int64_t total)
{
    if (i < 0) i = 0;
    if (total <= 0) total = 1;
    if (i > total) i = total;

    return to_str(double(i * 100.0) / double(total), 0, 2) + "%";
}
