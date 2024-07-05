#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <string>
#include <ctime> 
#include <algorithm>
#include <regex>
#include <functional>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h> 
#include <sys/file.h> 
#include <sys/types.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

const string op = "./Data/User/";
const string ed = "_tasks.txt";
const string account_filename = "./Data/Account.txt";

//任务优先级:1.高 2.中 3.低
enum Priority{
    HIGH, MODERATE, LOW
};

//任务类别:1.学习 2.生活 3.娱乐
enum Category{
    STUDY, LIFE, ENTERTAINMENT, NONE
};

struct Task
{
    int id; 
    string name;
    Priority prio;  //任务优先级
    Category cat;   //类别
    time_t start_time;  //任务启动时间
    time_t remind_time; //任务提醒时间
    string detail;   //任务详细信息
}; 

struct User
{
    int uid; 
    string username;
    string password; 
};

struct ThreadInfo
{
    User* user;
    pthread_mutex_t* mutex;
    bool running;
};



#endif
