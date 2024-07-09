#ifndef THREAD1_H
#define THREAD1_H

#include "task.h"

//Thread 1
void *thread1(void * arg);


//打印帮助信息
void display_help();
//添加任务
void add_task(void *arg);
//删除任务
void delete_task(void *arg);
//修改任务
void edit_task(void *arg); 
//打印任务列表
void display_task(void *arg);
//注销当前用户
bool deregister(void *arg);
//修改密码
void change_password(void *arg);

//读取任务列表
void load_task(vector<Task> &tasklist, void *arg);
//保存任务列表
void save_task(vector<Task> &tasklist, void *arg);

#endif