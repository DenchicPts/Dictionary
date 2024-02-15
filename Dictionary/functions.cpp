#include "lib.h"

vector<string> FILENAMES;

// Функция для преобразования слова в нижний регистр
string toLower(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


// Функция для очистки текста от знаков препинания
string cleanText(string str) {
    string result;
    if (str.empty() or str.length() >= 255)
        return result;
    for (char c : str)
        //isalnum(c) если большое количество символов возможно будет ошибка
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            result += c;


    return result;
}

// Функция для сохранения словаря в файл .txt
void saveDictionary(string filename, map<string, int>& dict, vector<string> names) {
    ofstream outfile(filename);

    if (!outfile.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
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

// Функция для загрузки словаря из файла .txt
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

    // Проверка открытия файла
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
        
        // Поиск слова в словаре
        auto it = dict.find(word);

        // Если слово не найдено
        if (it == dict.end()) {
            // Добавление слова в словарь
            dict[word] = 1;
            newWords.push_back(word);
            newWordsCount++;
        }
        else {
            // Увеличение счетчика существующего слова
            it->second++;
            existingWordsCount++;
        }
    }
	infile.close();
}