#!/bin/bash

# 测试脚本: shell.sh
# 用途: 测试MySchedule程序的基本功能


ROOT_DIR=$(cd $(dirname $0);cd ..; pwd)

echo "--------------------------------------------------------------"
echo "This file is used to test basic function of Schedule program."

echo "--------------------------------------------------------------"
echo "[Task 0] Start to run the cmakelist."
cd $ROOT_DIR
cmake -B build
cmake --build build
cmake --install build

echo "--------------------------------------------------------------"
echo "[Task 1] Test the fuction of register."
cd $ROOT_DIR
./bin/MySchedule register -u TestUser1 -p TestUser1
./bin/MySchedule register -u TestUser2 -p TestUser2
echo "Register TestUser1 and TestUser2 successfully."

echo "--------------------------------------------------------------"
echo "[Task 2] Test the fuction of addtask."
./bin/MySchedule addtask -u TestUser1 -p TestUser1 -n task1 
echo "Add task1 with default priority, category, start time, remind time and detail to TestUser1 successfully."
./bin/MySchedule addtask -u TestUser1 -p TestUser1 -n task2 -o HIGH -c STUDY -s 2025-01-01/00:00:00
echo "Add task2 with specified start time and default reminder time to TestUser1 successfully."
./bin/MySchedule addtask -u TestUser1 -p TestUser1 -n task3 -o MODERATE -c LIFE -s 2025-01-02/00:00:00 -r 2025-01-01/00:00:00 -d "This is test task 3."
./bin/MySchedule addtask -u TestUser1 -p TestUser1 -n task4 -o LOW -c WENTERTAINMENT -s 2025-01-03/00:00:00 -r 2025-01-02/00:00:00 -d "This is test task 4."
./bin/MySchedule addtask -u TestUser1 -p TestUser1 -n task5 -o HIGH -c STUDY -s 2025-01-04/00:00:00 -r 2025-01-03/00:00:00 -d "This is test task 5."
./bin/MySchedule addtask -u TestUser1 -p TestUser1 -n task6 -o MODERATE -c NONE -s 2025-01-05/00:00:00 -r 2025-01-04/00:00:00 -d "This is test task 6."
echo "Add task3, task4, task5 and task6 with all specified argument to TestUser1 successfully."

echo "--------------------------------------------------------------"
echo "[Task 3] Test the fuction of displaytask."
./bin/MySchedule displaytask -u TestUser1 -p TestUser1 -k id
echo "Display all tasks of TestUser1 sorted by id successfully."
./bin/MySchedule displaytask -u TestUser1 -p TestUser1 -k priority
echo "Display all tasks of TestUser1 sorted by priority successfully."
./bin/MySchedule displaytask -u TestUser1 -p TestUser1 -k category
echo "Display all tasks of TestUser1 sorted by category successfully."
./bin/MySchedule displaytask -u TestUser2 -p TestUser2 -k id
echo "Display all tasks of TestUser2 sorted by id successfully."

echo "--------------------------------------------------------------"
echo "[Task 4] Test the fuction of edittask."
./bin/MySchedule edittask -u TestUser1 -p TestUser1 -i 1 -n testtask1 -o HIGH -c STUDY -s 2025-01-02/00:00:00 -r 2025-01-01/00:00:00 -d "This is test task 1 that has been editted."
./bin/MySchedule edittask -u TestUser1 -p TestUser1 -i 2 -n testtask2 -o MODERATE -c LIFE -s 2025-01-03/00:00:00 -r 2025-01-02/00:00:00 -d "This is test task 2 that has been editted."
echo "Edit task1 and task2 of TestUser1 successfully."
./bin/MySchedule displaytask -u TestUser1 -p TestUser1 -k id

echo "--------------------------------------------------------------"
echo "[Task 5] Test the fuction of deltask."
./bin/MySchedule deltask -u TestUser1 -p TestUser1 -i 1
./bin/MySchedule deltask -u TestUser1 -p TestUser1 -i 4
echo "Delete task1 and task4 of TestUser1 successfully."
./bin/MySchedule displaytask -u TestUser1 -p TestUser1 -k id

echo "--------------------------------------------------------------"
echo "[Task 6] Test the fuction of checkremind."
./bin/MySchedule checkremind -u TestUser1 -p TestUser1

echo "--------------------------------------------------------------"
echo "[Task 7] Test the fuction of changepassword."
./bin/MySchedule changepassword -u TestUser1 -p TestUser1 -n TestUser1New
echo "Change password of TestUser1 to TestUser1New successfully."

echo "--------------------------------------------------------------"
echo "[Task 8] Test the fuction of deregister."
./bin/MySchedule deregister -u TestUser1 -p TestUser1New
./bin/MySchedule deregister -u TestUser2 -p TestUser2
echo "Deregister TestUser1 and TestUser2 successfully."

echo "--------------------------------------------------------------"
echo "All test cases have been completed successfully."
