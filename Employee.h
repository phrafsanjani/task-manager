#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <vector>
#include "Time.h"
#include "Task.h"

class Employee
{
public:
    void setName(std::string name);
    void setSSID(std::string ssid);
    void setStartTime(Time time);
    void setFinishTime(Time time);
    std::string getName() const;
    std::string getSSID() const;
    Time getStartTime() const;
    Time getFinishTime() const;
    std::vector<Task>& getTasks() { return tasks; }
    Employee& operator+=(const Task& task);
private:
    std::string name;
    std::string ssid;
    Time startTime;
    Time finishTime;
    std::vector<Task> tasks;
};

#endif // EMPLOYEE_H
