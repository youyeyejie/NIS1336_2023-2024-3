#ifndef CLI_H
#define CLI_H

#include "task.h"

using namespace std;

//命令行操作
void displayTask(int argc, char * argv[]);
void addTask(int argc, char * argv[]);
void delTask(int argc, char * argv[]);
void changeTask(int argc, char * argv[]);
//void userLogin(int argc, char * argv[]);
void userRegister(int argc, char * argv[]);
void changePasswd(int argc, char * argv[]);
//void checkTask(int argc, char* argv[]);
// void cmdError();
void displayHelp();
bool checkDateFormat(const string& str);


#endif
