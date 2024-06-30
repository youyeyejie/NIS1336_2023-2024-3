#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
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
    ./cli changeelement -u username -p password -i id -n name -o prio -c cat -r rem -d detail -s start
    ./cli register -u username -p password
    ./cli deregister -u username -p password
    ./cli changepassword -u username -p password -n newpassword
    ./cli check -u username -p password
    ./cli login -u username -p password
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
        deleteTask(argc, argv);
    }
    else if(strcmp(argv[1], "register") == 0){
        userRegister(argc, argv);
    }
    else if(strcmp(argv[1], "deregister") == 0){
        userDeregister(argc, argv);
    }
    else if(strcmp(argv[1], "passwd") == 0){
        changePassword(argc, argv);
    }
    else if(strcmp(argv[1], "changeelement") == 0){
        changeElement(argc, argv);
    }
    // else if(strcmp(argv[1], "login") == 0){
    //     userLogin(argc, argv);
    // }
    // else if(strcmp(argv[1], "check") == 0){
    //     checkTask(argc, argv);
    // }
    else{
        cout<<"Unknown command! Use help to show usage!";
    }
    return 0;
}

void displayHelp(){
    cout << "Usage: ./cli [command] [options]" << endl;
    cout << "Commands:" << endl;
    cout << "displaytask -u username -p password -k kindOfDisplay(id/starttime/remindtime/priority/category)" << endl;
    cout << "addtask -u username -p password -n name -p prio -c cat -s start_time -r remind_time -d detail" << endl;
    cout << "deltask -u username -p password -i id" << endl;
    cout << "changeelement -u username -p password -i id -n name -o prio -c cat -r rem -d detail -s start" << endl;
    cout << "register -u username -p password" << endl;
    cout << "deregsiter -u username -p password" << endl;
    cout << "changepassword -u username -p password -n newpassword" << endl;
    // cout << "check -u username -p password" << endl;    
    // cout << "login -u username -p password" << endl;
}

//按照指定方式显示任务
void displayTask(int argc, char * argv[]){
    /*
    ./cli displaytask -u username -p password -k kindOfDisplay(id/starttime/remindtime/priority/category)
    */
    string username, password, kindOfDisplay;
    Account account("Account.txt");

    //getopt
    char optret;
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

//添加任务
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


    //getopt
    char optret;
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
        cout<<"Incorrect user name or password. Please check your input.";
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
        cout << "This task name is unavailable!" << endl;
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
        bool flag = false;
   		for(int i=0; i<tasklist.size(); ++i){
        	if(tasklist[i].start_time == convertStringToTime(start_time)){
            	flag = true;
            	break;
        	}
    	}
    	if(flag){
        	cout << "This start time is already occupied!" << endl;
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

//删除任务
void deleteTask(int argc, char * argv[]){
    /* 
    ./cli deltask -u username -p password -i id
    */

    Account account("Account.txt");
    string username, password;
    int id = -1;

    //getopt
    char optret;
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

    //check login info
    if(username.empty() || password.empty()){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }

    //login
    User user = account.login(username, password);
    if(user.uid == -1){
        cout << "Incorrect user name or password. Please check your input." << endl;
        exit(-1);
    }

    //load tasks
    vector<Task> tasklist=loadTaskFromFile(&user);

    //check id and get index
    bool flag = false;
    int indexOfTask = -1;
    for(int i = 0; i < tasklist.size(); ++i){
        if(tasklist[i].id == id){
            flag = true;
            indexOfTask = i;
            break;
        }
    }

    //delete
    if(flag){
        tasklist.erase(tasklist.begin() + indexOfTask);
        saveTask2File(tasklist, &user);
        cout << "Delete successfully!" << endl;
    }else{
        cout << "Cannot find this task." << endl;
    }
}

//修改任务的某几个信息
void changeElement(int argc, char * argv[]){
    /*
    ./cli changeelement -u username -p password -i id -n name -o prio -c cat -r remind_time -d detail -s start_time
    */

    Account account("Account.txt");
    string username, password;
    int id = -1;
    string name, detail, prio, cat, start_time, remind_time;
    
    //getopt
    char optret;
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
            prio = optarg;
            break;

        case 'c':
            cat = optarg;
            break;

        case 'r':
            remind_time = optarg;
            break;

        case 'd':
            detail = optarg;
            break;

        case 's':
            start_time = optarg;
            break;
        
        default:
            break;
        }
    }

    //check login info
    if(username.empty() || password.empty() || id == 0){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }
    User user = account.login(username, password);
    if(user.uid == -1){
        cout << "Incorrect user name or password. Please check your input." << endl;
        exit(-1);
    }

    //load tasks
    vector<Task> tasklist=loadTaskFromFile(&user);

    //check id and get index
    bool flag = false;
    int indexOfTask = -1;
    for(int i = 0; i < tasklist.size(); ++i){
        if(tasklist[i].id == id){
            flag = true;
            indexOfTask = i;
            break;
        }
    }
    if(!flag){
        cout << "Cannot found this task " << id << endl;
        exit(-1);
    }

    //check name
    bool name_existed = false;
    if(!name.empty()){
        for(int i = 0; i < tasklist.size(); ++i){
        	if(tasklist[i].name == name){
        	    name_existed = true;
        	    break;
        	}
   		} 
    }
    if(name_existed){
        cout << "Task name already exists!" << endl;
        exit(-1);
    }
    tasklist[indexOfTask].name = name;
    
    //replace priority
    if (!prio.empty()){
        tasklist[indexOfTask].prio = convertStringToPriority(prio);
    }

    //replace category
    if (!cat.empty()){
        tasklist[indexOfTask].cat = convertStringToCategory(cat);
    }

    //replace detail
    if (!detail.empty()){
        tasklist[indexOfTask].detail = detail;
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
        bool flag = false;
   		for(int i=0; i<tasklist.size(); ++i){
            if (i == indexOfTask) continue;
        	if (tasklist[i].start_time == convertStringToTime(start_time)){
            	flag = true;
            	break;
        	}
    	}
    	if(flag){
        	cout << "This start time is already occupied!" << endl;
        	exit(-1);
    	} 
        tasklist[indexOfTask].start_time = convertStringToTime(start_time);
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
        tasklist[indexOfTask].remind_time = convertStringToTime(remind_time);
    }

    //save
    saveTask2File(tasklist, &user);
    cout << "Task " << id << " is successfully modified" << endl;
}

//注册用户
void userRegister(int argc, char* argv[]){
    /*
    ./cli register -u username -p password
    */
    Account account("Account.txt");

    string username, password;

    //getopt
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

    //check login info
    if(username.empty()|| password.empty()){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }

    bool flag = account.newAccount(username, password);
    if(flag){
        cout << "Register successfully!" << endl;
    }else{
        cout << "Register failed!" << endl;
        exit(-1);
    }
}

//删除用户
void userDeregister(int argc, char* argv[]){
    /*
    ./cli deregister -u username -p password
    */
    Account account("Account.txt");

    string username, password;

    //getopt
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

    //check login info
    if(username.empty()|| password.empty()){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }

    bool flag = account.deleteAccount(username, password);
    if(flag){
        cout << "Delete account successfully!" << endl;
    }else{
        cout << "Delete account failed!" << endl;
        exit(-1);
    }
}

//修改密码
void changePassword(int argc, char* argv[]){
    Account account("Account.txt");
    string username, password, new_password;


    //getopt
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

    if(username.empty()|| password.empty()|| new_password.empty()){
        cout << "Too few arguments!" << endl;
        exit(-1);
    }

    bool flag = account.changePassword(username, password, new_password);

    if(flag){
        cout << "Changed password successfully!" << endl;
    }else{
        cout << "Change password failed!" << endl;
        exit(-1);
    }
}



//void userLogin(int argc, char* argv[]){
//    char* username = NULL;
//    char* password = NULL;
//    Account account("Account.txt");
//
//    char optret;
//    while((optret = getopt(argc,argv,"u:p:"))!=-1){
//        switch(optret){
//            case 'u':
//            username = optarg;
//            break;
//
//        case 'p':
//            password = optarg;
//            break;
//
//        default:
//            break;
//        }
//    }
//
//    if(username == NULL || password == NULL){
//        printf("Too few arguments!");
//        exit(-1);
//    }
//
//    User user = account.login(username, password);
//
//    if(user.id == 0){
//        printf("Incorrect user name or password. Please check your input.");
//        exit(-1);
//    }else{
//        printf("Successfully loged in as %s.", user.username);
//    }
//}

//void checkTask(int argc, char* argv[]){
//    char* username = NULL;
//    char* password = NULL;
//    Account account("Account.txt");
//
//    char optret;
//    while((optret = getopt(argc,argv,"u:p:"))!=-1){
//        switch(optret){
//            case 'u':
//            username = optarg;
//            break;
//
//        case 'p':
//            password = optarg;
//            break;
//
//        default:
//            break;
//        }
//    }
//
//    if(username == NULL || password == NULL){
//        printf("Too few arguments!");
//        exit(-1);
//    }
//
//    User user = account.login(username, password);
//
//    if(user.id == 0){
//        printf("Incorrect user name or password. Please check your input.");
//        exit(-1);
//    }
//
//    //check task begin
//    vector<Task> tasklist;
//    struct tm *current_time;
//    struct tm *task_time;
//    double difft = 0;
//
//    loadTask(tasklist, &user);
//
//    //get current time
//    time_t timep;
//    time(&timep);
//    current_time = localtime(&timep);
//
//    //check arriving tasks
//    for(int i = 0; i<tasklist.size(); ++i){
//            
//        task_time = localtime(&(tasklist[i].remind_time));
//            
//        if(task_time->tm_year != current_time->tm_year) continue;
//        if(task_time->tm_mon != current_time->tm_mon) continue;
//        if(task_time->tm_mday != current_time->tm_mday) continue;
//        // day match if here
//        // difft = difftime(tasklist[i].remind_time, timep);
//
//        if(timep > tasklist[i].remind_time && timep < tasklist[i].s_time){
//            printf("Task %d %s is arriving: %s.", 
//            tasklist[i].id, tasklist[i].name, tasklist[i].detail);
//        }
//
//    }
//
//}

// void cmdError(){
//     cout<<"Unknown command! Use help to show usage!";
// }
