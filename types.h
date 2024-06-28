//枚举类型定义及类定义

#ifndef TYPES_H
#define TYPES_H
#include <ctime>
#include <pthread.h>

//任务优先级:1.高 2.中 3.低
enum Priority{
    HIGH, MODERATE, LOW
};

//任务类别:1.学习 2.生活 3.娱乐
enum Category{
    STUDY, LIFE, ENTERTAINMENT
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
    static int uid; 
    string username;
    string password; 
};

struct ThreadInfo
{
    User* user;
    pthread_mutex_t* mutex;
    bool running;
};

int User::uid = 0;

#endif