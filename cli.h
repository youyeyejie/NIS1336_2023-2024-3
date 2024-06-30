#ifndef CLI_H
#define CLI_H

#include "task.h"

using namespace std;

//命令行操作

//打印帮助信息
void displayHelp();
//按照指定方式显示任务
void displayTask(int argc, char * argv[]);
//添加任务
void addTask(int argc, char * argv[]);
//删除任务
void deleteTask(int argc, char * argv[]);
//修改任务的某几个信息
void changeElement(int argc, char * argv[]);
//注册用户
void userRegister(int argc, char * argv[]);
//删除用户
void userDeregister(int argc, char * argv[]);
//修改密码
void changePassword(int argc, char * argv[]);

//void userLogin(int argc, char * argv[]);
//void checkTask(int argc, char* argv[]);
#endif
