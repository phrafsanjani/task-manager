#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Employee.h"
#include "Task.h"
#include "Yearbook.h"
// #pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

using namespace std;

int main()
{
    string command;
    vector<Employee> employees;
    time_t now = time(0);
    unsigned int year = localtime(&now)->tm_year + 1900;
    Yearbook& yearbook = Yearbook::getInstance(year);
    Task task;
    static unsigned int tasksCount = 0;

    fstream binFile;
    binFile.open("bin", ios::binary | ios::in | ios::out);
    if (!binFile)
    {
        binFile.open("bin", ios::binary | ios::out);
        if (!binFile)
            cerr << " > error: failed to open file!\n";
    }
    else
    {
        binFile.read(reinterpret_cast<char*>(&tasksCount), sizeof(tasksCount));
        for (unsigned int i = 0; i < tasksCount; ++i)
        {
            binFile.read(reinterpret_cast<char*>(&task), sizeof(task));
            if (binFile.eof())
                break;
            yearbook.addTask(task);
        }

        binFile.close();
        binFile.open("bin", ios::binary | ios::out);
    }

    while (true)
    {
        try
        {
            cout << " ~ ";
            getline(cin, command);
            if (command == "exit")
            {
                binFile.seekp(0, ios::beg);
                binFile.write(reinterpret_cast<char*>(&tasksCount), sizeof(tasksCount));
                unsigned int size;
                for (unsigned int i = 1; i <= 12; ++i)
                {
                    size = yearbook.getMonths()[i - 1].getSize();
                    for (unsigned int j = 1; j <= size; ++j)
                        if (!yearbook.getTasks(j, i).empty())
                            for (unsigned int k = 0; k < yearbook.getTasks(j, i).size(); ++k)
                                binFile.write(reinterpret_cast<char*>(&yearbook.getTasks(j, i)[k]), sizeof(task));
                }
                binFile.close();
                break;
            }
            else if (command == "now")
            {
                now = time(0);
                tm* localTime = localtime(&now);
                cout << " > \t" << setfill('0') << setw(2) << localTime->tm_mday
                     << "-" << setfill('0') << setw(2) << localTime->tm_mon + 1 << " "
                     << localTime->tm_hour << ':' << setfill('0') << setw(2)
                     << localTime->tm_min << '\n';
            }
            else if (command == "today")
            {
                unsigned int month = localtime(&now)->tm_mon + 1;
                unsigned int day = localtime(&now)->tm_mday;

                vector<Task>& tasks = yearbook.getTasks(day, month);
                // sort(tasks.begin(), tasks.end(), CompareStartTimes());
                unsigned int size = tasks.size();

                if (!tasks.empty())
                    for (unsigned int i = 0; i < size; ++i)
                        cout << " > \t(" << i + 1 << ") " << tasks[i] << '\n';
                else
                    throw logic_error("no tasks for today!");
            }
            else if (command == "month")
            {
                unsigned int count = 1;
                bool monthIsEmpty = true;
                unsigned int month = localtime(&now)->tm_mon + 1;
                unsigned int monthDaysCount = yearbook.getMonths()[month - 1].getSize();

                for (unsigned int i = 1; i <= monthDaysCount; ++i)
                    if (!yearbook.getTasks(i, month).empty())
                    {
                        vector<Task>& tasks = yearbook.getTasks(i, month);
                        // sort(tasks.begin(), tasks.end(), CompareStartTimes());
                        unsigned int size = tasks.size();
                        monthIsEmpty = false;
                        for (unsigned int j = 0; j < size; ++j)
                            cout << " > \t(" << count++ << ") " << setfill('0') << setw(2)
                                 << tasks[j].getDay() << '-' << setfill('0') << setw(2)
                                 << tasks[j].getMonth() << ' ' << tasks[j] << '\n';
                    }
                if (monthIsEmpty)
                    throw logic_error("no tasks for this month!");
            }
            else if (command.find("free") != string::npos)
            {
                size_t pos = command.find('-');
                unsigned int day = stoul(command.substr((pos - 2), pos));
                unsigned int month = stoul(command.substr(pos + 1, pos + 3));
                pos = command.find(':');
                unsigned int hour = stoul(command.substr(pos - 2, pos));
                unsigned int minute = stoul(command.substr(pos + 1, pos + 3));
                Time time(hour, minute);
                vector<Task>& tasks = yearbook.getTasks(day, month);
                unsigned int tasksNum = tasks.size();
                vector<Task>::iterator it = tasks.begin();
                for (unsigned int i = 0; i < tasksNum; ++i)
                    if (tasks[i].getStartTime() <= time && tasks[i].getFinishTime() >= time)
                    {
                        tasks.erase(it + i);
                        --tasksCount;
                    }
            }
            else if (command.find("find time") != string::npos)
            {
                time_t now = time(0);
                size_t pos;
                unsigned int hour;
                unsigned int minute;
                bool found = false;
                unsigned int monthNum = localtime(&now)->tm_mon + 1;
                unsigned int today = localtime(&now)->tm_mday;
                Time thisTime(localtime(&now)->tm_hour, localtime(&now)->tm_min);

                pos = command.find(':');
                hour = stoul(command.substr(pos - 2, pos));
                minute = stoul(command.substr(pos + 1, pos + 3));
                Time duration(hour, minute);
                Month& thisMonth = yearbook.getMonths()[monthNum - 1];
                unsigned int thisMonthDaysNum = thisMonth.getSize();
                for (unsigned int i = today - 1; i < thisMonthDaysNum && !found; ++i)
                {
                    if (yearbook.getTasks((i + 1), monthNum).empty())
                    {
                        found = true;
                        cout << " > \t" << setfill('0') << setw(2) << today
                             << '-' << setfill('0') << setw(2) << monthNum
                             << " [" << thisTime << " - "
                             << thisTime + duration << "]\n";
                        break;
                    }

                    vector<Task>& tasks = yearbook.getTasks(i + 1, monthNum);
                    sort(tasks.begin(), tasks.end(), CompareStartTimes());
                    vector<Task>::iterator it;
                    unsigned int tasksSize = tasks.size();

                    if (i == today - 1)
                        for (unsigned int j = 0; j < tasksSize; ++j)
                            if (tasks[j].getFinishTime() <= thisTime)
                                tasks.erase(it + j);

                    if (tasks.front().getStartTime() >= thisTime &&
                        tasks.front().getStartTime() - thisTime >= duration)
                    {
                        found = true;
                        cout << " > \t" << setfill('0') << setw(2) << today
                             << '-' << setfill('0') << setw(2) << monthNum
                             << " [" << thisTime << " - "
                             << thisTime + duration << "]\n";
                        break;
                    }

                    for (unsigned int j = 0; j < tasksSize - 1; ++j)
                    {
                        if (!tasks[j].overlap(tasks[j + 1]) &&
                            tasks[j + 1].getStartTime() - tasks[j].getFinishTime() >= duration)
                        {
                            found = true;
                            cout << " > \t" << setfill('0') << setw(2) << today
                                 << '-' << setfill('0') << setw(2) << monthNum
                                 << " [" << tasks[j].getFinishTime() << " - "
                                 << tasks[j].getFinishTime() + duration << "]\n";
                            break;
                        }
                    }

                    sort(tasks.begin(), tasks.end(), CompareFinishTimes());
                    Time& finishTasksTime = tasks.back().getFinishTime();
                    if (!found && finishTasksTime <= Time(23, 59) &&
                        Time(23, 59) - finishTasksTime >= duration)
                    {
                        found = true;
                        cout << " > \t" << setfill('0') << setw(2) << today
                             << '-' << setfill('0') << setw(2) << monthNum
                             << " [" << finishTasksTime << " - "
                             << finishTasksTime + duration << "]\n";
                        break;
                    }
                }
                if (!found)
                {
                     for (unsigned int i = today - 1; i < thisMonthDaysNum; ++i)
                     {
                         if (yearbook.getTasks((i + 1), monthNum).empty())
                             continue;

                         vector<Task>& tasks = yearbook.getTasks(i + 1, monthNum);
                         unsigned int tasksSize = tasks.size();
                         sort(tasks.begin(), tasks.end(), CompareStartTimes());
                         Task chosenTask;
                         unsigned int chosenDay;
                         unsigned int overlapCount{0};

                         for (unsigned int j = 0; j < tasksSize; ++j)
                             for (unsigned int k = 0; k < tasksSize; ++k)
                                 if (!tasks[j].overlap(tasks[k]))
                                 {
                                     if (overlapCount == 0 || k - 1 < overlapCount)
                                     {
                                         chosenDay = i;
                                         chosenTask = tasks[j];
                                         overlapCount = k - 1;
                                     }
                                     break;
                                 }
                         cout << " > \t" << setfill('0') << setw(2) << chosenDay
                              << '-' << setfill('0') << setw(2) << monthNum
                              << " [" << chosenTask.getStartTime() << " - "
                              << chosenTask.getStartTime() + duration << "]\n";
                     }
                }
            }
            else if (command.find("schedule") != string::npos)
            {
                size_t pos;
                string ssid;
                unsigned int day, month;
                bool employeeFound = false;

                pos = command.find('-');
                day = stoul(command.substr(pos - 2, pos));
                month = stoul(command.substr(pos + 1, pos + 3));
                ssid = command.substr(pos + 4);

                for (unsigned int i = 0; i < employees.size(); ++i)
                    if (employees[i].getSSID() == ssid)
                    {
                        employeeFound = true;
                        Employee& employee = employees[i];
                        employee.getTasks().clear();
                        vector<Task>& tasks = yearbook.getTasks(day, month);
                        sort(tasks.begin(), tasks.end(), CompareFinishTimes());
                        for (unsigned int i = 0; i < tasks.size(); ++i)
                            if (i == 0 || employee.getTasks().back().getFinishTime() <=
                                                            tasks[i].getStartTime())
                            {
                                employee.getTasks().push_back(tasks[i]);
                                cout << " > " << tasks[i] << '\n';
                            }
                        break;
                    }
                if (!employeeFound)
                    throw invalid_argument("employee not found!");
            }
            else if (command == "assign task")
            {
                size_t pos;
                string ssid;
                string taskName;
                unsigned int queryNum = 0;

                while (command != "done")
                {
                    cout << " ~ ";
                    getline(cin, command);
                    if (queryNum == 0)
                    {
                        if (command == "done")
                            break;
                        pos = command.find("is") + 3;
                        ssid = command.substr(pos);
                        ++queryNum;
                        continue;
                    }
                    if (queryNum == 1)
                    {
                        pos = command.find("is") + 3;
                        taskName = command.substr(pos);
                        task = yearbook.getTaskByName(taskName);
                        if (!task.getName())
                            throw logic_error("task not found!");
                        bool employeeFound = false;
                        for (unsigned int i = 0; i < employees.size(); ++i)
                            if (employees[i].getSSID() == ssid)
                            {
                                employeeFound = true;
                                employees[i] += task;
                                break;
                            }
                        if (!employeeFound)
                            throw logic_error("employee not found!");
                        queryNum = 0;
                    }
                }
            }
            else if (command == "add employee")
            {
                Employee employee;
                size_t pos, fpos, spos;
                unsigned int hour, minute;
                unsigned int queryNum = 0;

                while (command != "done")
                {
                    cout << " ~ ";
                    getline(cin, command);
                    if (queryNum == 0)
                    {
                        if (command == "done")
                            break;
                        pos = command.find("is") + 3;
                        employee.setName(command.substr(pos));
                        ++queryNum;
                        continue;
                    }
                    if (queryNum == 1)
                    {
                        pos = command.find("is") + 3;
                        employee.setSSID(command.substr(pos));
                        ++queryNum;
                        continue;
                    }
                    if (queryNum == 2)
                    {
                        fpos = command.find("at") + 3;
                        spos = command.find(':');
                        hour = stoul(command.substr(fpos, spos));
                        minute = stoul(command.substr(spos + 1));
                        employee.setStartTime(Time(hour, minute));
                        ++queryNum;
                        continue;
                    }
                    if (queryNum == 3)
                    {
                        fpos = command.find("at") + 3;
                        spos = command.find(':');
                        hour = stoul(command.substr(fpos, spos));
                        minute = stoul(command.substr(spos + 1));
                        employee.setFinishTime(Time(hour, minute));
                        employees.push_back(employee);
                        queryNum = 0;
                        //checking employee details
                        /*
                        cout << " > added employee with following details:"
                             << "\n > name : " << employee.getName()
                             << "\n > ssid : " << employee.getSSID()
                             << "\n > start time : " << employee.getStartTime()
                             << "\n > finish time : " << employee.getFinishTime() << '\n';
                        */
                    }
                }
            }
            else if (command == "add task")
            {
                // Task task;
                unsigned int hour, minute, day, month;
                unsigned int queryNum = 0;
                size_t pos, fpos, spos;

                while (command != "done")
                {
                    cout << " ~ ";
                    getline(cin, command);
                    if (queryNum == 0)
                    {
                        if (command == "done")
                            break;
                        pos = command.find("is") + 3;
                        task.setName(command.substr(pos));
                        ++queryNum;
                        continue;
                    }
                    if (queryNum == 1)
                    {
                        fpos = command.find('-') - 2;
                        spos = command.find('-');
                        day = stoul(command.substr(fpos, spos));
                        fpos = spos;
                        month = stoul(command.substr(fpos + 1, fpos + 3));
                        fpos += 4;
                        spos = command.find(':');
                        hour = stoul(command.substr(fpos, spos));
                        minute = stoul(command.substr(spos + 1));
                        // checking details
                        /*
                        cout << " > day = " << day
                             << "\n > month = " << month << "\n > hour = " << hour
                             << "\n > minute = " << minute << '\n';
                        */
                        task.setStartTime(Time(hour, minute));
                        task.setDay(day);
                        task.setMonth(month);
                        ++queryNum;
                        continue;
                    }
                    if (queryNum == 2)
                    {
                        // fpos = command.find('-') - 2;
                        spos = command.find('-');
                        // day = stoul(command.substr(fpos, spos));
                        fpos = spos;
                        // month = stoul(command.substr(fpos + 1, fpos + 3));
                        fpos += 4;
                        spos = command.find(':');
                        hour = stoul(command.substr(fpos, spos));
                        minute = stoul(command.substr(spos + 1));
                        // checking details
                        /*
                        cout << " > day = " << day
                             << "\n > month = " << month << "\n > hour = " << hour
                             << "\n > minute = " << minute << '\n';
                        */
                        task.setFinishTime(Time(hour, minute));
                        yearbook.addTask(task);
                        ++tasksCount;
                        queryNum = 0;
                    }
                }
            }
            else
                throw invalid_argument("invalid command!");
        }
        catch (exception& err)
        {
            cout << " > error: "  << err.what() << '\n';
        }
    }
    return 0;
}
