//
// Created by bohdan on 5/29/17.
//
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <condition_variable>
#include "mainFunctions.h"

using namespace std;

int producer(string filename, size_t block_size, deque<vector<string>> &dataBatches, mutex &dequeMut, condition_variable cv, atomic <bool> done) {
    fstream file(filename); //full path to the file
    if (!file.is_open()) {
        cout << "error reading from file";
        return  0;
    }

    string line;
    vector<string> oneBatch;
    int currentLine = 0;
    while(getline(file, line)) {
        oneBatch.push_back(line);
        if(currentLine == BATCH_SIZE) {
            {
                lock_guard<mutex> lg(dequeMut);
                dataBatches.push_back(oneBatch);
            }
            cv.notify_one();
            oneBatch.clear();
            currentLine = 0;
        } else {
            currentLine++;
        }
    }
    if(oneBatch.size() != 0) {
        {
            lock_guard<mutex> lg(dequeMut);
            dataBatches.push_back(oneBatch);
        }
        cv.notify_one();
    }
    cv.notify_all();
    done = true;
    return 1;
}

int consumer(map<string, int> &countedWords) {
    
}