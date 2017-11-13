#include "ReadBitscore.h"
#include <fstream>
#include <iostream>
#include <cmath>

std::string str_add(std::string str1, std::string str2)
{
	if (str1 < str2)
	{
		return str1 + str2;
	}
	else
	{
		return str2 + str1;
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

ReadBitscore::ReadBitscore(std::string filename, ReadPPI &network)
{
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
			double top = distance(network.top_vec[temp[0]], network.top_vec[temp[1]]);
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
	}
}

ReadBitscore::~ReadBitscore()
{
}

double ReadBitscore::getScore(std::string pro1, std::string pro2)
{
	double alph = 0.5;
	std::string temp = str_add(pro1, pro2);
	double bit = protein_score[temp]->bitscore;
	double top = protein_score[temp]->topscore;
	return (bit - m_dMinBitsc) / (m_dMaxBitsc - m_dMinBitsc) * alph + top * (1 - alph);
}