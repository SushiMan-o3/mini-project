#include <iostream>
#include "ThreadPool.h"


// Constructors and Destructors for ThreadPool Class
ThreadPool::ThreadPool(int numofthreads) {
    threadCount = numofthreads;
    running = true;
    shared_counter = 0;

    for (int i = 0; i < threadCount; i++){
        workers.emplace_back(&ThreadPool::worker, this); // creating a thread running worker
    }
};

ThreadPool::~ThreadPool() {
    shutDown();
};


// Miscellaneous functions
int ThreadPool::getThreadCount(){
    return threadCount;
};


// Important functions

void ThreadPool::worker(){
    while (running) {
        // should be a loop where it is either excuting the task
        // or it should be sleeping until it is notifed that a 
        // new task popped up then execute is called on it 
    }
};

void ThreadPool::submit(std::function<void()> task){
    {
        std::lock_guard<std::mutex> lock(queueMutex); // locks queue mutex till it adds everything so nothing can be messed up

        if (!running) {
            throw std::runtime_error("Thread pool is shut down");
        }

        taskQueue.push(task);
    }

    // notify one thread that a new task has been added
}; 

void ThreadPool::execute(std::function<void()> task){
    task(); // executes the task function
};

void ThreadPool::shutDown(){
    running = false; 

    // waits till all threads are done executing
    
    // close all threads
    for (auto& worker: workers){
        worker.join();
    }
}; 