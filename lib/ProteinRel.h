#include <string>
#include <cmath>
#include <vector>
#pragma once

struct score
{
	double bitscore;
	double topscore;
	double finalscore;
};

std::string str_add(std::string str1, std::string str2);

double distance(double* pro1, double* pro2);

std::vector<std::string> split(std::string pattern, std::string str);