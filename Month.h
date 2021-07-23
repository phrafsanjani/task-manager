#ifndef MONTH_H
#define MONTH_H

#include <iostream>
#include "Day.h"

class Month
{
public:
    ~Month();
    void setName(std::string name);
    void setDays(bool isLeap);
    Day* getDays() { return days; }
    unsigned int getSize() const { return size; }
private:
    unsigned int size;
    std::string name;
    Day* days;
};

#endif // MONTH_H
