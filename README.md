# Task Manager
The goal of this program is managing and assigning tasks to employees of an 
organization. Project details are as follows:
## Features
+ The program must be always ready to get commands from the user.
+ `today` command: shows today's tasks.
+ `month` command: shows current month's tasks.
+ `add task` command: gets a new task from the user(name of the task, beginning 
and ending dates and times of the task in the form `dd-mm hh:mm`) and saves it 
in the file.
+ `find time` command: gets a time in the form `hh:mm` and finds an empty 
interval with the input length in the current month, the empty intervals that 
are closer to the current date are the first prorities. If there were no empty 
intervals, an interval that overlaps less with other intervals should be 
suggested.
+ `now` command: prints current date and time to the console.
+ `free` command: the input of this command is a date and time in the form of 
`dd-mm hh:mm` which removes every task that includes the inpute date & time.
+ `add employee` command: gets an employee's information(name, SSID, and the 
starting and ending time of his/her daily activities) and adds the employee to 
the employees' list.
+ `assign task` command: gets the employee's SSID followed by the task's name 
and assigns the task to the employee.
+ `schedule` command: the input of this command is a date in the form `dd-mm` 
followed by an employee's SSID. It removes the employee's previous tasks in that
 day and then assigns to the employee the maximum subset of the doable tasks in 
the day and prints them to the console(a greedy algorithm).
+ `exit` command: saves the changes in the file and exits the program.
## Implementation
+ The tasks' information should be kept in a binary file.
+ The project's design should be object-oriented. You are only allowed to 
implement the main menu in `main` and the rest of the code has to be implemented
 in an object-oriented structure. Any function outside of class structure has 
negative points(except for `main`).
+ Tasks should have a class structure.
+ Yearbook has to be implemented as a class, containing current year's months.
+ Month has to be implemented as a class, containing days of the month.
+ Each day contains a list of that day's tasks. Use `std::vector` to store this 
list.
## Notes
+ Performance was not a concern in this program.
+ The task's information is stored in a file named `bin`. This file should be 
next to the build files(i.e. in the same directory). If this file doesn't exist,
 it's created and if it exists, it's opened and the information stored in it is 
read by the program.
## Sample
```
 ~ add task
 ~ title is meeting
 ~ starts at 02-01 15:05
 ~ ends at 02-01 15:55
 ~ done
 ~ today
 >     (1) "meeting" [15:05 - 15:55]
 ~ add task
 ~ title is give up
 ~ starts at 02-01 15:45
 ~ ends at 02-01 21:30
 ~ done
 ~ today
 >     (1) "meeting" [15:05 - 15:55]
 >     (2) "give up" [15:45 - 21:30]
 ~ free 02-01 15:20
 ~ today
 >     (1) "give up" [15:45 - 21:30]
 ~ now
 >     02-01 14:35
 ~ find time 1:00
 >     02-01 [14:35 - 15:35]
 ~ add employee
 ~ name is Rick Astley
 ~ ssid is 9134134
 ~ starts at 9:00
 ~ ends at 17:00
 ~ done
 ~ assign task
 ~ ssid is 9134134
 ~ task is give up
 ~ done
```