#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/file.h> 
#include <sys/types.h> // Add this line to include the appropriate header file for 'fcntl'
#include "task.h"

using namespace std;

//string转换优先级
Priority convertToPriority(const string& priorityStr) {
    if (priorityStr == "HIGH") 
    {
        return HIGH;
    } 
    else if (priorityStr == "MODERATE") 
    {
        return MODERATE;
    } 
    else if (priorityStr == "LOW") 
    {
        return LOW;
    } 
    else 
    {
        return LOW;//默认
    }
}

//string转换类别
Category convertToCategory(const string& categoryStr) {
    if (categoryStr == "STUDY") 
    {
        return STUDY;
    } 
    else if (categoryStr == "LIFE") 
    {
        return LIFE;
    } 
    else if (categoryStr == "ENTERTAINMENT") 
    {
        return ENTERTAINMENT;
    } 
    else 
    {
        return STUDY;//默认
    }
}

//string转换时间
time_t convertToTime(const string& timeStr) {
    // timeStr:YYYY-MM-DD HH:MM:SS
    tm time = {};
    istringstream iss(timeStr);
    iss >> get_time(&time, "%Y-%m-%d %H:%M:%S");
    return mktime(&time);
}

//优先级转换为string
string convertPriorityToString(Priority priority) {
    if (priority == HIGH) 
    {
        return "HIGH";
    } 
    else if (priority == MODERATE) 
    {
        return "MODERATE";
    } 
    else if (priority == LOW) 
    {
        return "LOW";
    } 
    else 
    {
        return "NONE";
    }
}

//类别转换为string
string convertCategoryToString(Category category) {
    if (category == STUDY) 
    {
        return "STUDY";
    } 
    else if (category == LIFE) 
    {
        return "LIFE";
    } 
    else if (category == ENTERTAINMENT) 
    {
        return "ENTERTAINMENT";
    } 
    else 
    {
        return "NONE";
    }
}

//时间转换为string
string convertTimeToString(time_t time) {
    struct tm* timeinfo = localtime(&time);
    stringstream ss;
    ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

//获取下一个ID
int getNextId(vector<Task> tasks) {
    if (tasks.empty()) 
    {
        return 1;
    } 
    else 
    {
        int maxId = 0;
        for (const Task& task : tasks) 
        {
            if (task.id > maxId) 
            {
                maxId = task.id;
            }
        }
        return maxId + 1;
    }
}

//按开始时间打印任务
void displayTaskByStartTime(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.start_time < t2.start_time;
    });

    cout << "ID\tName\t\t\tStart Time\t\t\tPriority\tCategory\t\tRemind Time\t\tDetail" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
        cout << setw(2) << task.id << "\t" << setw(12) << task.name << "\t" << setw(24) << convertTimeToString(task.start_time) << "\t"
             << setw(12) << convertPriorityToString(task.prio) << "\t" << setw(16) << convertCategoryToString(task.cat) << "\t"
             << setw(24) << convertTimeToString(task.remind_time) << "\t" << task.detail << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按优先级打印任务
void displayTaskByPriority(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.prio < t2.prio;
    });

    cout << "ID\tName\t\t\tStart Time\t\t\tPriority\tCategory\t\tRemind Time\t\tDetail" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
        cout << setw(2) << task.id << "\t" << setw(12) << task.name << "\t" << setw(24) << convertTimeToString(task.start_time) << "\t"
             << setw(12) << convertPriorityToString(task.prio) << "\t" << setw(16) << convertCategoryToString(task.cat) << "\t"
             << setw(24) << convertTimeToString(task.remind_time) << "\t" << task.detail << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按类别打印任务
void displayTaskByCategory(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.cat < t2.cat;
    });

    cout << "ID\tName\t\t\tStart Time\t\t\tPriority\tCategory\t\tRemind Time\t\tDetail" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
        cout << setw(2) << task.id << "\t" << setw(12) << task.name << "\t" << setw(24) << convertTimeToString(task.start_time) << "\t"
             << setw(12) << convertPriorityToString(task.prio) << "\t" << setw(16) << convertCategoryToString(task.cat) << "\t"
             << setw(24) << convertTimeToString(task.remind_time) << "\t" << task.detail << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按ID打印任务
void displayTaskById(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.id < t2.id;
    });

    cout << "ID\tName\t\t\tStart Time\t\t\tPriority\tCategory\t\tRemind Time\t\tDetail" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
        cout << setw(2) << task.id << "\t" << setw(12) << task.name << "\t" << setw(24) << convertTimeToString(task.start_time) << "\t"
             << setw(12) << convertPriorityToString(task.prio) << "\t" << setw(16) << convertCategoryToString(task.cat) << "\t"
             << setw(24) << convertTimeToString(task.remind_time) << "\t" << task.detail << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按提醒时间打印任务
void displayTaskByRemindTime(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.remind_time < t2.remind_time;
    });

    cout << "ID\tName\t\t\tStart Time\t\t\tPriority\tCategory\t\tRemind Time\t\tDetail" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
        cout << setw(2) << task.id << "\t" << setw(12) << task.name << "\t" << setw(24) << convertTimeToString(task.start_time) << "\t"
             << setw(12) << convertPriorityToString(task.prio) << "\t" << setw(16) << convertCategoryToString(task.cat) << "\t"
             << setw(24) << convertTimeToString(task.remind_time) << "\t" << task.detail << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//加载任务
vector<Task> loadTaskFromFile(const User* user) {
    vector<Task> tasks;
    string filename = USER_DIR + user->username + ".txt" ;

    //begin lock
    int fd = open((USER_DIR + user->username).c_str(), O_RDWR);
    if(fd == -1){
        FILE* fp = fopen((USER_DIR + user->username).c_str(), "w");
        fclose(fp);
        fd = open((USER_DIR + user->username).c_str(), O_RDWR);
    }
    
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();

    fcntl(fd, F_SETLKW, &fl);
    //end lock

    ifstream file(filename);
    if (!file) {
        // should not happen
        printf("Failed to open task file!\n");
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string idStr, name, sTimeStr, prioStr, catStr, remind_timeStr, detail;
        
        if (getline(iss, idStr, ','))
        {
            // id
            int id = stoi(idStr);
            // name
            if (getline(iss >> ws, name, ','))
            {
                // start_time
                if (getline(iss >> ws, sTimeStr, ','))
                {
                    time_t start_time = convertToTime(sTimeStr);

                    // prio
                    if (getline(iss >> ws, prioStr, ','))
                    {
                        Priority prio = convertToPriority(prioStr);

                        // category
                        if (getline(iss >> ws, catStr, ','))
                        {
                            Category cat = convertToCategory(catStr);

                            // remind_time
                            if (getline(iss >> ws, remind_timeStr, ','))
                            {
                                time_t remind_time = convertToTime(remind_timeStr);

                                // detail
                                if (getline(iss >> ws, detail))
                                {
                                    // new_task
                                    Task task;
                                    task.id = id;
                                    strncpy(task.name, name.c_str(), sizeof(task.name) - 1);
                                    task.start_time = start_time;
                                    task.prio = prio;
                                    task.cat = cat;
                                    task.remind_time = remind_time;
                                    strncpy(task.detail, detail.c_str(), sizeof(task.detail) - 1);

                                    tasks.push_back(task);
                                }
                            }
                        }
                    }
                }
            }
        }

    }

    file.close();

    //release lock
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &fl);
    close(fd);
    return tasks;
}


void saveTask(const vector<Task>& tasks, const User* user){

    string user->username(user->username);
    string filename = USER_DIR + user->username + ".txt" ;

    //begin lock
    int fd = open((USER_DIR + user->username).c_str(), O_RDWR);
    if(fd == -1){
        FILE* fp = fopen((USER_DIR + user->username).c_str(), "w");
        fclose(fp);
        fd = open((USER_DIR + user->username).c_str(), O_RDWR);
    }
    
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();

    fcntl(fd, F_SETLKW, &fl);
    //end lock

    ofstream file(filename);
    if (!file) {
        printf("Failed to open task file for saving!\n");
        return;
    }

    for (const Task& task : tasks) {
        file << task.id << ","
             << task.name << ","
             << convertTimeToString(task.start_time) << ","
             << convertPriorityToString(task.prio) << ","
             << convertCategoryToString(task.cat) << ","
             << convertTimeToString(task.remind_time) << ","
             << task.detail << endl;
    }

    file.close();
    //release lock
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &fl);
    close(fd);


}

