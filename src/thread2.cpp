#include "../inc/thread2.h"

using namespace std;

void *thread2(void* arg){
    cout << "Begin to check remind time!" << endl;

    //get thread info
    ThreadInfo* th_2 = (ThreadInfo*)arg;
    pthread_mutex_t* mutex = th_2->mutex;
    User* user = th_2->user;
    bool* running = &th_2->running;
    
    //checktask
    while(*running){
        //read tasklist
        pthread_mutex_lock(mutex);
        vector<Task> tasklist = loadTaskFromFile(user);
        pthread_mutex_unlock(mutex);

        //check remind time
        checkRemindTime(tasklist);

        //save tasklist
        pthread_mutex_lock(mutex);
        saveTask2File(tasklist, user);
        pthread_mutex_unlock(mutex);

        //sleep 1s
        sleep(1);
    }

    return NULL;
   
}
