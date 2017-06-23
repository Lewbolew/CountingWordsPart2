//
// Created by bohdan on 5/30/17.
//
#include <map>
#include <vector>

#ifndef COUNTINGWORDSPART2_WRITERFUNCTIONS_H
#define COUNTINGWORDSPART2_WRITERFUNCTIONS_H
void writeByAlphabet(const std::map<std::string,int> &m, const std::string &filepath);
void writeByNumber(const std::map<std::string, int> &m, const std::string &filepath);

std::vector<std::vector<std::string>> mapToVector(const std::map<std::string, int> &m1);
bool compareFunc(const std::vector<std::string>& v1, const std::vector<std::string>& v2);

#endif //COUNTINGWORDSPART2_WRITERFUNCTIONS_H
