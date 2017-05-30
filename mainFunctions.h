//
// Created by bohdan on 5/29/17.
//
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <mutex>
#include <atomic>

#ifndef COUNTINGWORDSPART2_MAINFUNCTIONS_H
#define COUNTINGWORDSPART2_MAINFUNCTIONS_H
#define BATCH_SIZE 50

int producer(std::string filename, size_t block_size, std::deque<std::vector<std::string>> &dataBatches, std::mutex &dequeMut);
int consumer(std::map<std::string, int> &countedWords);
int producer(std::string filename, size_t block_size, std::deque<std::vector<std::string>> &dataBatches,
             std::mutex &dequeMut, std::condition_variable cv, std::atomic<bool> done);

#endif //COUNTINGWORDSPART2_MAINFUNCTIONS_H
