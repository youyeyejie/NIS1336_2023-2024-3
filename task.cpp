#include "task.h"

using namespace std;

//string转换优先级
Priority convertStringToPriority(const string& priorityStr) {
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
Category convertStringToCategory(const string& categoryStr) {
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
        return NONE;//默认
    }
}

//string转换时间
time_t convertStringToTime(const string& timeStr) {
    // timeStr:YYYY-MM-DD/HH:MM:SS
    tm time = {};
    istringstream iss(timeStr);
    iss >> get_time(&time, "%Y-%m-%d/%H:%M:%S");
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
    ss << put_time(timeinfo, "%Y-%m-%d/%H:%M:%S");
    return ss.str();
}

//默认提醒时间为一天前
string getDefaultRemindTime(time_t time) {
    time_t nextWeek = time - 24 * 60 * 60;
    return convertTimeToString(nextWeek);
}

//获取下一个ID
int getNextId(vector<Task> tasks) {
    if (tasks.empty()) 
    {
        return 0;
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

//检查日期格式
bool checkDateFormat(const string& str) {
    // define regular expression
    regex re(R"(^\d{4}-\d{2}-\d{2}/\d{2}:\d{2}:\d{2}$)");
    // judge
    if(!regex_match(str, re))return false;
    
    tm time = {};
    istringstream iss(str);
    iss >> get_time(&time, "%Y-%m-%d/%H:%M:%S");
    time_t tm=mktime(&time);
    if( tm==-1 || convertTimeToString(tm)!=str ) return false;
    return true;
}

//打印单个任务
void displaySingleTask(const Task& task) {
    cout << setw(2) << task.id << "\t";
    cout << setw(12) << task.name << "\t";
    cout << setw(24) << convertTimeToString(task.start_time) << "\t";
    cout << setw(12) << convertPriorityToString(task.prio) << "\t";
    cout << setw(16) << convertCategoryToString(task.cat) << "\t";
    cout << setw(24) << convertTimeToString(task.remind_time) << "\t";
    cout << task.detail << endl;
}

//打印表头
void displayTaskTitle(){
    cout << setw(2) << "ID" << "\t";
    cout << setw(12) << "Name" << "\t";
    cout << setw(24) << "Start Time" << "\t";
    cout << setw(12) << "Priority" << "\t";
    cout << setw(16) << "Category" << "\t";
    cout << setw(24) << "Remind Time" << "\t";
    cout << "Detail" << endl;
}
//按开始时间打印任务
void displayTaskByStartTime(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.start_time < t2.start_time;
    });

    displayTaskTitle();
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
        displaySingleTask(task);
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按优先级打印任务
void displayTaskByPriority(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.prio < t2.prio;
    });

    displayTaskTitle();
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
         displaySingleTask(task);
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按类别打印任务
void displayTaskByCategory(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.cat < t2.cat;
    });

    displayTaskTitle();
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
         displaySingleTask(task);
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按ID打印任务
void displayTaskById(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.id < t2.id;
    });

    displayTaskTitle();
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
         displaySingleTask(task);
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//按提醒时间打印任务
void displayTaskByRemindTime(const vector<Task>& tasks) {
    vector<Task> clonetasks(tasks);

    sort(clonetasks.begin(), clonetasks.end(), [](const Task& t1, const Task& t2) {
        return t1.remind_time < t2.remind_time;
    });

    displayTaskTitle();
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& task : clonetasks) {
         displaySingleTask(task);
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//加载任务
vector<Task> loadTaskFromFile(const User* user) {
    vector<Task> tasks;
    string filename = op + user->username + ed ;

    //begin lock
    int fd = open(filename.c_str(), O_RDWR);
    if(fd == -1){
        FILE* fp = fopen(filename.c_str(), "w");
        fclose(fp);
        fd = open(filename.c_str(), O_RDWR);
    }
    
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();

    fcntl(fd, F_SETLKW, &fl);
    //end lock

    //open file
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open task file for loading!" << endl;
        return tasks;
    }
    
    //read file
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string idStr, name, start_TimeStr, prioStr, catStr, remind_timeStr, detail;
        
        if (getline(iss, idStr, ',') && getline(iss, name, ',') && getline(iss, start_TimeStr, ',') && getline(iss, prioStr, ',') && getline(iss, catStr, ',') && getline(iss, remind_timeStr, ',') && getline(iss, detail)) {
            Task task;
            task.id = stoi(idStr);
            task.name = name;
            task.start_time = convertStringToTime(start_TimeStr);
            task.prio = convertStringToPriority(prioStr);
            task.cat = convertStringToCategory(catStr);
            task.remind_time = convertStringToTime(remind_timeStr);
            task.detail = detail;
            tasks.push_back(task);
        }
    }
    
    //close file
    file.close();

    //release lock
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &fl);
    close(fd);
    return tasks;
}

//保存任务
void saveTask2File(const vector<Task>& tasks, const User* user){
    string filename = op + user->username + ed ;

    //begin lock
    int fd = open(filename.c_str(), O_RDWR);
    if(fd == -1){
        FILE* fp = fopen(filename.c_str(), "w");
        fclose(fp);
        fd = open(filename.c_str(), O_RDWR);
    }
    
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();

    fcntl(fd, F_SETLKW, &fl);
    //end lock

    //open file
    ofstream file(filename);
    if (!file) {
        cout << "Failed to open task file for saving!" << endl;
        return;
    }

    //write file
    for (const Task& task : tasks) {
        file << task.id << ","
             << task.name << ","
             << convertTimeToString(task.start_time) << ","
             << convertPriorityToString(task.prio) << ","
             << convertCategoryToString(task.cat) << ","
             << convertTimeToString(task.remind_time) << ","
             << task.detail << endl;
    }

    //close file
    file.close();
  
    //release lock
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &fl);
    close(fd);
}

