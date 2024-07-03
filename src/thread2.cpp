#include"head.h"
#include"task.h"

using namespace std;

void *thread2(void* arg){
    cout << "Begin to check remind time!" << endl;

    //get thread info
    ThreadInfo* th_2 = (ThreadInfo*)arg;
    pthread_mutex_t* mutex = th_2->mutex;
    User* user = th_2->user;
    bool running = th_2->running;
    
    //checktask
    while(1){
        //check running
        if(running == false){
            return NULL;
        }
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

        //sleep 2s
        sleep(2);
    }

    return NULL;
   
}
