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



extern map<int ,USER> userinfo;
extern int UID_NUM;
extern int UID_CURR;
extern string uidFilename;


//管理权限修改
void admin_change(int admin_add_uid,int i);
//展示用户
void show_user();
void *thread1(void * arg);
//切换登录
void su_user(int su_uid, TaskManager& task_manager)；
#endif
