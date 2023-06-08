#include "TaskGenerator.h"

TaskGenerator::TaskGenerator(){
    idCounter = 0;
}

Task* TaskGenerator::generateTask(){
    Task* task = new Task(idCounter);
    idCounter++;
    return task;
}


