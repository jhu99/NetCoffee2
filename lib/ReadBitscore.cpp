#include "ReadBitscore.h"
#include <fstream>
#include <iostream>
#include <cmath>

std::vector<std::string> split(std::string pattern, std::string str);

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
	return 1/ (1 + sqrt(res));
}

ReadBitscore::ReadBitscore(std::string filename, 
	std::unordered_map<std::string, double* > &top_vec, double alph)
{
	m_dAlph = alph;
	m_dMaxBitsc = 0;
	m_dMinBitsc = 1000;
	std::ifstream in(filename);
	if (!in){
		std::cout << "can't open bip net..." << std::endl;
	}//从文本中读取网络
	std::string temp[3];
	std::cout << "reading bip network..." << std::endl;
	while (in >> temp[0] && in >> temp[1] && in >> temp[2])
	{
		double value = atof(temp[2].c_str());//将string类型转化成double类型
		if (temp[0] != temp[1])
		{
			std::string str_pro = str_add(temp[0], temp[1]);
			double top = distance(top_vec[temp[0]], top_vec[temp[1]]);
			score* scr = new score;
			scr->bitscore = value;
			scr->topscore = top;
			protein_score[str_pro] = scr;

			if (value > m_dMaxBitsc)
			{
				m_dMaxBitsc = value;
			}
			if (value < m_dMinBitsc)
			{
				m_dMinBitsc = value;
			}
		}
		can_size = protein_score.size();
	}
	std::cout << "read done..." << std::endl;
}

ReadBitscore::~ReadBitscore()
{
}

void ReadBitscore::colected_candidates(std::string* candidates)
{
	std::cout << "begin select candidates..." << std::endl;
	double res = 0;
	int cnt = 0;
	std::unordered_map<std::string, score*>::iterator it;
	for (it = protein_score.begin(); it != protein_score.end(); it++)
	{
		std::vector<std::string> temp = split("\t", it->first);
		candidates[cnt] = temp[0];
		candidates[cnt + 1] = temp[1];
		cnt += 2;

		double bit = it->second->bitscore;
		double top = it->second->topscore;
		double fin = (bit - m_dMinBitsc) / (m_dMaxBitsc - m_dMinBitsc) * m_dAlph
			+ top * (1 - m_dAlph);
		it->second->finalscore = fin;
		can_weight[it->first] = fin;
		res += fin;
	}
	m_dMeanf = res / protein_score.size();
	std::cout << "select finish!" << std::endl;
	std::cout << "mean of final score: " << res / protein_score.size() << std::endl;
}

std::vector<std::string> split(std::string pattern, std::string str) //定义分割字符串的函数
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