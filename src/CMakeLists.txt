add_library(MyLibrary Account.cpp cli.cpp task.cpp run.cpp thread1.cpp thread2.cpp)

add_executable(MySchedule main.cpp)

target_link_libraries(MySchedule MyLibrary)
