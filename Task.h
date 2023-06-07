#ifndef THREADPOOLSIMPLIFIED_TASK_H
#define THREADPOOLSIMPLIFIED_TASK_H
#include "iostream"
#include <cstdlib>
#include <ctime>
using namespace std;

class Task {
    int id;
    float time_to_perform;

public:
    Task(int id){
        this->id = id;
        srand(time(0));
        time_to_perform = (static_cast<float>(rand() % 70 + 40)) / 10;
    }

    float getTime(){
        return time_to_perform;
    }

    int getId(){
        return id;
    }

};


#endif
