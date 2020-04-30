#ifndef MULTI_THREAD_MUTEX_H
#define MULTI_THREAD_MUTEX_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>


int GetRandom(int max) {
    srand(time(NULL));
    return random() % max;
}

void ExecuteThread(int id) {
    auto nowTime = std::chrono::system_clock::now();
    std::time_t sleepTime = std::chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);

    std::cout << "Thread " << id
              << " Sleep Time : " << std::ctime(&sleepTime)
              << "\n";;

    std::cout << myLocalTime.tm_hour
              << ":" << myLocalTime.tm_min
              << ":" << myLocalTime.tm_sec
              << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(GetRandom(5)));
    nowTime = std::chrono::system_clock::now();
    sleepTime = std::chrono::system_clock::to_time_t(nowTime);
    std::cout << "Thread " << id
              << " Awake Time : " << std::ctime(&sleepTime)
              << "\n";

}

std::string GetTime() {
    auto nowTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(nowTime);
    return std::ctime(&time);
}

double accountBalance = 100;

std::mutex acctLock;

void GetMoney(int id, double withdrawal) {
    std::lock_guard<std::mutex> lock(acctLock);
    std::cout << id << " tries to withdrawal " << withdrawal << " on " << GetTime();
    std::this_thread::sleep_for(std::chrono::seconds(3));

    if (accountBalance < withdrawal) {
        std::cout << "Not enough money!" << std::endl;
    } else {
        accountBalance -= withdrawal;
        std::cout << "New account balance is $ " << accountBalance << std::endl;
        std::cout << "Current balance is $ " << accountBalance << std::endl;
    }

    std::cout << std::endl;
}

void run() {

    std::thread threads[10];

    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(GetMoney, i, 15);
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

#endif //MULTI_THREAD_MUTEX_H
