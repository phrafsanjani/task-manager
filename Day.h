#ifndef DAY_H
#define DAY_H

#include <vector>
#include "Task.h"

class Day
{
public:
    std::vector<Task>& getTasks() { return tasks; }
private:
    std::vector<Task> tasks;
};

#endif // DAY_H
