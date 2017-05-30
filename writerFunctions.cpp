//
// Created by bohdan on 5/30/17.
//
#include <fstream>
#include <algorithm>
#include "writerFunctions.h"
using namespace std;

bool compareFunc(const vector<string>& v1, const vector<string>& v2)
{
    return stoi(v1[1]) > stoi(v2[1]);
}

vector<vector<string>> mapToVector(map<string, int> m1)
{
    vector<vector<string>> v;
    for(auto mapIterator = m1.begin();
        mapIterator != m1.end();
        mapIterator++)
    {
        vector<string> temp;
        temp.push_back(mapIterator->first);
        temp.push_back(to_string(mapIterator->second));
        v.push_back(temp);
    }
    return  v;
}

void writeByAlphabet(map<string,int> m, string filepath) {
    ofstream fileWithSortedAlph;

    fileWithSortedAlph.open(filepath);

    for(auto wordsCountIterator = m.begin();
        wordsCountIterator != m.end();
        wordsCountIterator++) {
        fileWithSortedAlph << wordsCountIterator->first << " : "<< wordsCountIterator->second<< endl;
    }

    fileWithSortedAlph.close();
}

void writeByNumber(map<string, int> m, string filepath) {
    ofstream fileWithSortedNumb;

    fileWithSortedNumb.open(filepath);

    vector<vector<string>> v = mapToVector(m);
    sort(v.begin(), v.end(), compareFunc);
    for (vector<string> subv: v)
    {
        fileWithSortedNumb << subv[0] << " : " << subv[1] << endl;
    }

    fileWithSortedNumb.close();
}

