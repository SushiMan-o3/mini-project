# Thread Pool
## What is a thread pool?
A thread pool is a group of created worker threads that are assigned tasks then reassigned tasks and reused. Tasks often wait in the thread queue until it is dequeued and an thread picks it up and does what it is assigned. Once a thread it is done, it goes back to waiting for an unfinished task and the cycle continues.


### What are threads
Threads are similar to workers that a program can run. Each program starts with one thread main() but you can spin up multiple threads to work at the same time or interleave them (if the CPU has multiple cores).

A more sofisticated definition of a thread is an independent sequence of instructions a program can run. 

## How it works?
There are three parts to a thread pool. 

1. Worker Threads - The Actual threads that execute the task
2. Task Queue - Stores tasks that are waiting to be executed
3. Thread Pool Manager - Decides what happens when a new task arrives (create a new thread or put it in the task queue)

The general flow of how a thread pool works is demonstrated in the image below
![alt text](image.png)

There are three main functions: 
1. Submit() - Submits a new task to the thread pool and returns a future which allows you to retrive the result later
2. Execute() - Executes a task and does not return a result
3. ShutDown() - Finishes all tasks and stops accepting other tasks

These functions are used to manage the thread pool. 

There are different factors that play a factor in the decisions that a thread pool makes. The following are corePoolSize, maximumPoolSize, workQueue, keepAliveTim and rejectionHandler. These factors determine what happen next in a thread queue such as create a new thread. 

For this thread pool in particular, the design that I am currently thinking about is doing if the taskQueue is basically double the amount of threads (i.e., 2 * threads = length of task queue), then the task queue will be increased by half of t he number of threads in the thread pool (i.e., number of threads = 1/2 * number of threads + number of threads). 


## Why use a thread pool?
The benefit of using a thread pool comes from the fact that creating new threads every single time is not efficent. So reusing the same threads over and over can save a lot of time and be more efficent in terms of CPU usage since it is using up less cores. 

## Implementation


## Important Concepts
### Concurrency vs Parellelism


### Synchronization


