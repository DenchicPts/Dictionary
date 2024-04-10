#include "jsonWork.h"

nlohmann::json objJson;

void jsonStartup() {
	fstream fileInput;
	fileInput.open("main_config.json");
	fileInput >> setw(4) >> objJson;
	fileInput.close();
}
void jsonDefaultSave() {
	ofstream fileInput;
	fileInput.open("main_config.json");
	fileInput << setw(4) << objJson;
	fileInput.close();
}

void jsonSave() {
	ofstream fileInput;
	fileInput.open("new_main_config.json");
	fileInput << setw(4) << objJson;
	fileInput.close();
}



vector<string> get_checkedFiles() {
	return objJson["checkedFiles"];
}

int get_CountFiles() {
	return objJson["size"];
}

bool isCheckFiles() {
	return objJson["checkFiles"];
}
bool isProblemWords() {
	return objJson["problemWords"];
}

void jsonAll() {
	cout << setw(4) << objJson << endl;
}

bool jsonCheck(const string& setting) {
	try
	{
		cout << setting << ": " << objJson[setting] << endl;
		return true;
	}
	catch (const exception&)
	{
		printf("Error this %s doesn't match\n", setting);
		return false;
	}
}

template<typename dataType>
void jsonChange(const string& setting,  dataType data) {
	try
	{
		objJson[setting] = data;
		cout << "JSON changed: " << objJson[setting] << endl;
	}
	catch (const std::exception&)
	{
		printf("Error: invalid data type");
	}
}

void set_checkedFiles(string& fileName) {
	auto it = find(objJson["checkedFiles"].begin(), objJson["checkedFiles"].end(), fileName);
	if (it == objJson["checkedFiles"].end()) {
		objJson["checkedFiles"].push_back(fileName);
		objJson["size"] = get_CountFiles() + 1;
	}
}