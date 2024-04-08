#pragma once
#include "lib.h"
#include "nlohmann/json.hpp"

void jsonStartup();
void jsonChange();
vector<string> get_checkedFiles();
int get_CountFiles();
void set_checkedFiles(string& fileName);
