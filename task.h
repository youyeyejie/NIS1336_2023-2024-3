#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <ctime>
#include "Account.h"

using namespace std;

extern const string USER_DIR;

//string转换优先级
Priority convertToPriority(const string& priorityStr);
//string转换类别
Category convertToCategory(const string& categoryStr);
//string转换时间
time_t convertToTime(const string& timeStr);

//优先级转换为string
string convertPriorityToString(Priority priority);
//类别转换为string
string convertCategoryToString(Category category);
//时间转换为string
string convertTimeToString(time_t time);

//获取下一个ID
int getNextId(vector<Task> tasks);

//按开始时间打印任务
void displayTaskByStartTime(const vector<Task>& tasks);
//按优先级打印任务
void displayTaskByPriority(const vector<Task>& tasks);
//按类别打印任务
void displayTaskByCategory(const vector<Task>& tasks);
//按ID打印任务
void displayTaskById(const vector<Task>& tasks);
//按提醒时间
void displayTaskByRemindTime(const vector<Task>& tasks);
//加载任务
vector<Task> loadTaskFromFile(const User* user);
//保存任务
void saveTask2File(const vector<Task>& tasks, const User* user);


#endif