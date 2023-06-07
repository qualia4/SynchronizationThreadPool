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
    void addTask(Task *task){
        unique_lock<mutex> lock(mutex_);
        tasks.push(task);
        task_waiter.notify_one();
    }

    Task* getTask(){
        unique_lock<mutex> lock(mutex_);
        if(tasks.empty()){
            task_waiter.wait(lock);
        }
        Task* toReturn = tasks.front();
        tasks.pop();
        cout << "Thread " << this_thread::get_id() << " took the task" << endl;
        return toReturn;
    }

    bool empty(){
        unique_lock<std::mutex> lock(mutex_);
        return tasks.empty();
    }

    void clear(){
        unique_lock<std::mutex> lock(mutex_);
        while(!tasks.empty()){
            tasks.pop();
        }
    }

    int getSize(){
        unique_lock<std::mutex> lock(mutex_);
        return tasks.size();
    }
};


#endif
