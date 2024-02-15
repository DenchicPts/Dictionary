#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem>

using namespace std;



string toLower( string& str);
string cleanText( string str);
void saveDictionary(string filename, map<string, int>& dict, vector<string> names);
map<string, int> loadDictionary(string filename);
void workWithWords(string& filename, int& newWordsCount, int& existingWordsCount,
    map<string, int>& dict, vector<string>& newWords);
