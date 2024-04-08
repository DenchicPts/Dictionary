#include "jsonWork.h"

nlohmann::json objJson;

void jsonStartup() {
	fstream fileInput;
	fileInput.open("main_config.json");
	fileInput >> setw(4) >> objJson;
	fileInput.close();
}
void jsonChange() {
	ofstream fileInput;
	fileInput.open("main_config.json");
	fileInput << setw(4) << objJson;
	fileInput.close();
}

vector<string> get_checkedFiles() {
	return objJson["checkedFiles"];
}

int get_CountFiles() {
	return objJson["size"];
}

void set_checkedFiles(string& fileName) {
	auto it = find(objJson["checkedFiles"].begin(), objJson["checkedFiles"].end(), fileName);
	if (it == objJson["checkedFiles"].end()) {
		objJson["checkedFiles"].push_back(fileName);
		objJson["size"] = get_CountFiles() + 1;
	}
}