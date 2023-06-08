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
    Task(int id);
    float getTime();
    int getId();
};


#endif
