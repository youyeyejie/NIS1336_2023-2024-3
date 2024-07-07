#ifndef THREAD1_H
#define THREAD1_H

#include "task.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <istream>
#include <sstream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <ctime>
using namespace std;

class TaskManager//前向声明




class USER{
private:
  string password_hash;//用户密码用hash保存
  int UID;//用户名
  //读取文件
  friend int userfile_read(const string &);
  //写入用户数据
  friend int userfile_update(const string &);
  //用户注册
  friend int rigist(const string& name,const string& passwd);
  //用户登录检验
  friend int user_check(const string& name,const string& passwd);
  //改密码
  friend void change_passwd(int uid_change);
  //删除用户
  friend bool dele_user(int uid_dele);
public:
  string username;
  bool is_admin;
};



struct Task{
  int taskId;
  string task_name;
  string start_name;
  int priority;
  string category;
  string  attention_time;
  bool printedReminder;//标记是否打印过
}；
class TaskManager{
private:
  vector<Task> tasks;
  int taskIdCounter;
  unordered_set<string> uniqueTaskIdentifiers;//储存任务名称+开始时间

  void updateTaskIds();
  //比较函数，用于按开始时间排序
  static bool compareTasksByStartTime(const Task& task1,const Task& task2);
  //设置默认的注意时间
  void setDefaultAttentionTime(Task& task);
  //将时间解析为std::tm结构体
  tm parseTime(const string& timeStr);
public:
  TaskManager();
  //添加任务
  void addTask(const string& task_name, const string& start_time, int priority,const string& category,const string& attention_time);
  //删除任务
  void deleteTask(int taskId);
  //展示任务
  void showTask(const string& date = "",const string& month = "",const string& category = "");
  //读取任务
  void readFromFile(const string& userfilename);
  //写任务
  void write2File(const string& userfilename);
  //提醒
  void checkAttentionTime();
};

extern map<int ,USER> userinfo;
extern int UID_NUM;
extern int UID_CURR;
extern string uidFilename;
extern std::string taskfilename;


//管理权限修改
void admin_change(int admin_add_uid,int i);
//展示用户
void show_user();
void *thread1(void * arg);
//切换登录
void su_user(int su_uid, TaskManager& task_manager)；
#endif
