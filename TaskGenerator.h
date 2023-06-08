#ifndef THREADPOOLSIMPLIFIED_TASKGENERATOR_H
#define THREADPOOLSIMPLIFIED_TASKGENERATOR_H
#include "Task.h"

class TaskGenerator {
    int idCounter;
public:
    TaskGenerator();
    Task* generateTask();
};


#endif
