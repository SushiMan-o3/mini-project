#ifndef THREADPOOL_H // use pragma once
#define THREADPOOL_H // remove this uf pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class ThreadPool {
    private: // private cause it will only be called in the function
        int threadCount; // how many threads there are
        bool running; // whether program is running or not

        std::queue<std::function<void()>> taskQueue; // all tasks that haven't been finished
        std::vector<std::thread> workers; // contains all threads

        std::mutex queueMutex; // prevent multiple threads from running same task
        int shared_counter; 

        std::condition_variable condition; // will put thread to sleep if condition holds

        void worker(); // each thread has a worker function it run that just executes tasks from queue

        void execute(std::function<void()> task); // executes task function


    public: // public, user needs these functions
        // constructors and destructors
        ThreadPool(int threads);
        ~ThreadPool();

        int getThreadCount(); // returns the number of threads in the pool

        void submit(std::function<void()> task); // submits tasks to task queue

        void shutDown(); // finishes all tasks then closes all threads, sets running to false
};

#endif // remove this uf pragma once