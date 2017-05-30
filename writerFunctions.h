//
// Created by bohdan on 5/30/17.
//

#ifndef COUNTINGWORDSPART2_WRITERFUNCTIONS_H
#define COUNTINGWORDSPART2_WRITERFUNCTIONS_H
void writeByAlphabet(std::map<std::string,int> m, std::string filepath);
void writeByNumber(std::map<std::string, int> m, std::string filepath);
std::vector<std::vector<std::string>> mapToVector(std::map<std::string, int> m1);
bool compareFunc(const std::vector<std::string>& v1, const std::vector<std::string>& v2);

#endif //COUNTINGWORDSPART2_WRITERFUNCTIONS_H
