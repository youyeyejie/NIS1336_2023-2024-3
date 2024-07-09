#ifndef TASKS_H
#define TASKS_H

#include "Account.h"

using namespace std;

extern const string op;
extern const string ed;

//string转换优先级
Priority convertStringToPriority(const string& priorityStr);
//string转换类别
Category convertStringToCategory(const string& categoryStr);
//string转换时间
time_t convertStringToTime(const string& timeStr);


//优先级转换为string
string convertPriorityToString(Priority priority);
//类别转换为string
string convertCategoryToString(Category category);
//时间转换为string
string convertTimeToString(time_t time);
//默认提醒时间为一天
string getDefaultRemindTime(time_t time);


//获取下一个ID
int getNextId(vector<Task> tasks);
//检查日期格式
bool checkDateFormat(const string& str);
//检查id格式
bool checkIdFormat(const string id);
//检查提醒时间
void checkRemindTime(const vector<Task> tasks);


//打印单个任务
void displaySingleTask(const Task& task);
//打印表头
void displayTaskTitle();
//按开始时间打印任务
void displayTaskByStartTime(const vector<Task>& tasks);
//按优先级打印任务
void displayTaskByPriority(const vector<Task>& tasks);
//按类别打印任务
void displayTaskByCategory(const vector<Task>& tasks);
//按ID打印任务
void displayTaskById(const vector<Task>& tasks);
//按提醒时间打印任务
void displayTaskByRemindTime(const vector<Task>& tasks);


//加载任务
vector<Task> loadTaskFromFile(const User* user);
//保存任务
void saveTask2File(const vector<Task>& tasks, const User* user);


#endif
