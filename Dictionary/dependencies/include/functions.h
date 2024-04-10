#pragma once
#include "lib.h"

string toLower(string& str);

class DictionaryWork {
public:
	const vector<string> FILENAMES;
	map<string, int> dictionary;
	vector<string> newWords;
	vector<string> files;
	vector<string> missingWords;
	string fileCheck = "";
	int newWordsCount = 0;
	int existingWordsCount = 0;
	int Errors = 0;

private:
	string cleanText(string str);
	void saveDictionary(string filename);
	void loadDictionary(string filename);
	void workWithWords(string& filename);
	vector<string> getFiles(const string& path);
	bool isMistakes(const string& word1, const string& word2, size_t index1,
		size_t index2, int mistake);
	bool containsDigit(const string& str);

public:
	DictionaryWork(string path);
	void checkFileWord(const string& fileCheck);
	void fixingMistakes(const string& fileCheck);
};


