#include "lib.h"

map<string, int> colorCodes = {
  {"Dark red", 31},
  {"Dark green", 32},
  {"Dark yellow", 33},
  {"Dark blue", 34},
  {"Dark magenta", 35},
  {"Dark cyan", 36},
  {"Dark white", 37},
  {"Light red", 90},
  {"Light green", 92},
  {"Light yellow", 93},
  {"Light blue", 94},
  {"Light magenta", 95},
  {"Light cyan", 96},
  {"Light white", 97},
};

// Устанавливает цвет текста.
void setColorss(string color) {
    if (colorCodes.find(color) != colorCodes.end())
        cout << "\x1b[30m";
    cout << "\x1b[" << colorCodes[color] << "m";
}

// Делает текст по умолчанию.
void resetColorss() {
    cout << "\x1b[0m";
}

int main() {
    DictionaryWork work("Text", "check.txt");

    cout << "Added new words: " << work.newWordsCount << endl;
    cout << "We found this words: " << work.existingWordsCount << endl;


    cout << "New words:" << endl;
    for (string word : work.newWords) {
        cout << word << "   ";
    }


    cout << "_____________________________________" << endl;
    cout << "_____________________________________" << endl;
    cout << "_____________________________________" << endl;
    setColorss("Dark red");
    for (const auto& word : work.missingWords) {

        cout << word << '\t';
    }
    resetColorss();
    cout << endl << "Number of words with error " << work.Errors << endl;

    return 0;
}




