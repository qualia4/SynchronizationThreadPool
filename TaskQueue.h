#ifndef THREADPOOLSIMPLIFIED_TASKQUEUE_H
#define THREADPOOLSIMPLIFIED_TASKQUEUE_H
#include "Task.h"
#include "queue"
#include <thread>
#include <shared_mutex>

class TaskQueue {
    queue<Task*> tasks;
    mutex mutex_;
    condition_variable task_waiter;

public:
    void addTask(Task *task);
    Task* getTask();
    bool empty();
    void clear();
    int getSize();
};


#endif
