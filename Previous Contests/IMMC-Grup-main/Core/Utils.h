#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>  

enum TipCelula
{
	NUMBER,
	TEXT
};

using namespace std;

constexpr size_t COMPARE_PRECISION = 4;

void ltrim(std::string &s);

string toLowerCase(string s);
string getCurrentDateAndTime();

bool is_number(const std::string& s);

bool areNumbersEqual(double n, double n2, size_t precision = COMPARE_PRECISION);

#include "Exception.h"