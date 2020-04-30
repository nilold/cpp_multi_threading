#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>

std::mutex vectorLock;

std::vector<unsigned> primeVector;

void FindPrime(unsigned start, unsigned end) {
    for (unsigned x = start; x <= end; x += 2) {
        for (unsigned y = 2; y < x; y++) {
            if ((x % y) == 0) {
                break;
            } else if ((y + 1) == x) {
                vectorLock.lock();
                primeVector.push_back(x);
                vectorLock.unlock();
            }
        }
    }
}

void FindPrimesWithThreads(unsigned start, unsigned end, unsigned numThreads){
    std::vector<std::thread> threadVector;
    unsigned threadSpread = end / numThreads;
    unsigned newEnd = start + threadSpread - 1;
    for(unsigned x=0; x< numThreads; x++){
        threadVector.emplace_back(FindPrime, start, newEnd);
        start += threadSpread;
        newEnd += threadSpread;
    }

    for(auto& t : threadVector){
        t.join();
    }
}


int main() {
    int startTime = clock();
    FindPrimesWithThreads(1, 200000, 1);
    int endTime = clock();

    for(auto i: primeVector)
        std::cout << i << ",";
    std::cout << "\b\n";

    std::cout << "execution time = " << (endTime - startTime)/double(CLOCKS_PER_SEC) << std::endl;


    return 0;
}
