#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem> // для поиска в директории 


using namespace std;


#include "jsonWork.h"
#include "functions.h"

// почему без статика выдаёт ошибку, а с не выдаёт.
static map<string, int> colorCodes = { 
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
void setColorss(string color);
void resetColorss();