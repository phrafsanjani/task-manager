#include "Yearbook.h"

Yearbook::Yearbook(unsigned int currentYear)
    : year(currentYear)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        isLeap = true;
    else
        isLeap = false;

    months = new Month[12];

    months[0].setName("January");
    months[0].setDays(isLeap);
    months[1].setName("February");
    months[1].setDays(isLeap);
    months[2].setName("March");
    months[2].setDays(isLeap);
    months[3].setName("April");
    months[3].setDays(isLeap);
    months[4].setName("May");
    months[4].setDays(isLeap);
    months[5].setName("June");
    months[5].setDays(isLeap);
    months[6].setName("July");
    months[6].setDays(isLeap);
    months[7].setName("August");
    months[7].setDays(isLeap);
    months[8].setName("September");
    months[8].setDays(isLeap);
    months[9].setName("October");
    months[9].setDays(isLeap);
    months[10].setName("November");
    months[10].setDays(isLeap);
    months[11].setName("December");
    months[11].setDays(isLeap);
}

void Yearbook::addTask(Task task)
{
    // months[task.getMonth() - 1].getDays()[task.getDay() - 1].getTasks().push_back(task);
    getTasks(task.getDay(), task.getMonth()).push_back(task);
}

std::vector<Task>& Yearbook::getTasks(unsigned int day, unsigned int month)
{
    return months[month - 1].getDays()[day - 1].getTasks();
}

Task Yearbook::getTaskByName(std::string name)
{
    unsigned int size;
    Task task;
    for (unsigned int i = 1; i <= 12; ++i)
    {
        size = getMonths()[i - 1].getSize();
        for (unsigned int j = 1; j <= size; ++j)
            if (!getTasks(j, i).empty())
                for (unsigned int k = 0; k < getTasks(j, i).size(); ++k)
                    if (getTasks(j, i)[k].getName() == name)
                    {
                        task = getTasks(j, i)[k];
                        return task;
                    }
    }
    return task;
}

Yearbook& Yearbook::getInstance(unsigned int currentYear)
{
    static Yearbook yearbook(currentYear);
    return yearbook;
}

Yearbook::~Yearbook()
{
    delete[] months;
}
