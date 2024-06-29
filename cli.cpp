#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <regex>
#include <getopt.h>
#include <unistd.h>
#include "cli.h"

using namespace std;


int main(int argc, char * argv[]){
    /*
    support commands:
    ./cli displaytask -u username -p password -k kindOfDisplay
    ./cli addtask -u username -p password -n name -p prio -c cat -s start_time -r remind_time -d detail 
    ./cli deltask -u username -p password -i id
    ./cli login -u username -p password
    ./cli reg -u username -p password
    ./cli passwd -u username -p password -n newpassword
    ./cli check -u username -p password
    */

    if(argc < 2 || strcmp(argv[1], "help") == 0){
        displayHelp();
        exit(-1);
    }
    else if(strcmp(argv[1], "displaytask") == 0){
        displayTask(argc, argv);
    }
    else if(strcmp(argv[1], "addtask") == 0){
        addTask(argc, argv);
    }
    else if(strcmp(argv[1], "deltask") == 0){
        delTask(argc, argv);
    }
    else if(strcmp(argv[1], "login") == 0){
        userLogin(argc, argv);
    }
    else if(strcmp(argv[1], "reg") == 0){
        userRegister(argc, argv);
    }
    else if(strcmp(argv[1], "passwd") == 0){
        changePasswd(argc, argv);
    }
    else if(strcmp(argv[1], "check") == 0){
        checkTask(argc, argv);
    }
    else{
        cmdError();
    }
    return 0;
}


//display task
void displayTask(int argc, char * argv[]){
    /*
    ./cli displaytask -u username -p password -k kindOfDisplay(id/starttime/remindtime/priority/category)
    */
    string username, password, kindOfDisplay;
    Account account("Account.txt");
    int optret;

    //getopt
    while((optret = getopt(argc, argv, "u:p:k:")) != -1){
        switch(optret)
        {
        case 'u':
            username = optarg;
            break;
        case 'p':
            password = optarg;
            break;
        case 'k':
            kindOfDisplay = optarg;
            break;
        }
    }

    //check info
    if (username.empty() || password.empty() || kindOfDisplay.empty()){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }

    //login
    User user = account.login(username, password);
    if(user.uid == -1){
        cout << "Incorrect user name or password. Please check your input." << endl;
        exit(-1);
    }

    //load task
    vector<Task> tasklist = loadTaskFromFile(&user);
    if (kindOfDisplay == "id")
    {
        displayTaskById(tasklist);
    }
    else if (kindOfDisplay == "starttime")
    {
        displayTaskByStartTime(tasklist);
    }
    else if (kindOfDisplay == "remindtime")
    {
        displayTaskByRemindTime(tasklist);
    }
    else if (kindOfDisplay == "priority")
    {
        displayTaskByPriority(tasklist);
    }
    else if (kindOfDisplay == "category")
    {
        displayTaskByCategory(tasklist);
    }
    else
    {
        cout << "Unknown kind of display!" << endl;
        exit(-1);
    }
}

void addTask(int argc, char * argv[]){
    /*
    ./cli add -u username -p password -n name -o prio -c cat -s start_time -r remind_time -d detail 
    */

    Account account("Account.txt");
    string username, password;
    string name;
    string detail = "No detail";
    string prio = "LOW";
    string cat = "NONE";
    string start_time = convertTimeToString(time(NULL));
    string remind_time = getDefaultRemindTime(time(NULL));

    char optret;

    //getopt
    while((optret = getopt(argc, argv, "u:p:n:o:c:s:r:d:")) != -1){
        switch (optret)
        {
        case 'u':
            username = optarg;
            break;
        case 'p':
            password = optarg;
            break;
        case 'n':
            name = optarg;
            break;
        case 'o':
            prio = optarg;
            break;
        case 'c':
            cat = optarg;
            break;
        case 's':
            start_time = optarg;
            break;
        case 'r':
            remind_time = optarg;
            break;
        case 'd':
            detail = optarg;
            break;
        default:
            break;
        }
    }

    //check login info
    if (username.empty() || password.empty()){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }

    //login
    User user = account.login(username, password);
    if(user.uid == -1){
        printf("Incorrect user name or password. Please check your input.\n");
        exit(-1);
    }


    Task new_task;

    //get next id
    vector<Task> tasklist= loadTaskFromFile(&user);
    new_task.id = getNextId(tasklist);

    //check name
    if(name.empty()){
        cout << "Please input task name!" << endl;
        exit(-1);
    }

    bool flag = false;
    for(int i=0; i<tasklist.size(); ++i){
        if(tasklist[i].name == name){
            flag = true;
            break;
        }
    }
    if(flag){
        printf("This task name is unavailable!\n");
        exit(-1);
    }   
    new_task.name = name;

    //replace priority
    if (!prio.empty()){
        new_task.prio = convertStringToPriority(prio);
    }

    //replace category
    if (!cat.empty()){
        new_task.cat = convertStringToCategory(cat);
    }

    //replace detail
    if (!detail.empty()){
        new_task.detail = detail;
    }

    //replace start time
    if (!start_time.empty()) {
        if (!checkDateFormat(start_time)){
            cout << "Start time format error!" << endl;
            exit(-1);
        }
        if (convertStringToTime(start_time) < time(NULL)){
            cout << "Start time cannot be earlier than current time!" << endl;
            exit(-1);
        }
        new_task.start_time = convertStringToTime(start_time);
    }

    //replace remind time
    if (!remind_time.empty()) {
        if (!checkDateFormat(remind_time)){
            cout << "Remind time format error!" << endl;
            exit(-1);
        }
        if (convertStringToTime(remind_time) < convertStringToTime(start_time)){
            cout << "Remind time cannot be earlier than start time!" << endl;
            exit(-1);
        }
        new_task.remind_time = convertStringToTime(remind_time);
    }

    //add new task to tasklist
    tasklist.push_back(new_task);

    //save
    saveTask2File(tasklist, &user);
}


//todo




void altTask(int argc, char * argv[]){
    /*
    ./cli alt -u username -p password -i id -n name -o prio -c cat -r remind_time -d detail -s start_time
    */

    Account account("Account.txt");

    //login info
    string username, password;
    int id;
    string name, prio, cat, start_time, remind_time, detail;
    int optret;
    
    while((optret = getopt(argc, argv, "u:p:i:n:o:c:r:d:s:"))!=-1){
        switch (optret)
        {
        case 'u':
            username = optarg;
            break;

        case 'p':
            password = optarg;
            break;

        case 'i':
            id = atoi(optarg);
            break;

        case 'n':
            name = optarg;
            break;

        case 'o':
            c_prio = optarg;
            break;

        case 'c':
            c_cat = optarg;
            break;

        case 'r':
            c_rem = optarg;
            break;

        case 'd':
            detail = optarg;
            break;

        case 's':
            c_stime = optarg;
            break;
        
        default:
            break;
        }
    }

    //check login info
    if(username == NULL || password == NULL){
        printf("Too few arguments!\n");
        exit(-1);
    }

    User user = account.login(username, password);
    if(user.id == 0){
        printf("Incorrect user name or password. Please check your input.\n");
        exit(-1);
    }

    std::vector<Task> tasklist;
    loadTask(tasklist, &user);

    std::vector<Task>::iterator target_it;
    bool found = false;
    for(target_it = tasklist.begin(); target_it != tasklist.end(); ++target_it){
        if(target_it->id == id){
            found = true;
            break;
        }
    }

    if(!found){
        printf("Cannot found task %d.\n", id);
        exit(-1);
    }

    //check name
    if(name){
        bool name_existed = false;
        for(auto it = tasklist.begin(); it != tasklist.end(); ++it){
            if(!strcmp(it->name, name)){
                name_existed = true;
                break;
            }
        }

        if(name_existed){
            printf("Task name already exists!\n");
            exit(-1);
        }

        strcpy(target_it->name, name);
        
    }
    //check detail
    if(detail){
        strcpy(target_it->detail, detail);
    }
    //check prio
    if(c_prio){
        std::string s_prio = c_prio;
        target_it->prio = convertToPriority(s_prio);
    }
    //check category
    if(c_cat){
        std::string s_cat = c_cat;
        target_it->cat = convertToCategory(s_cat);
    }

    //check s_time and rem_time
    time_t stime;
    time_t rtime;
    if(c_stime){
        std::string s_time_str = c_stime;
        if(!checkDateFormat(s_time_str)){
            printf("Time format error!\n");
            exit(-1);
        }
        tm s_time_tm = {};
        std::istringstream ss(s_time_str);
        ss >> std::get_time(&s_time_tm, "%Y-%m-%d,%T");
        stime = mktime(&s_time_tm);
    }else{
        stime = target_it->s_time;
    }

    if(c_rem){
        std::string r_time_str = c_rem;
        if(!checkDateFormat(r_time_str)){
            printf("Time format error!\n");
            exit(-1);
        }
        tm r_time_tm = {};
        std::istringstream sr(r_time_str);
        sr >> std::get_time(&r_time_tm, "%Y-%m-%d,%T");
        rtime = mktime(&r_time_tm);
    }else{
        rtime = target_it->remind_time;
    }

    //validation
    time_t cur;
    time(&cur);

    if(cur > stime){
        printf("Cannot use past time!\n");
        exit(-1);
    }

    if(stime < rtime){
        printf("Start time cannot be earlier than remind time.\n");
        exit(-1);
    }

    for(auto it = tasklist.begin(); it != tasklist.end();++it){
        if( it->id == id ) continue;
        if(it->s_time == stime){
            printf("This start_time time is occupied!\n");
            exit(-1);
        }
    }

    target_it->remind_time = rtime;
    target_it->s_time = stime;

    saveTask(tasklist, &user);
    printf("Task %d is successfully modified\n", id );


}

void delTask(int argc, char * argv[]){
    char* username = NULL;
    char* password = NULL;
    int id;
    char optret;

    Account account("Account.txt");

    while((optret = getopt(argc, argv, "u:p:i:")) != -1){
        switch(optret){
        case 'u':
            username = optarg;
            break;

        case 'p':
            password = optarg;
            break;

        case 'i':
            id = atoi(optarg);
            break;

        default:
            break;
        }
    }

    //check user auth
    if(username == NULL || password == NULL){
        printf("Too few arguments!\n");
        exit(-1);
    }

    User user = account.login(username, password);

    if(user.id == 0){
        printf("Incorrect user name or password. Please check your input.\n");
        exit(-1);
    }

    std::vector<Task> tasklist;
    loadTask(tasklist, &user);
    bool flag = false;

    for(auto it = tasklist.begin(); it != tasklist.end(); ++it){
        if((*it).id == id){
            tasklist.erase(it);
            flag = true;
            break;  //if deleted, exit loop
        }
    }

    if(flag){
        saveTask(tasklist, &user);
        printf("Delete successfully!\n");
    }else{
        printf("Cannot find this task.\n");
    }
    
}

void userLogin(int argc, char* argv[]){
    char* username = NULL;
    char* password = NULL;
    Account account("Account.txt");

    char optret;
    while((optret = getopt(argc,argv,"u:p:"))!=-1){
        switch(optret){
            case 'u':
            username = optarg;
            break;

        case 'p':
            password = optarg;
            break;

        default:
            break;
        }
    }

    if(username == NULL || password == NULL){
        printf("Too few arguments!\n");
        exit(-1);
    }

    User user = account.login(username, password);

    if(user.id == 0){
        printf("Incorrect user name or password. Please check your input.\n");
        exit(-1);
    }else{
        printf("Successfully loged in as %s.\n", user.username);
    }
}

void userRegister(int argc, char* argv[]){
    char* username = NULL;
    char* password = NULL;
    Account account("Account.txt");

    char optret;
    while((optret = getopt(argc,argv,"u:p:"))!=-1){
        switch(optret){
            case 'u':
            username = optarg;
            break;

        case 'p':
            password = optarg;
            break;

        default:
            break;
        }
    }

    if(username == NULL || password == NULL){
        printf("Too few arguments!\n");
        exit(-1);
    }

    bool flag = account.registerUser(username, password);
    if(flag){
        printf("Registration succeeded!\n");
    }else{
        printf("Registration failed!\n");
        exit(-1);
    }
}

void changePasswd(int argc, char* argv[]){
    char* username = NULL;
    char* password = NULL;
    char* new_password = NULL;
    Account account("Account.txt");

    char optret;
    while((optret = getopt(argc,argv,"u:p:n:"))!=-1){
        switch(optret){
            case 'u':
            username = optarg;
            break;

        case 'p':
            password = optarg;
            break;

        case 'n':
            new_password = optarg;
            break;

        default:
            break;
        }
    }

    if(username == NULL || password == NULL || new_password == NULL){
        printf("Too few arguments!\n");
        exit(-1);
    }

    bool flag = account.changePassword(username, password, new_password);

    if(flag){
        printf("Changed password successfully!\n");
    }else{
        printf("Change password failed!\n");
        exit(-1);
    }
}

void checkTask(int argc, char* argv[]){
    char* username = NULL;
    char* password = NULL;
    Account account("Account.txt");

    char optret;
    while((optret = getopt(argc,argv,"u:p:"))!=-1){
        switch(optret){
            case 'u':
            username = optarg;
            break;

        case 'p':
            password = optarg;
            break;

        default:
            break;
        }
    }

    if(username == NULL || password == NULL){
        printf("Too few arguments!\n");
        exit(-1);
    }

    User user = account.login(username, password);

    if(user.id == 0){
        printf("Incorrect user name or password. Please check your input.\n");
        exit(-1);
    }

    //check task begin
    std::vector<Task> tasklist;
    struct tm *current_time;
    struct tm *task_time;
    double difft = 0;

    loadTask(tasklist, &user);

    //get current time
    time_t timep;
    time(&timep);
    current_time = localtime(&timep);

    //check arriving tasks
    for(int i = 0; i<tasklist.size(); ++i){
            
        task_time = localtime(&(tasklist[i].remind_time));
            
        if(task_time->tm_year != current_time->tm_year) continue;
        if(task_time->tm_mon != current_time->tm_mon) continue;
        if(task_time->tm_mday != current_time->tm_mday) continue;
        // day match if here
        // difft = difftime(tasklist[i].remind_time, timep);

        if(timep > tasklist[i].remind_time && timep < tasklist[i].s_time){
            printf("Task %d %s is arriving: %s.\n", 
            tasklist[i].id, tasklist[i].name, tasklist[i].detail);
        }

    }

}

void cmdError(){
    printf("Unknown command! Use help to show usage!\n");
}

void displayHelp(){
    cout << "Usage: ./cli [command] [options]\n";
    cout << "Commands:\n";
    cout << "displaytask -u username -p password -k kindOfDisplay(id/starttime/remindtime/priority/category)\n";
    cout << "addtask -u username -p password -n name -p prio -c cat -s start_time -r remind_time -d detail\n";
    cout << "deltask -u username -p password -i id\n";
    cout << "login -u username -p password\n";
    cout << "reg -u username -p password\n";
    cout << "passwd -u username -p password -n newpassword\n";
    cout << "check -u username -p password\n";

}


bool checkDateFormat(const std::string& str) {
    // 定义正则表达式
    std::regex re(R"(^\d{4}-\d{2}-\d{2},\d{2}:\d{2}:\d{2}$)");

    // 判断是否匹配正则表达式
    return std::regex_match(str, re);
}