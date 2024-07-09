#include "../inc/thread1.h"

using namespace std;

void *thread1(void * arg){
    string command;

    //clear buffer
    getline(cin, command); 

    display_help();

    bool stop = false;

    //start polling
    do{
        //get command
        getline(cin, command);
        
        //match command
        if (command == "addtask"){
            add_task(arg);
        }else if (command == "deltask"){
            delete_task(arg);
        }else if (command == "edittask"){
            edit_task(arg);
        }else if (command == "displaytask"){
            display_task(arg);
        }else if (command == "deregister"){
            deregister(arg);
            stop = true;
        }else if (command == "changepassword"){
            change_password(arg);
        }else if (command == "help"){
            display_help();
        }else if (command == "quit"){
            stop = true;
        }else{
            cout << "Invalid command!" << endl;
            display_help();
        }
        cout << "-----------------------------------------------" << endl;
    }while (!stop);
    
    
    //exit thread
    pthread_exit(NULL);

    return NULL;
}


//打印帮助信息
void display_help(){
cout << "Runnning..." << endl;
cout << "-----------------------------------------------" << endl;
cout << "command list:" << endl;
cout << "addtask            Add a task." << endl;
cout << "deltask            Delete task with specified id." << endl;
cout << "edittask           Edit task with specified id." << endl;
cout << "displaytask        Display tasks in specified order." << endl;
cout << "deregister         Deregister current user." << endl;
cout << "changepassword     Change the password of current user." << endl;
cout << "help               Display help information." << endl;
cout << "quit               Log out current user." << endl;
}


//读取任务列表
void load_task(vector<Task> &tasklist, void *arg)
{
    pthread_mutex_lock(((ThreadInfo *)arg)->mutex);
    tasklist = loadTaskFromFile(((ThreadInfo *)arg)->user);
    pthread_mutex_unlock(((ThreadInfo *)arg)->mutex);
}


//保存任务列表
void save_task(vector<Task> &tasklist, void *arg)
{
    pthread_mutex_lock(((ThreadInfo *)arg)->mutex);
    saveTask2File(tasklist, ((ThreadInfo *)arg)->user);
    pthread_mutex_unlock(((ThreadInfo *)arg)->mutex);
}


//添加任务
void add_task(void *arg)
{
    //load task list
    vector<Task> tasklist;
    load_task(tasklist, arg);

    Task newtask;

    //check name
    bool valid = false;
    while (!valid)
    {
        //input task name
        cout << "Please input the task name " << QUIT << ": ";
        getline(cin, newtask.name);

        //check if user wants to quit
        if (newtask.name == "ESC")
        {
            return;
        }

        //check if name is empty
        if (newtask.name == "")
        {
            cout << "Task name cannot be empty!" << endl;
            continue;
        }

        //check if name already exists
        bool exist = false;
        for (int i = 0; i < tasklist.size(); i++)
        {
            if (tasklist[i].name == newtask.name)
            {
                cout << "Task name already exists!" << endl;
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            valid = true;
        }
    }

    //ask user to input priority
    cout << "Please input the task priority (1.Low[Default] 2.Moderate 3.High) " << QUIT << ": ";
    string prio;
    getline(cin, prio);
    if (prio == "ESC")
    {
        return;
    }
    if (prio == "2")
    {
        newtask.prio = MODERATE;
    }
    else if (prio == "3")
    {
        newtask.prio = HIGH;
    }
    else
    {
        newtask.prio = LOW;
    }

    //ask user to input category
    cout << "Please input the task category (1.Study 2.Life 3.Entertainment 4.NONE[Default]) " << QUIT << ": ";
    string cat;
    getline(cin, cat);
    if (cat == "ESC")
    {
        return;
    }
    if (cat == "1")
    {
        newtask.cat = STUDY;
    }
    else if (cat == "2")
    {
        newtask.cat = LIFE;
    }
    else if (cat == "3")
    {
        newtask.cat = ENTERTAINMENT;
    }
    else
    {
        newtask.cat = NONE;
    }

    //ask user to input start time
    string stime;
    valid = false; 
    while (!valid)
    {   
        cout << "Please input the task start time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
        getline(cin, stime);
        if (stime == "ESC")
        {
            return;
        }

        //check if date format is valid
        if (!checkDateFormat(stime))
        {
            cout << "Invalid date format!" << endl;
            cout << "Please input the task start time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        //check if date is in the past
        if (convertStringToTime(stime) < time(NULL))
        {
            cout << "Start time cannot be earlier than current time!" << endl;
            cout << "Please input the task start time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        //check if date is exist
        bool exist = false;
        for (int i = 0; i < tasklist.size(); i++)
        {
            if (tasklist[i].start_time == convertStringToTime(stime))
            {
                cout << "Task start time already exists!" << endl;
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            newtask.start_time = convertStringToTime(stime);
            valid = true;
        } 
    }

    //ask user to input remind time
    string rtime;
    valid = false;
    while (!valid)
    {
        cout << "Please input the task remind time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
        getline(cin, rtime);
        if (rtime == "ESC")
        {
            return;
        }

        //check if date format is valid
        if (!checkDateFormat(rtime))
        {
            cout << "Invalid date format!" << endl;
            cout << "Please input the task remind time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        //check if date is in the past
        if (convertStringToTime(rtime) > newtask.start_time)
        {
            cout << "Remind time cannot be later than start time!" << endl;
            cout << "Please input the task remind time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        newtask.remind_time = convertStringToTime(rtime);
        valid = true;
    }

    //ask user to input detail
    cout << "Please input the task detail " << QUIT << ": ";
    string detail;
    getline(cin, detail);
    if (detail == "ESC")
    {
        return;
    }
    if (detail == "")
    {
        newtask.detail = "No detail.";
    }
    else
    {
        newtask.detail = detail;
    }

    //add task
    tasklist.push_back(newtask);

    //save task list
    save_task(tasklist, arg);
    cout << "Task added successfully!" << endl;
}


//删除任务
void delete_task(void *arg)
{
    //load task list
    vector<Task> tasklist;
    load_task(tasklist, arg);

    //check if task list is empty
    if (tasklist.size() == 0)
    {
        cout << "No task to delete!" << endl;
        return;
    }

    //display task list
    displayTaskById(tasklist);

    //ask user to input task id
    cout << "Please input the task id you want to delete " << QUIT << ": ";
    string id;
    getline(cin, id);
    if (id == "ESC")
    {
        return;
    }

    //check if id is valid
    if (!checkIdFormat(id))
    {
        cout << "Invalid id format!" << endl;
        return;
    }

    //check if id exists
    bool exist = false;
    for (int i = 0; i < tasklist.size(); i++)
    {
        if (tasklist[i].id == stoi(id))
        {
            tasklist.erase(tasklist.begin() + i);
            exist = true;
            break;
        }
    }
    if (!exist)
    {
        cout << "Task id does not exist!" << endl;
        return;
    }

    //save task list
    save_task(tasklist, arg);
    cout << "Task deleted successfully!" << endl;
}


//修改任务  
void edit_task(void *arg)
{
    //load task list
    vector<Task> tasklist;
    load_task(tasklist, arg);

    //check if task list is empty
    if (tasklist.size() == 0)
    {
        cout << "No task to edit!" << endl;
        return;
    }

    //display task list
    displayTaskById(tasklist);

    //ask user to input task id
    cout << "Please input the task id you want to edit " << QUIT << ": ";
    string id;
    getline(cin, id);
    if (id == "ESC")
    {
        return;
    }

    //check if id is valid
    if (!checkIdFormat(id))
    {
        cout << "Invalid id format!" << endl;
        return;
    }

    //check if id exists
    bool exist = false;
    Task task;
    for (int i = 0; i < tasklist.size(); i++)
    {
        if (tasklist[i].id == stoi(id))
        {
            exist = true;
            task = tasklist[i];
            tasklist.erase(tasklist.begin() + i);
            break;  
        }
    }
    if (!exist)
    {
        cout << "Task id does not exist!" << endl;
        return;
    }
    displaySingleTask(task);

    //ask user to input new task name
    string name;

    bool valid = false;
    while (!valid)
    {
        cout << "Please input the new task name (press ENTER to skip) " << QUIT << ": ";
        getline(cin, name);
        if (name == "ESC")
        {
            return;
        }
        if (name == "" || name == task.name)
        {
            break;
        }

        //check if name already exists
        bool exist = false;
        for (int i = 0; i < tasklist.size(); i++)
        {
            if (tasklist[i].name == name)
            {
                cout << "Task name already exists!" << endl;
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            task.name = name;
            valid = true;
        }
    }

    //ask user to input new task priority
    cout << "Please input the new task priority (press ENTER to skip) (1.Low 2.Moderate 3.High) " << QUIT << ": ";
    string prio;
    getline(cin, prio);
    if (prio == "ESC")
    {
        return;
    }

    if (prio == "1")
    {
        task.prio = LOW;
    }
    else if (prio == "2")
    {
        task.prio = MODERATE;
    }
    else if (prio == "3")
    {
        task.prio = HIGH;
    }

    //ask user to input new task category
    cout << "Please input the new task category (press ENTER to skip) (1.Study 2.Life 3.Entertainment 4.NONE) " << QUIT << ": ";
    string cat;
    getline(cin, cat);
    if (cat == "ESC")
    {
        return;
    }

    if (cat == "1")
    {
        task.cat = STUDY;
    }
    else if (cat == "2")
    {
        task.cat = LIFE;
    }
    else if (cat == "3")
    {
        task.cat = ENTERTAINMENT;
    }
    else if (cat == "4")
    {
        task.cat = NONE;
    }

    //ask user to input new task start time
    string stime;
    valid = false;
    while (!valid)
    {
        cout << "Please input the new task start time (press ENTER to skip) (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
        getline(cin, stime);
        if (stime == "ESC")
        {
            return;
        }

        if (stime == "" || stime == convertTimeToString(task.start_time))
        {
            break;
        }

        //check if date format is valid
        if (!checkDateFormat(stime))
        {
            cout << "Invalid date format!" << endl;
            cout << "Please input the new task start time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        //check if date is in the past
        if (convertStringToTime(stime) < time(NULL))
        {
            cout << "Start time cannot be earlier than current time!" << endl;
            cout << "Please input the new task start time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        //check if date is exist
        bool exist = false;
        for (int i = 0; i < tasklist.size(); i++)
        {
            if (tasklist[i].start_time == convertStringToTime(stime))
            {
                cout << "Task start time already exists!" << endl;
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            task.start_time = convertStringToTime(stime);
            valid = true;
        }
    }

    //ask user to input new task remind time
    string rtime;
    valid = false;
    while (!valid)
    {
        cout << "Please input the new task remind time (press ENTER to skip) (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
        getline(cin, rtime);
        if (rtime == "ESC")
        {
            return;
        }

        if (rtime == "" || rtime == convertTimeToString(task.remind_time))
        {
            break;
        }

        //check if date format is valid
        if (!checkDateFormat(rtime))
        {
            cout << "Invalid date format!" << endl;
            cout << "Please input the new task remind time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        //check if date is in the past
        if (convertStringToTime(rtime) > task.start_time)
        {
            cout << "Remind time cannot be later than start time!" << endl;
            cout << "Please input the new task remind time (Format: yyyy-mm-dd/hh:mm:ss) " << QUIT << ": ";
            continue;
        }

        task.remind_time = convertStringToTime(rtime);
        valid = true;
    }

    //ask user to input new task detail
    cout << "Please input the new task detail (press ENTER to skip) " << QUIT << ": ";
    string detail;
    getline(cin, detail);
    if (detail == "ESC")
    {
        return;
    }
    if (detail != "" && detail != task.detail)
    {
        task.detail = detail;
    }

    //add task
    tasklist.push_back(task);

    //save task list
    save_task(tasklist, arg);
    cout << "Task edited successfully!" << endl;
}


//打印任务列表
void display_task(void *arg)
{
    //load task list
    vector<Task> tasklist;
    load_task(tasklist, arg);

    //check if task list is empty
    if (tasklist.size() == 0)
    {
        cout << "No task to display!" << endl;
        return;
    }

    //ask user to input order
    cout << "Please input the order you want to display tasks: " << QUIT << endl;
    cout << "1. By ID" << endl;
    cout << "2. By priority" << endl;
    cout << "3. By category" << endl;
    cout << "4. By start time" << endl;
    cout << "5. By remind time" << endl;
    cout << "Your order: ";
    string order;
    getline(cin, order);
    cout << endl;

    if (order == "ESC")
    {
        return;
    }

    if (order == "1")
    {
        displayTaskById(tasklist);
    }
    else if (order == "2")
    {
        displayTaskByPriority(tasklist);
    }
    else if (order == "3")
    {
        displayTaskByCategory(tasklist);
    }
    else if (order == "4")
    {
        displayTaskByStartTime(tasklist);
    }
    else if (order == "5")
    {
        displayTaskByRemindTime(tasklist);
    }
    else
    {
        cout << "Invalid order!" << endl;
    }
}


//注销当前用户
void deregister(void *arg)
{
    string cur_username = ((ThreadInfo *)arg)->user->username;
    string cur_password = ((ThreadInfo *)arg)->user->password;
    string input_password;

    //ask user to input password
    cout << "Please input your password to deregister " << QUIT << ": ";
    getline(cin, input_password);
    if (input_password == "ESC")
    {
        return;
    }

    //check if password is correct
    if (input_password != cur_password)
    {
        cout << "Password is incorrect!" << endl;
        return;
    }

    //delete account
    Account account(account_filename);
    if (account.deleteAccount(cur_username, cur_password))
    {
        cout << "Deregister successfully!" << endl;
        cout << "Quitting..." << endl;
    }
    else
    {
        cout << "Deregister failed!" << endl;
    }

}


//修改密码
void change_password(void *arg)
{
    string cur_username = ((ThreadInfo *)arg)->user->username;
    string cur_password = ((ThreadInfo *)arg)->user->password;
    string input_password;

    //ask user to input password
    cout << "Please input your password " << QUIT << ": ";
    getline(cin, input_password);
    if (input_password == "ESC")
    {
        return;
    }

    //check if password is correct
    if (input_password != cur_password)
    {
        cout << "Password is incorrect!" << endl;
        return;
    }

    //ask user to input new password
    string new_password;
    cout << "Please input your new password " << QUIT << ": ";
    getline(cin, new_password);
    if (new_password == "ESC")
    {
        return;
    }

    //change password
    Account account(account_filename);
    if (account.changePassword(cur_username, cur_password, new_password))
    {
        cout << "Password changed successfully!" << endl;
    }
    else
    {
        cout << "Password changed failed!" << endl;
    }
}
