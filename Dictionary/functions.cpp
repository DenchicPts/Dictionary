#include "lib.h"

vector<string> FILENAMES;

// ������� ��� �������������� ����� � ������ �������
string toLower(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


// ������� ��� ������� ������ �� ������ ����������
string cleanText(string str) {
    string result;
    if (str.empty() or str.length() >= 255)
        return result;
    for (char c : str)
        //isalnum(c) ���� ������� ���������� �������� �������� ����� ������
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            result += c;


    return result;
}

// ������� ��� ���������� ������� � ���� .txt
void saveDictionary(string filename, map<string, int>& dict, vector<string> names) {
    ofstream outfile(filename);

    if (!outfile.is_open()) {
        cout << "������ �������� �����!" << endl;
        return;
    }
	outfile << names.size() << endl;
    for (auto& n : names)
    {
        outfile << n << endl;
    }


    for (auto it : dict)
        outfile << it.first << " " << it.second << endl;


    outfile.close();
}

// ������� ��� �������� ������� �� ����� .txt
map<string, int> loadDictionary(string filename) {
    ifstream infile(filename);
    map<string, int> dict;
    if (!infile.is_open())
        return dict;

    string word;
    int count;
  
    if (!getline(infile, word))
        return dict;
    



    int i = stoi(word);
    for (; i > 0; i--) {
        getline(infile, word);
		FILENAMES.push_back(word);
    }
    

    while (infile >> word >> count)
        dict[word] = count;

    infile.close();

    return dict;
}


void workWithWords(string& filename, int& newWordsCount, int& existingWordsCount,
    map<string, int>& dict, vector<string>& newWords){
    

    ifstream infile(filename);

    // �������� �������� �����
    if (!infile.is_open()) {
        cout << "failed!" << endl;
        return;
    }
    
    string word;
    while (infile >> word) {
		bool next = false;
        for (auto& i : FILENAMES)
            if (i == filename) {
				next = true;
                break;
            }
        
        if (next)
            break;


        word = cleanText(word);
        word = toLower(word);
        if (word.empty()) 
            continue;
        
        // ����� ����� � �������
        auto it = dict.find(word);

        // ���� ����� �� �������
        if (it == dict.end()) {
            // ���������� ����� � �������
            dict[word] = 1;
            newWords.push_back(word);
            newWordsCount++;
        }
        else {
            // ���������� �������� ������������� �����
            it->second++;
            existingWordsCount++;
        }
    }
	infile.close();
}