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
  //用于访问private的友元函数
  friend int userfile_read(const string &);
  friend int userfile_update(const string &);
  friend int rigist(const string& name,const string& passwd);
  friend int user_check(const string& name,const string& passwd);
  friend void change_passwd(int uid_change);
  friend bool dele_user(int uid_dele);
public:
  string username;
  bool is_admin;
};



extern map<int ,USER> userinfo;
extern int UID_NUM;
extern int UID_CURR;
extern string uidFilename;



void admin_change(int admin_add_uid,int i);
void show_user();
void *thread1(void * arg);

#endif
