#include "../inc/cli.h"
#include "../inc/run.h"

using namespace std;

int main(int argc, char * argv[]){
    /*
    support commands:
    ./main run
    ./main help
    ./main displaytask -u username -p password -k kindOfDisplay
    ./main addtask -u username -p password -n name -o prio -c cat -s start_time -r remind_time -d detail 
    ./main deltask -u username -p password -i id
    ./main edittask -u username -p password -i id -n name -o prio -c cat -r rem -d detail -s start
    ./main register -u username -p password
    ./main deregister -u username -p password
    ./main changepassword -u username -p password -n newpassword
    ./main checkremind -u username -p password
    ./main login -u username -p password
    */

    if(argc < 2 || strcmp(argv[1], "run") == 0){
        run();
    }
    else if(strcmp(argv[1], "help") == 0){
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
    else if(strcmp(argv[1], "changepassword") == 0){
        changePassword(argc, argv);
    }
    else if(strcmp(argv[1], "edittask") == 0){
        editTask(argc, argv);
    }
    else if(strcmp(argv[1], "checkremind") == 0){
        checkRemindTime(argc, argv);
    }
    else{
        cout<<"Unknown command!"<< endl;
        displayHelp();
    }
    return 0;
}
