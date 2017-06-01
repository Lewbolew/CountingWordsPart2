//
// Created by bohdan on 5/29/17.
//
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <mutex>
#include <atomic>
#include <condition_variable>
#ifndef COUNTINGWORDSPART2_MAINFUNCTIONS_H
#define COUNTINGWORDSPART2_MAINFUNCTIONS_H
#define BATCH_SIZE 50

int producerFunc(std::string filename, size_t block_size, std::deque<std::vector<std::string>> &dataBatches,
             std::mutex &dequeMut, std::condition_variable &cv, std::atomic <bool> &done);

int consumerFunc(std::map<std::string, int> &countedWords, std::deque<std::vector<std::string>> &dataBatches,
             std::mutex &dequeMut,std::mutex &mapMut, std::condition_variable &cv, std::atomic <bool> &done);

std::vector<std::string> wordsRedactor(const std::vector<std::string> &words);


#endif //COUNTINGWORDSPART2_MAINFUNCTIONS_H
