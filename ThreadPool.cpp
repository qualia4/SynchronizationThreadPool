#include "ThreadPool.h"

ThreadPool::ThreadPool(int num_of_threads){
    this->num_of_threads = num_of_threads;
    workers.reserve(num_of_threads);
}

void ThreadPool::routine(TaskQueue* toPerform, int stopId) {
    while (activated) {
        Task* task = getTask(toPerform, stopId);
        std::this_thread::sleep_for(std::chrono::duration<float>(task->getTime()));
        cout << "Task " << task->getId() << " done by thread " << this_thread::get_id() << endl;
    }
}

void ThreadPool::terminate(){
    if(activated){
        for(int i = 0; i < num_of_threads; i++){
            workers[i].detach();
        }
    }
}

bool ThreadPool::activate(TaskQueue* toPerform, int stopID, condition_variable* next_iteration, bool* finished){
    unique_lock<std::mutex> lock(mutex_);
    if(activated){
        cout << "Thread pool already working" << endl;
        return false;
    }
    activated = true;
    if(!initialized){
        for(int i = 0; i < num_of_threads; i++){
            workers.emplace_back([this, toPerform ,stopID]{ routine(toPerform, stopID);});
        }
        initialized = true;
    }else{
        for(int i = 0; i < num_of_threads; i++){
            workers.at(i) = std::thread(&ThreadPool::routine, this, toPerform, stopID);
        }
    }
    for(int i = 0; i < num_of_threads; i++){
        workers[i].join();
    }
    *finished = true;
    next_iteration->notify_one();
}

Task* ThreadPool::getTask(TaskQueue* toPerform, int stopID){
    if(!activated){
        terminate();
    }
    Task *task = toPerform->getTask();
    if(task->getId() == stopID){
        activated = false;
    }
    return task;
}