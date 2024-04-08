#pragma once
#include "lib.h"


class DictionaryWork {
public:
	vector<string> FILENAMES;
	map<string, int> dictionary;
	vector<string> newWords;
	vector<string> files;
	vector<string> missingWords;
	int newWordsCount = 0;
	int existingWordsCount = 0;
	int Errors = 0;

private:
	string toLower(string& str);
	string cleanText(string str);
	void fileSearch(const string& path);
	void saveDictionary(string filename);
	void loadDictionary(string filename);
	void workWithWords(string& filename);
	vector<string> getFiles(const string& path);

public:
	DictionaryWork(string path, string checkFile);
};


