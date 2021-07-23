#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>

class Time
{
    friend std::ostream& operator<<(std::ostream& ouput, const Time& time);
public:
    explicit Time(unsigned int h = 0, unsigned int m = 0);
    void setHour(unsigned int hour);
    void setMinute(unsigned int minute);
    bool operator==(const Time& time) const;
    bool operator<(const Time& time) const;
    bool operator>(const Time& time) const;
    bool operator>=(const Time& time) const;
    bool operator<=(const Time& time) const;
    Time operator-(const Time& time);
    Time operator+(const Time& time);
private:
    unsigned int hour;
    unsigned int minute;
};

#endif // TIME_H
