#include <iostream>
#include <thread>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "mainFunctions.h"
using namespace std;


int main() {
    deque<vector<string>> dequeVectors;
    map<string, int> wordsCountMap;
    string filename = "example";
    int blockSize = 2;
    condition_variable cv;
    mutex mutexDeque;
    atomic <bool> done = {false};
    mutex mutexMap;
    int threadsNumber = 2;
    thread producer = thread(producerFunc, filename, blockSize, ref(dequeVectors), ref(mutexDeque), ref(cv), ref(done));
    thread consumers[threadsNumber];
    for(int i = 0; i < threadsNumber; i++) {
        consumers[i] = thread(consumerFunc, ref(wordsCountMap), ref(dequeVectors), ref(mutexDeque),
                              ref(mutexMap), ref(cv), ref(done));
    }


    for(int j = 0; j < threadsNumber; j++) {
        consumers[j].join();
    }
    producer.join();

    for (const auto &p : wordsCountMap) {
        std::cout <<p.first << ": " << p.second << '\n';
    }

    return 0;

}