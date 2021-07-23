#ifndef TASK_H
#define TASK_H

#include <iostream>
#include "Time.h"
#define MAX_NAME_SIZE 16

class Task
{
    friend std::ostream& operator<<(std::ostream& output, const Task& task);
public:
    void setName(std::string name);
    void setStartTime(Time time);
    void setFinishTime(Time time);
    void setMonth(unsigned int month);
    void setDay(unsigned int day);
    unsigned int getDay() const { return day; }
    unsigned int getMonth() const { return month; }
    const Time& getStartTime() const { return startTime; }
    const Time& getFinishTime() const { return finishTime; }
    Time& getStartTime() { return startTime; }
    Time& getFinishTime() { return finishTime; }
    const Time getTaskDuration() { return finishTime - startTime; }
    const char* getName() const { return name; };
    bool overlap(const Task& task);
private:
    char name[MAX_NAME_SIZE + 1];
    Time startTime;
    Time finishTime;
    unsigned int month;
    unsigned int day;
};

class CompareStartTimes
{
public:
    inline bool operator()(const Task& first, const Task& second)
    {
        return first.getStartTime() < second.getStartTime();
    }
};

class CompareFinishTimes
{
public:
    inline bool operator()(const Task& first, const Task& second)
    {
        return first.getFinishTime() < second.getFinishTime();
    }
};

#endif // TASK_H
