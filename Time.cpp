#include "Time.h"

Time::Time(unsigned int hour, unsigned int minute)
{
    setHour(hour);
    setMinute(minute);
}

std::ostream& operator<<(std::ostream& output, const Time& time)
{
    output << std::setfill('0') << std::setw(2) << time.hour << ':'
           << std::setfill('0') << std::setw(2) << time.minute;
    return output;
}

void Time::setHour(unsigned int hour)
{
    if (hour < 24)
        this->hour = hour;
    else
        throw std::out_of_range("invalid value for hour!");
}

void Time::setMinute(unsigned int minute)
{
    if (minute < 60)
        this->minute = minute;
    else
        throw std::out_of_range("invalid value for minute!");
}


bool Time::operator==(const Time& time) const
{
    return hour == time.hour && minute == time.minute;
}

bool Time::operator<(const Time& time) const
{
    if (hour < time.hour)
        return true;
    else if (hour > time.hour)
        return false;
    return minute < time.minute;
}

bool Time::operator<=(const Time& time) const
{
    return *this < time || *this == time;
}

bool Time::operator>(const Time& time) const
{
    return !(*this <= time);
}

bool Time::operator>=(const Time& time) const
{
    return *this > time || *this == time;
}


Time Time::operator-(const Time& time)
{
    Time resultTime;
    if (*this < time)
        throw std::logic_error("invalid subtraction for class Time operands!");
    else if (*this == time)
        return resultTime;
    else if (hour == time.hour)
            resultTime.setMinute(minute - time.minute);
    else
    {
        unsigned int temp = 60 * (hour - time.hour) + minute - time.minute;
        resultTime.setHour(temp / 60);
        resultTime.setMinute(temp % 60);
    }
    return resultTime;
}

Time Time::operator+(const Time& time)
{
    Time resultTime;
    resultTime.setMinute((minute + time.minute) % 60);
    resultTime.setHour((hour + time.hour + (minute + time.minute) / 60) % 24);
    return resultTime;
}
