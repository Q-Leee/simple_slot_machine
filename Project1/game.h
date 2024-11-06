#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

class game
{
	vector<vector<string>> table;

public:
	game();
	void start();
	void instruction();
	void startGame();
	void simulation();
};

