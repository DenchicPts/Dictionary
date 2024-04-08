#include "functions.h"



// Преобразует строку в нижний регистр
string DictionaryWork::toLower(string& str) {
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
DictionaryWork::DictionaryWork(string path, string checkFile) {

    this->loadDictionary("dictionary.txt");

    // Получение списка файлов
    files = getFiles(path);
    for (auto& name : files)
        this->workWithWords(name);

    fileSearch(checkFile);


    this->saveDictionary("dictionary.txt");
}

// Сохраняет словарь и список файлов
void DictionaryWork::saveDictionary(string filename) {
    ofstream outfile(filename);

    if (!outfile.is_open()) {
        cout << "failed!" << endl;
        return;
    }
    outfile << files.size() << endl;
    for (auto& n : files)
    {
        outfile << n << endl;
    }


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

    if (!getline(infile, word))
        return;



 
    int i = stoi(word);
    // Читаем имена файлов из следующих строк и добавляем их в список FILENAMES
    for (; i > 0; i--) {
        getline(infile, word);
        this->FILENAMES.push_back(word);
    }


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

    string word;
    while (infile >> word) {
        bool next = false;
        // Проверяем является ли текущий файл одним из файлов обработанных ранее
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
    // Итерируемся по всем элементам в этой директории.
    for (const auto& entry : filesystem::directory_iterator(path)) {
        files.push_back(entry.path().string());
    }
    return files;
}

// Выполняет поиск слов
void DictionaryWork::fileSearch(const string& path) {
    ifstream file(path);


    if (!file.is_open()) {
        cout << "failed!" << endl;
        return;
    }

    string word;
    while (file >> word) {
        word = cleanText(word);
        word = toLower(word);
        if (word.empty())
            continue;
        // Проверяет есть ли слово в словаре.
        if (dictionary.find(word) == dictionary.end() && 
            find(missingWords.begin(), missingWords.end(), word) == missingWords.end()) {
            //Увеличиваем счётчик ошибок и добавляем в вектор неправильное слово
            Errors++;
            missingWords.push_back(word);
        }


    }
    file.close();
}