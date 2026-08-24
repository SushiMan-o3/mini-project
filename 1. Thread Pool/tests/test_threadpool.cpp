#include <atomic>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "ThreadPool.h"

// Minimal hand-rolled test harness (no external framework required).

static int g_failures = 0;

#define CHECK(cond) \
    do { \
        if (!(cond)) { \
            std::cerr << "  FAILED: " << #cond << " (line " << __LINE__ << ")\n"; \
            g_failures++; \
        } \
    } while (0)

#define RUN_TEST(fn) \
    do { \
        std::cout << "Running " << #fn << "...\n"; \
        fn(); \
    } while (0)


// getThreadCount() should report back exactly what was passed to the constructor.
void test_thread_count() {
    ThreadPool pool(4);
    CHECK(pool.getThreadCount() == 4);
}

// A single submitted task should actually run.
void test_single_task_runs() {
    ThreadPool pool(2);
    std::atomic<bool> ran{false};

    pool.submit([&ran] { ran = true; });
    pool.shutDown(); // waits for all queued tasks to finish

    CHECK(ran.load());
}

// Every submitted task should run exactly once, even with more tasks than threads.
void test_all_tasks_run() {
    const int numTasks = 100;
    ThreadPool pool(4);
    std::atomic<int> counter{0};

    for (int i = 0; i < numTasks; i++) {
        pool.submit([&counter] { counter++; });
    }
    pool.shutDown();

    CHECK(counter.load() == numTasks);
}

// Tasks queued before shutDown() is called must still run to completion.
void test_shutdown_drains_queue() {
    const int numTasks = 20;
    std::atomic<int> counter{0};

    {
        ThreadPool pool(2);
        for (int i = 0; i < numTasks; i++) {
            pool.submit([&counter] {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                counter++;
            });
        }
        // destructor calls shutDown(), which should block until all tasks finish
    }

    CHECK(counter.load() == numTasks);
}

// Submitting after shutDown() should be rejected, not silently dropped.
void test_submit_after_shutdown_throws() {
    ThreadPool pool(2);
    pool.shutDown();

    bool threw = false;
    try {
        pool.submit([] {});
    } catch (const std::runtime_error&) {
        threw = true;
    }

    CHECK(threw);
}

// With multiple threads, independent sleeping tasks should overlap rather than
// run strictly one-after-another.
void test_tasks_run_concurrently() {
    const int numTasks = 4;
    const auto taskDuration = std::chrono::milliseconds(100);

    ThreadPool pool(numTasks);
    auto start = std::chrono::steady_clock::now();

    std::atomic<int> counter{0};
    for (int i = 0; i < numTasks; i++) {
        pool.submit([&counter, taskDuration] {
            std::this_thread::sleep_for(taskDuration);
            counter++;
        });
    }
    pool.shutDown();

    auto elapsed = std::chrono::steady_clock::now() - start;
    CHECK(counter.load() == numTasks);
    // Sequential execution would take ~numTasks * taskDuration; parallel execution
    // should comfortably finish in well under that.
    CHECK(elapsed < taskDuration * numTasks);
}


int main() {
    RUN_TEST(test_thread_count);
    RUN_TEST(test_single_task_runs);
    RUN_TEST(test_all_tasks_run);
    RUN_TEST(test_shutdown_drains_queue);
    RUN_TEST(test_submit_after_shutdown_throws);
    RUN_TEST(test_tasks_run_concurrently);

    if (g_failures == 0) {
        std::cout << "\nAll tests passed.\n";
        return 0;
    } else {
        std::cout << "\n" << g_failures << " check(s) failed.\n";
        return 1;
    }
}
