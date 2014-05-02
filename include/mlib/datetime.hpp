
#ifndef __DATETIME_HPP__
#define __DATETIME_HPP__

#include <string>
#include <ostream>

namespace mlib
{
    /*! \class DataTime
    **
    */
    class DateTime
    {
    public:
        //! Return current date and time
        static DateTime now();

        std::string date_str() const;
        std::string time_str() const;

        DateTime(int yr, int mt, int dy, int hr, int mn, int sc);
        DateTime(size_t sec);

        int Y() const;
        int M() const;
        int D() const;
        int h() const;
        int m() const;
        int s() const;

        friend std::ostream& operator<<(std::ostream& stream, const DateTime& dt);

    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    };
}

#endif
