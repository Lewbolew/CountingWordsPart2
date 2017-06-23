//
// Created by bohdan on 6/23/17.
//
#include <string>
#include <vector>
#ifndef COUNTINGWORDSPART2_CONFIGREADER_H
#define COUNTINGWORDSPART2_CONFIGREADER_H

std::vector<std::string> configurationReader(std::string filepath);
std::string betweenQuotes(std::string s);
int intParser(std::string s);

#endif //COUNTINGWORDSPART2_CONFIGREADER_H
