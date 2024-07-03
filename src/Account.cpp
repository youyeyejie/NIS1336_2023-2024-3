#include "Account.h"

using namespace std;

extern const string op;
extern const string ed;

Account::Account(const string& filename):filename(filename)
{
    ifstream file(filename);
    if (!file)  ofstream newFile(filename);   
}


Account::~Account()
{
}

//哈希加密
string hashString(const string& input)
{
    hash<string> str_hash;
    size_t hash = str_hash(input);
    return to_string(hash);
}

//检查用户名是否存在
bool isUserExists(const string& username, const string& Account_File) {

    ifstream file(Account_File);
    if (!file.is_open()) {
        cout << "Account file cannot open!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string uid, name, password;

        if (getline(iss, uid, ',') && getline(iss, name, ',') && getline(iss, password)) {
            if (name == username) {
                file.close();
                return true; // 用户名已存在
            }
        }
    }

    file.close();
    return false;// 用户名不存在
}

//获取用户信息
User getUser(const string& username, const string& password, const string& Account_File) {

    User user;
    user.uid = -1;

    ifstream file(Account_File);
    if (!file) {
        cout << "Account file cannot open!" << endl;
        return user;
    }

    string line;
    while (getline(file, line)) {

        istringstream iss(line);
        string uid, name, storedPassword;

        if (getline(iss, uid, ',') && getline(iss, name, ',') && getline(iss, storedPassword)) {
            if (name == username && storedPassword == password) {

                user.uid = stoi(uid);
                user.username = name;
                user.password = password;
                file.close();
                return user; 
            }
        }
    }

    file.close();
    return user; 
}

//获取下一个用户的uid
int getNextUid(const string& Account_File){
    ifstream file(Account_File);
    if (!file) {
        cout << "Account file cannot open!" << endl;
        return -1;
    }


    string line;
    int max_uid=-1;
    while (getline(file, line)) {
        istringstream iss(line);
        string uid, name, storedPassword;

        if (getline(iss, uid, ',') && getline(iss, name, ',') && getline(iss, storedPassword)) {
            max_uid=max(max_uid, stoi(uid));
        }
    }

    file.close();
    return max_uid+1;
}

//写入用户信息
bool writeUser(const User& user, const string& Account_File) {

    ofstream file(Account_File, ios::app);
    if (!file) {
        cout << "Account file cannot open!" << endl;
        return false;
    }

    if (isUserExists(user.username, Account_File)) {
        cout << "User " << user.username << " already exists! Please change your username." << endl;
        return false;
    }
    
    string line = to_string(user.uid) + "," + user.username + "," + user.password + "\n";
    file << line;
    file.close();
    return true;
}

//更新用户信息
bool updateUser(const User& user, const string& Account_File) {

    ifstream file(Account_File);
    if (!file) {
        cout << "Account file cannot open!" << endl;
        return false;
    }

    ofstream tempFile("temp.txt"); // temporary file

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string uid, name, storedPassword;

        if (getline(iss, uid, ',') && getline(iss, name, ',') && getline(iss, storedPassword)) {
            if (name == user.username) {
                tempFile << user.uid << "," << user.username << "," << user.password << "\n";
            }
            else {
                // Write the existing line to the temporary file
                tempFile << line << '\n';
            }
        }
    }

    file.close();
    tempFile.close();

    // replace
    remove(Account_File.c_str());
    rename("temp.txt", Account_File.c_str());

    return true;
}

//删除用户信息
bool deleteUser(const User& user, const string& Account_File) {

    ifstream file(Account_File);
    if (!file) {
        cout << "Account file cannot open!" << endl;
        return false;
    }

    ofstream tempFile("temp.txt"); // temporary file

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string uid, name, storedPassword;

        if (getline(iss, uid, ',') && getline(iss, name, ',') && getline(iss, storedPassword)) {
            if (name != user.username) {
                // Write the existing line to the temporary file
                tempFile << line << '\n';
            }
        }
    }

    file.close();
    tempFile.close();

    // replace
    remove(Account_File.c_str());
    rename("temp.txt", Account_File.c_str());
    string userfile = op + user.username + ed;
    remove(userfile.c_str());
    return true;
}

//获取用户ID
int getUid(const string& Account_File) {

    ifstream file(Account_File);
    if (!file) {
        cout << "Account file cannot open!" << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        string uid, name, storedPassword;

        if (getline(iss, uid, ',') && getline(iss, name, ',') && getline(iss, storedPassword)) {
            continue;
        }
            
        file.close();
        return stoi(uid);
    }

    cout << "No user found!" << endl;
    file.close();
    return -1;
}

//注册账号
bool Account::newAccount(const string& input_username, const string& input_pwd)
{
    // open
    FILE* file = fopen(filename.c_str(), "a");
    if (!file)
    {
        cout << "Account file cannot open!" << endl;
        return false;
    }
    
    //new user
    User NewUser;
    NewUser.username = input_username;
    NewUser.password = hashString(input_pwd);
    NewUser.uid = getNextUid(filename);
    
    // write
    if (writeUser(NewUser, filename) == false)
    {
        return false;
    }

    // close
    fclose(file);

    // create user file
    string user_file = op + input_username + ed;
    //ofstream userFile(user_file);
    FILE* userFile = fopen(user_file.c_str(), "a");
    if (!userFile)
    {
        cout << "User file cannot open!" << endl;
        return false;
    }
    //userFile.close();
    fclose(userFile);
    //cout << "Account created successfully!" << endl;

    return true;
}

//登录
User Account::login(const string& input_username, const string& input_pwd)
{
    // hash
    string hashpwd = hashString(input_pwd);

    // verify
    User user;
    user = getUser(input_username, hashpwd, filename);
    if ( user.uid != -1 ) 
    {
        cout << "Login successful!" << endl;
    } 
    else {
        cout << "Incorrect user name or password. Please check your input." << endl;
    }
    return user;
}

//修改密码
bool Account::changePassword(const string& input_username, const string& OldPwd, const string& NewPwd)
{
    //hash
    string hashOldPwd = hashString(OldPwd);
    string hashNewPwd = hashString(NewPwd);

    // Verify 
    User user = getUser(input_username, hashOldPwd, filename);
    if (user.uid == -1)
    {
        cout << "Incorrect user name or password. Please check your input." << endl;
        return false;
    }

    // Update 
    user.password = hashNewPwd;
    updateUser(user, filename);
    cout << "Password changed successfully!" << endl;
    return true;
}

//删除账号
bool Account::deleteAccount(const string& input_username, const string& input_password)
{
    //hash
    string hashpwd = hashString(input_password);

    // Verify
    User user = getUser(input_username, hashpwd, filename);
    if (user.uid == -1)
    {
        cout << "Incorrect user name or password. Please check your input." << endl;
        return false;
    }

    // Delete
    deleteUser(user, filename);
    cout << "Account deleted successfully!" << endl;
    return true;
}
