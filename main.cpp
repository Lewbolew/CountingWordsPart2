#include <iostream>
#include <thread>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "mainFunctions.h"
#include "configReader.h"
#include "writerFunctions.h"
using namespace std;

int main(int argc, char *argv[]) {
    //_______________configReading____________________________________
    vector<string> arguments = configurationReader(argv[1]);
    string nameOutputFileAlphabet = betweenQuotes(arguments[1]);
    string nameOupputFileNumber = betweenQuotes(arguments[2]);
    int threadsNumber = intParser(arguments[3]);
    //________________________________________________________________
    deque<vector<string>> dequeVectors;
    deque<map<string, int>> dequeMaps;
    map<string, int> wordsCountMap;
    int currThreadNum = 0;
    string filename = betweenQuotes(arguments[0]);
    int blockSize = 2;
    condition_variable cv;
    mutex mutexDeque;
    mutex mutexMap;
    mutex mergeMaps;
    atomic <bool> done = {false};
    thread producer = thread(producerFunc, filename, blockSize, ref(dequeVectors), ref(mutexDeque), ref(cv), ref(done));
    thread consumers[threadsNumber];
    for(int i = 0; i < threadsNumber; i++) {
        consumers[i] = thread(consumerFunc, ref(dequeMaps), ref(dequeVectors), ref(mutexDeque),
                              ref(mutexMap), ref(mergeMaps),ref(cv), ref(done));
    }


    for(int j = 0; j < threadsNumber; j++) {
        consumers[j].join();
    }
    producer.join();
    thread mergers[threadsNumber];
    for(int k = 0; k < threadsNumber; k++) {
        mergers[k] = thread(mapMerger, ref(dequeMaps), ref(mergeMaps),
        ref(threadsNumber), ref(cv), ref(currThreadNum));
    }
    for(int n = 0; n < threadsNumber; n++) {
        mergers[n].join();
    }
    for (const auto &p : dequeMaps[0]) {
        std::cout <<p.first << ": " << p.second << '\n';
    }


    // WRITES RESULTS INTO A FILES
    writeByAlphabet(dequeMaps[0], nameOutputFileAlphabet);
    writeByNumber(dequeMaps[0], nameOupputFileNumber);
    return 0;

}