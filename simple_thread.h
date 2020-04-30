#ifndef MULTI_THREAD_SIMPLE_THREAD_H
#define MULTI_THREAD_SIMPLE_THREAD_H

#include <iostream>
#include <thread>

static bool s_Finished = false;

void DoWork() {
    using namespace std::literals::chrono_literals;
    while (!s_Finished) {
        std::cout << "working...\n";
        std::this_thread::sleep_for(100ms);
    }
}

void DoSleep() {
    using namespace std::literals::chrono_literals;
    while (!s_Finished) {
        std::cout << "sleeping...\n";
        std::this_thread::sleep_for(1s);
    }
}

void run() {
    std::thread worker(DoWork);
    std::thread sleep(DoSleep);

    std::cin.get();
    s_Finished = true;

    worker.join();
    sleep.join();

    std::cout << "finished!";

    std::cin.get();
}

#endif //MULTI_THREAD_SIMPLE_THREAD_H
