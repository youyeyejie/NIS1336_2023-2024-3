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
    printf("Welcome to Task Manager!\n");
    printf("Please select the operation: 1.Register 2.Login 3.Quit\n");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1://register
        printf("User register:\n");
        printf("Input your username:");
        scanf("%s", username);
        printf("Input your password:");
        scanf("%s", password);
        if(account.newAccount(username, password)){
            printf("Register successfully!\n");
        }

    case 2://login
        printf("User login:\n");
        printf("Input your username:");
        scanf("%s", username);
        printf("Input your password:");
        scanf("%s", password);
        current_user = account.login(username, password);
        if(current_user.uid == -1){
            printf("Incorrect user name or password. Please check your input.\n");
            exit(-1);
        }
        printf("Login successfully! Welcome %s.\n", current_user.username);
        break;

    case 3://quit
        exit(0);
        break;
    
    default:
        printf("Unknown command! Can only accept '1' or '2'.\n");
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
    if(pthread_create(th_1, NULL, thread1, &thread_arg)){
        printf("Create thread 1 failed.\n");
        exit(-1);
    }

    //create thread2
    if(pthread_create(th_2, NULL, thread2, &thread_arg)){
        printf("Create thread 2 failed.\n");
        exit(-1);
    }

    //main thread
    pthread_join(*th_1, NULL);
    pthread_join(*th_2, NULL);

    //destroy mutex
    pthread_mutex_destroy(&mutex);
}

