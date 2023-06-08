//A thread pool is served by 4 worker threads and has one execution queue.
// Tasks are added immediately to the end of the execution queue.
// The queue of tasks is performed at intervals of 45 seconds (the buffer is filled with tasks for 45 seconds,
// which are then performed). Tasks added during the execution of the task queue are postponed to the next iteration.
// The task takes a random time between 4 and 10 seconds.


#include <iostream>
#include "TaskGenerator.h"
#include "TaskQueue.h"
#include "ThreadPool.h"
#include "vector"
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int iteration = 0;
bool activated = true;
bool *iteration_finished = new bool;
condition_variable *next_iteration = new condition_variable;
mutex mutex_;


void generateTasks(vector<int>* stopIDs, TaskQueue* taskQueue, TaskGenerator* generator){
    auto playback_begin = high_resolution_clock::now();
    bool generated = false;
    int stopID;
    while(!generated){
        Task *task = generator->generateTask();
        taskQueue->addTask(task);
        stopID = task->getId();
        auto playback_end = high_resolution_clock::now();
        auto elapsed = duration_cast<chrono::seconds>(playback_end - playback_begin);
        if(elapsed.count() >= 45){
            generated = true;
        }
        std::this_thread::sleep_for(std::chrono::duration<float>(2));
    }
    stopIDs->emplace_back(stopID);
    if(activated){
        generateTasks(stopIDs, taskQueue, generator);
    }
}

void performTasks(TaskQueue* taskQueue, ThreadPool *threadPool, vector<int>* stopIDs){
    while(activated){
        *iteration_finished = false;
        std::this_thread::sleep_for(std::chrono::duration<float>(45));
        cout << "Start performing the tasks" << endl;
        threadPool->activate(taskQueue, stopIDs->at(iteration), next_iteration, iteration_finished);
        unique_lock<mutex> lock(mutex_);
        if(!iteration_finished){
            next_iteration->wait(lock);
        }
        iteration++;
        cout << "Iteration finished. Sleeping..." << endl;
    }
}



int main() {
    auto taskGenerator = new TaskGenerator();
    auto taskQueue = new TaskQueue();
    auto threadPool = new ThreadPool(4);
    auto stopIDs = new vector<int>;
    thread generator(generateTasks, stopIDs, taskQueue, taskGenerator);
    std::this_thread::sleep_for(std::chrono::duration<float>(5));
    thread performer(performTasks, taskQueue, threadPool, stopIDs);
    string end;
    cin >> end;
    threadPool->terminate();
    cout << "ended" << endl;
}


