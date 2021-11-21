#pragma once
using namespace std;
#include "Hill.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <random>
#include <vector>
#include <ctime>
#include <map>
#include <stdlib.h>
#include <list>
#include <locale.h>

int randomInt(int, int);
double randomDouble(double, double);
void colorText(unsigned short color, string text);
double percent(double prc, double num);
double normalRandom(double mid, double a);
void binomalRandom(int up, int chance);
//-----------------------------//
void loadHills();
void loadJumpers(bool ifForm);
//void loadTrainingConfig();
void selectTrainingHill();
void selectTrainingJumper();
void showHillInfo(Hill hl);
void showJumpers();
void defaultClearFile(string file);

#define APP_VERSION "0.3.2"
#define cls system("cls")
#define hillsfile hlf
#define jumpersfile jpf
#define configfile cf
#define nationsfile ntf
#define resultsfile rsf