#include "lib.h"

int main() {
    jsonStartup();

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

	vector<string> files = get_checkedFiles();
    for (auto& i : files)
    {
        cout << i << endl;
    }
	cout << get_CountFiles() << endl;

    jsonChange();
    return 0;
}

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