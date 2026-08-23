#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

struct Task {
    int taskID;
    std::function<void()> taskFunction;
};

class ThreadPool {
    private: // private cause it will only be called in the function
        int threadCount;
        bool running;

        std::queue<Task> taskQueue;
        std::vector<std::thread> workers;
        // need mutex (dont know what that is)
        // need condition variable (dont know what that is)

        void worker(); // each thread has a worker function it run that just executes tasks from queue

        void execute(Task task); // executes task function

    public: // public, user needs these functions
        ThreadPool() {
            threadCount = 2;
            running = false;
        }

        ThreadPool(int threads) {
            threadCount = threads;
            running = false;
        }

        ~ThreadPool() {
            shutDown();
            // figure out a way to clean up threads and tasks
            running = false;
            std::cout << "ThreadPool destroyed" << std::endl;
        }

        int getThreadCount(); // returns the number of threads in the pool

        void start(); // create threadcount number of worker queue, sets running to true and accepts tasks

        void submit(Task task); // submits tasks to task queue

        void shutDown(); // finishes all tasks then closes all threads, sets running to false
};

#endif
