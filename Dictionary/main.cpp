#include "lib.h"

int main() {
	jsonStartup();

	DictionaryWork work("Text");

	cout << "Added new words: " << work.newWordsCount << endl;
	cout << "We found this words: " << work.existingWordsCount << endl;


	cout << "New words:" << endl;
	for (string word : work.newWords) {
		cout << word << "   ";
	}
	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;


	work.checkFileWord("check.txt");
	work.fixingMistakes("check.txt");

	jsonAll();
	cout << "Are you want to change some settings? Y/N " << endl;
	string user = "";
	cin >> user;
	if (toLower(user) == "y" || toLower(user) == "yes") {
		while (true)
		{
			cout << "Write a name of setting to change and to see value. Write \"exit\" for leave" << endl;
			cin >> user;
			if (user == "exit")
				break;

			if (jsonCheck(user) == true) {
				cout << "Are you want to change a value? Y/N" << endl;
				cin >> user;
				if (toLower(user) == "y" || toLower(user) == "yes")
				{

					string value;
					cin >> value;

					// Преобразование строки в число
					try {
						int intValue = stoi(value);
						//jsonChange(user, intValue);
					}
					catch (...) {}

					// Преобразование строки в число с плавающей точкой
					try {
						float floatValue = stof(value);
						//jsonChange(user, floatValue);
					}
					catch (...) {}

					// Преобразование строки в булево значение
					if (value == "true" || value == "false") {
						bool boolValue = (value == "true");
						//jsonChange(user, boolValue);
						// Используйте boolValue как булево значение
					}
					else {}
					//jsonChange(user, value);
				}
			}
		}
		jsonSave();
	}


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