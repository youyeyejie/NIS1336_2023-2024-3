#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "head.h"

using namespace std;

class Account
{
public:
    Account(const string& filename);
    ~Account();
    //注册账号，成功返回true，失败返回false
    bool newAccount(const string& input_username, const string& input_password);
    //登录，成功返回用户信息，失败返回空
    User login(const string& input_username, const string& input_password);
    //修改密码，成功返回true，失败返回false
    bool changePassword(const string& input_username, const string& OldPwd, const string& NewPwd);
    //删除账号，成功返回true，失败返回false
    bool deleteAccount(const string& input_username, const string& input_password);

private:
    string filename;//账户文件名
};


//哈希加密
string hashString(const string& input);
//获取可执行文件所在文件夹路径
string getRootPath();
//检查用户名是否存在
bool isUserExists(const string& username, const string& Account_File);
//获取用户信息,成功返回用户信息，失败返回uid为-1的用户信息
User getUser(const string& username, const string& password, const string& Account_File);
//获取下一个用户的uid
int getNextUid(const string& Account_File);
//写入用户信息,成功返回true，失败返回false
bool writeUser(const User& user, const string& Account_File);
//更新用户信息,成功返回true，失败返回false
bool updateUser(const User& user, const string& Account_File);
//删除用户信息,成功返回true，失败返回false
bool deleteUser(const User& user, const string& Account_File);


#endif
