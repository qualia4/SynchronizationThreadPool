#ifndef THREADPOOLSIMPLIFIED_TASKGENERATOR_H
#define THREADPOOLSIMPLIFIED_TASKGENERATOR_H
#include "Task.h"

class TaskGenerator {
    int idCounter;
public:
    TaskGenerator(){
        idCounter = 0;
    }

    Task* generateTask(){
        Task* task = new Task(idCounter);
        idCounter++;
        return task;
    }
};


#endif
