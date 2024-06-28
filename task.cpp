#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include "task.h"

using namespace std;

Priority convertToPriority(const string& priorityStr) {
    if (priorityStr == "HIGH") {
        return HIGH;
    } else if (priorityStr == "MODERATE") {
        return MODERATE;
    } else if (priorityStr == "LOW") {
        return LOW;
    } else {
        // default
        return LOW;
    }
}


Category convertToCategory(const string& categoryStr) {
    if (categoryStr == "STUDY") {
        return STUDY;
    } else if (categoryStr == "LIFE") {
        return LIFE;
    } else if (categoryStr == "ENTERTAINMENT") {
        return ENTERTAINMENT;
    } else {
        // default
        return STUDY;
    }
}


time_t convertToTime(const string& timeStr) {
    // timeStr:YYYY-MM-DD HH:MM:SS
    tm timeInfo = {};
    istringstream iss(timeStr);
    iss >> get_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
    return mktime(&timeInfo);
}


string convertPriorityToString(Priority priority) {
    switch (priority) {
        case HIGH:
            return "HIGH";
        case MODERATE:
            return "MODERATE";
        case LOW:
            return "LOW";
        default:
            return "LOW";
    }
}


string convertCategoryToString(Category category) {
    switch (category) {
        case STUDY:
            return "STUDY";
        case LIFE:
            return "LIFE";
        case ENTERTAINMENT:
            return "ENTERTAINMENT";
        default:
            return "NONE";
    }
}


string convertTimeToString(time_t time) {
    stringstream ss;
    struct tm* timeinfo;
    timeinfo = localtime(&time);

    ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}


void loadTask(vector<Task>& tasks, const User* user){

    tasks.clear(); 

    string user_name(user->username);
    string filename = USER_DIR + user_name + ".txt" ;

    //begin lock
    int fd = open((USER_DIR + user_name).c_str(), O_RDWR);
    if(fd == -1){
        FILE* fp = fopen((USER_DIR + user_name).c_str(), "w");
        fclose(fp);
        fd = open((USER_DIR + user_name).c_str(), O_RDWR);
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

}


void saveTask(const vector<Task>& tasks, const User* user){

    string user_name(user->username);
    string filename = USER_DIR + user_name + ".txt" ;

    //begin lock
    int fd = open((USER_DIR + user_name).c_str(), O_RDWR);
    if(fd == -1){
        FILE* fp = fopen((USER_DIR + user_name).c_str(), "w");
        fclose(fp);
        fd = open((USER_DIR + user_name).c_str(), O_RDWR);
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


void showTask(const vector<Task>& tasks) {
    vector<Task> newtasks(tasks);

    sort(newtasks.begin(), newtasks.end(), [](const Task& t1, const Task& t2) {
        return t1.start_time < t2.start_time;
    });

    printf("The info of all tasks (most recent start time comes first):\n");
    printf("%2s\t%-12s%-24s%-12s%-16s%-24s%s\n", "ID", "Task Name", "Start Time", "Priority", "Category", "remind_timeind Time", "Details");

    for (const auto& task : newtasks) {
        printf("%2d\t%-12s%-24s%-12s%-16s%-24s%s\n", task.id, task.name, convertTimeToString(task.start_time).c_str(),
               convertPriorityToString(task.prio).c_str(), convertCategoryToString(task.cat).c_str(),
               convertTimeToString(task.remind_time).c_str(), task.detail);
    }
}

int getminId(vector<Task> tasks) {
    int size = tasks.size();
    if(size <=0) return 1;
    for(int i=0;i<size;i++){
        while(tasks[i].id>0&&tasks[i].id<size&&(i!=tasks[i].id)){
            int t = tasks[i].id;
            if(tasks[t].id==tasks[i].id) break;
            int tmp = tasks[i].id;
            tasks[i].id=tasks[t].id;
            tasks[t].id = tmp;
        }
    }
    for(int i =1;i<size;i++){
        if(i!=tasks[i].id)return i;
    }

    return size+(tasks[0].id==(size));
}