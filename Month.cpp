#include "Month.h"

Month::~Month()
{
    delete[] days;
}

void Month::setName(std::string name)
{
    this->name = name;
}

void Month::setDays(bool isLeap)
{
    if (name == "September" || name == "April" || name == "June" || name == "November")
    {
        size = 30;
        days = new Day[size];
    }
    else if (name == "February")
    {
        if (isLeap)
        {
            size = 29;
            days = new Day[size];
        }
        else
        {
            size = 28;
            days = new Day[size];
        }
    }
    else
    {
        size = 31;
        days = new Day[size];
    }
}
