#include "Task.h"

std::ostream& operator<<(std::ostream& output, const Task& task)
{
    output << '\"' << task.name << "\" [" << task.startTime << " - "
                                          << task.finishTime << ']';
    return output;
}

void Task::setName(std::string name)
{
    name = name.c_str();
    unsigned int i = 0;
    while (name[i])
    {
        this->name[i] = name[i];
        ++i;
    }
    this->name[i] = name[i];
}

void Task::setStartTime(Time time)
{
    startTime = time;
}

void Task::setFinishTime(Time time)
{
    if (time >= startTime)
        finishTime = time;
    else
        throw std::invalid_argument("finish time cannot be less than start time!");
}

void Task::setDay(unsigned int day)
{
    this->day = day;
}

void Task::setMonth(unsigned int month)
{
    this->month = month;
}

bool Task::overlap(const Task& task)
{
    return (finishTime >= task.startTime && task.finishTime >= startTime) ||
           (task.finishTime >= startTime && finishTime >= task.startTime);
}
