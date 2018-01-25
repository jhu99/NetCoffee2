#include "ProteinRel.h"

std::string str_add(std::string str1, std::string str2)
{
	if (str1 < str2)
	{
		return str1 + "\t" + str2;
	}
	else
	{
		return str2 + "\t" + str1;
	}
}

double distance(double* pro1, double* pro2)
{
	double res = 0;
	for (int i = 0; i < 5; i++)
	{
		res += (pro1[i] - pro2[i]) * (pro1[i] - pro2[i]);
	}
	return sqrt(res);
}

double distance_Gaussian(double* pro1, double* pro2)
{
	double res = 0;
	for(int i = 0; i < 5; i++)
	{
		res += (pro1[i] - pro2[i]) * (pro1[i] - pro2[i]);
	}
	res = exp(-(res * res) / 2);
	return res;
}
//define the function to splite a string by "\t"
std::vector<std::string> split(std::string pattern, std::string str)
{
	size_t pos;
	std::vector<std::string> result;
	str = str + pattern;
	int size = str.size();

	for (int i = 0; i < size; i++){
		pos = str.find(pattern, i);
		if (pos < size){
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}

	return result;
}
