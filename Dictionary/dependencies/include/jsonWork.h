#pragma once
#include "lib.h"
#include "nlohmann/json.hpp"

void jsonStartup();
void jsonDefaultSave();
void jsonSave();
vector<string> get_checkedFiles();
int get_CountFiles();
void set_checkedFiles(string& fileName);

bool isCheckFiles();
bool isProblemWords();

void jsonAll();
bool jsonCheck(const string& setting);

//template<typename dataType>
//void jsonChange(const string& setting, dataType data);
