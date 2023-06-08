#ifndef THREADPOOLSIMPLIFIED_THREADPOOL_H
#define THREADPOOLSIMPLIFIED_THREADPOOL_H
#include "TaskQueue.h"
#include "vector"
#include "thread"
#include "chrono"
#include "mutex"


class ThreadPool {
    vector<thread> workers;
    int num_of_threads;
    bool activated = false;
    bool initialized = false;
    mutex mutex_;

public:
    ThreadPool(int num_of_threads);
    void routine(TaskQueue* toPerform, int stopId);
    void terminate();
    bool activate(TaskQueue* toPerform, int stopID, condition_variable* next_iteration, bool* finished);
    Task* getTask(TaskQueue* toPerform, int stopID);
};


#endif
