//
// Created by bohdan on 5/29/17.
//
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <condition_variable>
#include <algorithm>
#include "mainFunctions.h"

using namespace std;

void wordsRedactor(vector<string> &words) {
    for (int k=0;k < words.size();k++) {
        transform(words[k].begin(), words[k].end(), words[k].begin(), ::tolower);
        words[k].erase (remove_if (words[k].begin (), words[k].end (), ::ispunct), words[k].end ());
    }
}
int producer(string filename, size_t block_size, deque<vector<string>> &dataBatches, mutex &dequeMut, condition_variable &cv, atomic <bool> &done) {
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

int consumer(map<string, int> &countedWords, deque<vector<string>> &dataBatches, mutex &dequeMut,mutex &mapMut, condition_variable &cv, atomic <bool> &done) {
    bool checker = true;
    while(checker) {
        unique_lock<mutex> lg(dequeMut);
        if(dataBatches.size() != 0) {
            vector<string> currBatch {(vector<string> &&) dataBatches.front()};
            dataBatches.pop_front();
            lg.unlock();
            wordsRedactor(currBatch);
            for(int i = 0; i < currBatch.size(); i++) {
                if(currBatch[i] != "") {
                    ++countedWords[currBatch[i]];
                }
            }
        } else {
            if(done) {
                break;
            } else{
                cv.wait(lg);
            }
        }
    }
    return 0;
}