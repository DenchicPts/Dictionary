#include "lib.h"
static map<string, int> dictionary;
static vector<string> newWords;

vector<string> getFiles(const string& path) {
    vector<string> files;
    for (const auto& entry : filesystem::directory_iterator(path)) {
        files.push_back(entry.path().string());
    }
    return files;
}


int main() {
    dictionary = loadDictionary("dictionary.txt");
    // �������� ���������� �����

    vector<string> files = getFiles("\Text");

    
    // �������� ��� ����� � ������������ ����
    int newWordsCount = 0;
    int existingWordsCount = 0;



    for (auto& name : files)
    {
        workWithWords(name, newWordsCount, existingWordsCount, dictionary, newWords);

    }

    



    cout << "Added new words: " << newWordsCount << endl;
    cout << "We found this words: " << existingWordsCount << endl;
    
    // ����� ������ ����� ����
    cout << "New words:" << endl;
    for (string word : newWords) {
        cout << word << "   ";
    }
    saveDictionary("dictionary.txt", dictionary, files);

    return 0;
}




