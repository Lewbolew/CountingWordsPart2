#include <iostream>
#include <thread>
#include "mainFunctions.h"
using namespace std;

int main() {
    deque<vector<string>> dequeVectors;
    map<string, int> wordsCountMap;
    string filename = "example.txt";
    int blockSize = 10;
    condition_variable cv;
    mutex mutexDeque;
    mutex mutexMap;
    atomic <bool> done = {false};
    int threadsNumber = 5;

    thread producer = thread(producer, filename, blockSize, ref(dequeVectors), ref(mutexDeque),
    ref(cv), ref(done));
    thread consumers[threadsNumber];

    for(int i = 0; i < threadsNumber; i++) {
        consumers[i] = thread(consumer, ref(wordsCountMap), ref(dequeVectors), ref(mutexDeque),
                              ref(mutexMap), ref(cv), ref(done));
    }

    for(int j = 0; j < threadsNumber; j++) {
        consumers[j].join();
    }





    return 0;

}