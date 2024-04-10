#include "functions.h"



// Преобразует строку в нижний регистр
string toLower(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


// Очищает текст от символов
string DictionaryWork::cleanText(string str) {
    string result;
    // Проверяем, не пустая ли строка и не превышает ли она максимальную длину
    if (str.empty() or str.length() >= 255)
        return result;

    for (char c : str)
        //Проверяем является ли символ буквой
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            result += c;


    return result;
}

// Конструктор, который загружает словарь, обрабатывает файлы в указанной директории,
// выполняет поиск в заданном файле и сохраняет обновленный словарь.
DictionaryWork::DictionaryWork(string path) : FILENAMES(get_checkedFiles()){
    this->loadDictionary("dictionary.txt");


    // Получение списка файлов
    files = getFiles(path);
    for (auto& name : files)
        this->workWithWords(name);

    this->saveDictionary("dictionary.txt");
}

// Сохраняет словарь и список файлов
void DictionaryWork::saveDictionary(string filename) {
    ofstream outfile(filename);

    if (!outfile.is_open()) {
        cout << "failed!" << endl;
        return;
    }

    for (auto& n : files)
        set_checkedFiles(n);
    


    for (auto it : this->dictionary)
        outfile << it.first << " " << it.second << endl;

    outfile.close();
}

// Загружает словарь
void DictionaryWork::loadDictionary(string filename) {
    ifstream infile(filename);
    if (!infile.is_open())
        return;

    string word;
    int count;

    while (infile >> word >> count)
        this->dictionary[word] = count;

    infile.close();

}

// Обрабатывает слова
void DictionaryWork::workWithWords(string& filename) {

    ifstream infile(filename);

    if (!infile.is_open()) {
        cout << "failed!" << endl;
        return;
    }
    // Проверяет был ли уже обработан этот файл
    for (auto& comp : FILENAMES)
    {
        if (comp == filename) {
			infile.close();
            return;
        }
    }


    string word;
    while (infile >> word) {

        word = cleanText(word);
        word = toLower(word);
        if (word.empty())
            continue;

        // Проверяем есть ли слово в словаре
        auto it = this->dictionary.find(word);

        // Если слово не найдено в словаре
        if (it == this->dictionary.end()) {
            
            this->dictionary[word] = 1;
            this->newWords.push_back(word);
            this->newWordsCount++;
        }
        else {
            // Если слово найдено в словаре
            it->second++;
            this->existingWordsCount++;
        }
    }
    infile.close();
}

// Получает список файлов в указанной директории
vector<string> DictionaryWork::getFiles(const string& path) {

    vector<string> files;
    if (isCheckFiles()) {
        return files;
    }

    // Итерируемся по всем элементам в этой директории.
    for (const auto& entry : filesystem::directory_iterator(path)) {
        files.push_back(entry.path().string());
    }
    return files;
}

// Выполняет поиск слов с ошибками
void DictionaryWork::checkFileWord(const string& fileCheck) {

    if(isProblemWords())
		return;

    ifstream infile(fileCheck);
    stringstream buffer;
    if (!infile.is_open()) {
        cout << "Unable to open file: " << fileCheck << endl;
        return;
    }

    buffer << infile.rdbuf(); // Чтение содержимого файла в буфер stringstream
    infile.close();
    string file_contents =
        buffer.str(); // Получение содержимого буфера stringstream в виде строки

    int isIncorrect = 0;
    string word;
    string red_color = "\x1B[31m";
    string reset_color = "\x1B[0m";

    cout << "File contents:\n";
    istringstream iss(file_contents);
    while (iss >> word) {
        string cleaned_word;
        for (char c : word) {
            if (isalpha(c)) {
                cleaned_word += tolower(c); // Приводим к нижнему регистру
            }
        }

        if (dictionary.find(cleaned_word) == dictionary.end()) {
            isIncorrect++;
            // Слова нет в словаре, выводим его красным цветом
            cout << red_color << word << reset_color << " ";
        }
        else {
            cout << word << " ";
        }

    }
    cout << "-----------------------------------------------" << endl;
    cout << "Number of incorect words: " << isIncorrect << endl;
}

bool DictionaryWork::isMistakes(const std::string& word1, const std::string& word2, size_t index1,
                                 size_t index2, int mistake) {
    if (mistake > 1)
        return false;

    if (containsDigit(word1)) 
        return false; // Не изменять слово, если содержит цифры
    
    if (index1 == word1.size() && index2 == word2.size()) {
        return mistake == 1;
    }

    if (index1 == word1.size() || index2 == word2.size()) {
        return mistake + std::abs((int)word1.size() - (int)word2.size()) == 1;
    }

    if (word1[index1] == word2[index2]) {
        return isMistakes(word1, word2, index1 + 1, index2 + 1, mistake);
    } else {
        return isMistakes(word1, word2, index1 + 1, index2, mistake + 1) ||
               isMistakes(word1, word2, index1, index2 + 1, mistake + 1) ||
               isMistakes(word1, word2, index1 + 1, index2 + 1, mistake + 1);
    }
}

bool DictionaryWork::containsDigit(const string& str) {
    return any_of(str.begin(), str.end(), ::isdigit);
}
void DictionaryWork::fixingMistakes(const string& fileCheck) {
    ifstream inputFile(fileCheck);
    if (!inputFile.is_open()) {
        return;
    }
    string outputFileName =
        fileCheck.substr(0, fileCheck.find_last_of(".")) + "_fixed.txt";
    ofstream outputFile(outputFileName); // Открытие нового файла для записи

    if (!outputFile.is_open()) {
        return;
    }

    string line;
    while (getline(inputFile, line)) { // Чтобы файл в результате выдал почти такой же какой и получил
        string word;
        istringstream iss(line);
        while (iss >> word) { // поиск ошибок
            bool corrected = false;
            word = toLower(word);

            if (dictionary.find(word) != dictionary.end()) {
                outputFile << word << " ";
                corrected = true;
            }
            else {
                for (const auto& dictWord : dictionary) {
                    if (isMistakes(word, dictWord.first, 0, 0, 0)) {
                        outputFile << dictWord.first << " ";
                        corrected = true;
                        break;
                    }
                }
            }

            if (!corrected) {
                outputFile << word << " ";
            }
        }
        outputFile << endl; // переход на новою строку
    }
    inputFile.close();
    outputFile.close();
}