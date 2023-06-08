#include "Task.h"

Task::Task(int id){
    this->id = id;
    srand(time(0));
    time_to_perform = (static_cast<float>(rand() % 70 + 30)) / 10;
    //cout << "Task" << id << " created. Time to perform " << time_to_perform << " seconds" << endl;
}

float Task::getTime(){
    return this->time_to_perform;
}

int Task::getId(){
    return id;
}
