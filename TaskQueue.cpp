#include "TaskQueue.h"

void TaskQueue::addTask(Task *task){
    unique_lock<mutex> lock(mutex_);
    tasks.push(task);
    task_waiter.notify_one();
}

Task* TaskQueue::getTask(){
    unique_lock<mutex> lock(mutex_);
    if(tasks.empty()){
        task_waiter.wait(lock);
    }
    Task* toReturn = tasks.front();
    tasks.pop();
    cout << "Thread " << this_thread::get_id() << " took the task" << endl;
    return toReturn;
}

bool TaskQueue::empty(){
    unique_lock<std::mutex> lock(mutex_);
    return tasks.empty();
}

void TaskQueue::clear(){
    unique_lock<std::mutex> lock(mutex_);
    while(!tasks.empty()){
        tasks.pop();
    }
}

int TaskQueue::getSize(){
    unique_lock<std::mutex> lock(mutex_);
    return tasks.size();
}




