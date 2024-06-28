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

//获取最小ID
int getminId(vector<Task> tasks);

//打印任务
void showTask(const vector<Task>& tasks);
//加载任务
void loadTask(vector<Task>& tasks, const User* user);
//保存任务
void saveTask(const vector<Task>& tasks, const User* user);


#endif