#ifndef YEARBOOK_H
#define YEARBOOK_H

#include "Month.h"
#include "Employee.h"

/* ------------- NOTE: Yearbook is a singleton class ------------- */
class Yearbook
{
public:
    static Yearbook& getInstance(unsigned int currentTear);
    explicit Yearbook(unsigned int currentYear);
    void addTask(Task task);
    Month* getMonths() { return months; }
    std::vector<Task>& getTasks(unsigned int day, unsigned int month);
    Task getTaskByName(std::string name);
    ~Yearbook();
private:
    Yearbook() {}
    Yearbook(const Yearbook&) = delete;
    Yearbook& operator=(const Yearbook&) = delete;
    Month* months;
    int year;
    bool isLeap;
};

#endif // YEARBOOK_H
