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
    shutDown(); // if still running, shut down
};


// Miscellaneous functions
int ThreadPool::getThreadCount(){
    return threadCount;
};


// Important functions

void ThreadPool::worker(){
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        condition.wait(lock, [this] { // waiting to be notified of something
            return !taskQueue.empty() || !running; 
        });

        if (!running && taskQueue.empty()) {
            return; // shutdown, nothing left
        }

        std::function<void()> task = taskQueue.front();
        taskQueue.pop();
        lock.unlock();

        execute(task);
    }
};

void ThreadPool::submit(std::function<void()> task){
    {
        std::lock_guard<std::mutex> lock(queueMutex); // locks queue mutex till it adds everything so nothing can be messed up

        if (!running) {
            throw std::runtime_error("Thread pool is shut down");
        }

        taskQueue.push(task); // add to queue
    }

    condition.notify_one(); // notifes one thread that a task was added

}; 

void ThreadPool::execute(std::function<void()> task){
    task(); // executes the task function

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        shared_counter++;
    }
};

void ThreadPool::shutDown(){
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        running = false;
    }

    condition.notify_all(); // notifes all threads to shut down

    // close all threads
    for (auto& worker: workers){
        if (worker.joinable()) {
            worker.join();
        }
    }
}; 