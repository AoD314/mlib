
#include "mlib/timer.hpp"
#include "mlib/convert.hpp"
#include "mlib/formatter.hpp"

#include <limits>

namespace mlib
{
    void Timer::CalcSec()
    {
        count_time++;
        seconds_last = static_cast<double>(time_last) / static_cast<double>(fr);
        seconds_total += seconds_last;
        seconds_min = (seconds_min > seconds_last) ? seconds_last : seconds_min;
        seconds_max = (seconds_max < seconds_last) ? seconds_last : seconds_max;

        time_total += time_last;
        time_min = (time_min > time_last) ? time_last : time_min;
        time_max = (time_max < time_last) ? time_last : time_max;
    }

    void Timer::reset()
    {
        seconds_total = 0.0;
        seconds_last = 0.0;
        seconds_min = std::numeric_limits<double>::max();
        seconds_max = std::numeric_limits<double>::min();

        time_total = 0;
        time_last = 0;
        time_min = std::numeric_limits<unsigned long long>::max();
        time_max = std::numeric_limits<unsigned long long>::min();
        count_time = 0;
    }

    unsigned long long Timer::get_time_in_tick() const
    {
        return time_last;
    }

    unsigned long long Timer::get_total_time_in_tick() const
    {
        unsigned long long ret = 0;

        if (mode_c == mode_sum)
        {
            ret = time_total;
        }
        else if (mode_c == mode_min)
        {
            ret = time_min;
        }
        else if (mode_c == mode_max)
        {
            ret = time_max;
        }
        else if (mode_c == mode_avg)
        {
            ret = time_total / count_time;
        }

        return ret;
    }

    Timer::Timer(unsigned long long frequency, TimerModeCount mode)
        : seconds_total(0.0)
        , seconds_last(0.0)
        , seconds_min(std::numeric_limits<double>::max())
        , seconds_max(std::numeric_limits<double>::min())
        , fr(frequency)
        , time_total(0)
        , time_last(0)
        , time_min(std::numeric_limits<unsigned long long>::max())
        , time_max(std::numeric_limits<unsigned long long>::min())
        , count_time(0)
        , time_edx(0)
        , time_edx1(0)
        , time_eax(0)
        , time_eax1(0)
        , mode_p(inAll)
        , mode_c(mode)
    {
    }

    Timer::Timer(TimerModeCount mode)
        : seconds_total(0.0)
        , seconds_last(0.0)
        , seconds_min(std::numeric_limits<double>::max())
        , seconds_max(std::numeric_limits<double>::min())
        , fr(Processor::get_frequency())
        , time_total(0)
        , time_last(0)
        , time_min(std::numeric_limits<unsigned long long>::max())
        , time_max(std::numeric_limits<unsigned long long>::min())
        , count_time(0)
        , time_edx(0)
        , time_edx1(0)
        , time_eax(0)
        , time_eax1(0)
        , mode_p(inAll)
        , mode_c(mode)
    {
    }

    unsigned long long Timer::get_frequency() const
    {
        return fr;
    }

    double Timer::operation_per_second() const
    {
        return 1.0 / seconds_last;
    }

    double Timer::get_time_in_mseconds() const
    {
        return get_time_in_seconds() * 1000.0;
    }

    double Timer::get_time_in_seconds() const
    {
        return seconds_last;
    }

    double Timer::get_time_in_minutes() const
    {
        return seconds_last / 60.0f;
    }

    double Timer::get_time_in_hours() const
    {
        return seconds_last / (60.0f * 60.0f);
    }

    double Timer::get_time_in_days() const
    {
        return seconds_last / (60.0f * 60.0f * 24.0f);
    }

    double Timer::get_total_time_in_seconds() const
    {
        double ret = 0;

        if (mode_c == mode_sum)
        {
            ret = seconds_total;
        }
        else if (mode_c == mode_min)
        {
            ret = seconds_min;
        }
        else if (mode_c == mode_max)
        {
            ret = seconds_max;
        }
        else if (mode_c == mode_avg)
        {
            ret = seconds_total / static_cast<double>(count_time);
        }

        return ret;
    }

    double Timer::get_total_time_in_mseconds() const
    {
        return get_total_time_in_seconds() * 1000;
    }

    double Timer::get_total_time_in_minutes() const
    {
        return get_total_time_in_seconds() / 60.0f;
    }

    double Timer::get_total_time_in_hours() const
    {
        return get_total_time_in_seconds() / (60.0f * 60.0f);
    }

    double Timer::get_total_time_in_days() const
    {
        return get_total_time_in_seconds() / (60.0f * 60.0f * 24.0f);
    }

    void Timer::set_mode(TimerModePrint m)
    {
        mode_p = m;
    }

    std::ostream& operator<<(std::ostream& out, const Timer& t)
    {
        if (t.mode_p == inSec)
        {
            out << t.get_total_time_in_seconds() << " sec";
        }
        else if (t.mode_p == inMin)
        {
            out << t.get_total_time_in_minutes() << " min";
        }
        else if (t.mode_p == inHour)
        {
            out << t.get_total_time_in_hours() << " h";
        }
        else if (t.mode_p == inDays)
        {
            out << t.get_total_time_in_days() << " d";
        }
        else if (t.mode_p == inAll)
        {
            out << mlib::Print::time(t.get_total_time_in_mseconds());
        }

        return out;
    }
}
