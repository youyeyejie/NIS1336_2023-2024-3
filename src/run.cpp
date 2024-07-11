#include "../inc/run.h"

using namespace std;


void run(){
    //init
    Account account(account_filename);
    string username, password;
    User current_user;
    ThreadInfo thread_arg;
    int opt;

    //register or login
    cout<< "Welcome to Task Manager!\n";
    cout<< "Please select the operation: 1.Register 2.Login 3.Quit\n";
    scanf("%d", &opt);
    cin.get();
    bool valid;
    
    switch (opt)
    {
    case 1://register
    	valid=false;
    	while(!valid){
    		cout<< "User register:\n";
        	cout<< "Input your username:";
        	getline(cin, username);
        	cout<< "Input your password:";
        	getline(cin, password);
        	if(account.newAccount(username, password)){
        	    cout<< "Register successfully!\n";
        	    valid=true;
        	}
    	}
        current_user = account.login(username, password);
        cout<< "Login successfully! Welcome " << current_user.username << "!" << endl;
        break;

    case 2://login
    	valid=false;
    	while(!valid){
    		cout<< "User login:\n";
        	cout<< "Input your username:";
        	getline(cin, username);
        	cout<< "Input your password:";
        	getline(cin, password);
        	current_user = account.login(username, password);
        	if(current_user.uid == 0){
        	    cout<< "Incorrect user name or password. Please check your input.\n";
        	}
        	else valid = true;
    	}
        
        cout<< "Login successfully! Welcome " << current_user.username << "!" << endl;
        break;

    case 3://quit
        exit(0);
        break;
    
    default:
        cout<< "Unknown command! Can only accept '1' or '2' or '3'.\n";
        exit(-1);
        break;
    }

    //create thread
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t *th_1, *th_2;
    thread_arg.mutex = &mutex;
    thread_arg.user = &current_user;
    thread_arg.running = true;

    //create thread1
    th_1 = new pthread_t;
    if(pthread_create(th_1, NULL, thread1, &thread_arg)){
        cout<< "Create thread 1 failed.\n";
        exit(-1);
    }

    //create thread2
    th_2 = new pthread_t;
    if(pthread_create(th_2, NULL, thread2, &thread_arg)){
        cout<< "Create thread 2 failed.\n";
        exit(-1);
    }

    //main thread
    pthread_join(*th_1, NULL);
    pthread_join(*th_2, NULL);

    //destroy mutex
    pthread_mutex_destroy(&mutex);
}

