#include "Employee.h"

void Employee::setName(std::string name)
{
    this->name = name;
}

void Employee::setSSID(std::string ssid)
{
    this->ssid = ssid;
}

void Employee::setStartTime(Time time)
{
    startTime = time;
}

void Employee::setFinishTime(Time time)
{
    finishTime = time;
}

std::string Employee::getName() const
{
    return name;
}

std::string Employee::getSSID() const
{
    return ssid;
}

Time Employee::getStartTime() const
{
    return startTime;
}

Time Employee::getFinishTime() const
{
    return finishTime;
}

Employee& Employee::operator+=(const Task& task)
{
    tasks.push_back(task);
    return *this;
}
