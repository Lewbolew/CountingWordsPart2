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
#include <sstream>
#include "mainFunctions.h"

using namespace std;

vector<string> wordsRedactor(const vector<string> &words) {
    vector<string> result;

    for (int k=0;k < words.size();k++) {
        string currLine = words[k];
        std::istringstream iss(currLine);
        while(iss) {
            string currWord;
            iss >> currWord;
            transform(currWord.begin(), currWord.end(), currWord.begin(), ::tolower);
            currWord.erase (remove_if (currWord.begin (), currWord.end (), ::ispunct), currWord.end ());
            result.push_back(currWord);

        }
    }
    return result;
}
int producerFunc(string filename, size_t block_size, deque<vector<string>> &dataBatches, mutex &dequeMut, condition_variable &cv, atomic<bool> &done) {
    fstream file(filename);
    if (!file.is_open()) {
        cout << "error reading from file";
        return  0;
    }

    string line;
    vector<string> oneBatch;
    int currentLine = 0;
    while(getline(file, line)) {
        oneBatch.push_back(line);
        if(currentLine == block_size) {
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

int consumerFunc(map<string, int> &countedWords, deque<vector<string>> &dataBatches, mutex &dequeMut,mutex &mapMut, condition_variable &cv, atomic <bool> &done) {
    bool checker = true;
    while(checker) {
        unique_lock<mutex> lg(dequeMut);
        if(dataBatches.size() != 0) {
            vector<string> currBatch {(vector<string> &&) dataBatches.front()};
            dataBatches.pop_front();
            lg.unlock();
            vector<string> splittedWords = wordsRedactor(currBatch);
            for(int i = 0; i < splittedWords.size(); i++) {
                if(splittedWords[i] != "") {
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