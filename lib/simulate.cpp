#include "simulate.h"
#include <fstream>
#include <time.h>
#include <random>
#include <iostream>

sumulate::sumulate(int _K, int _T_max, int _T_min, int can_size,
	std::unordered_map<std::string, score*>::iterator *candidate, Alignment *ali)
{
	m_iK = _K;
	m_iTmax = _T_max;
	m_iTmin = _T_min;
	m_Pcandidates = candidate;
	m_cansize = can_size;
	m_Pali = ali;
}

sumulate::~sumulate()
{

}

void sumulate::start()
{
	std::cout << "begin iterate..." << std::endl;
	std::ofstream out("alignment_score.txt");
	double score = 0;
	
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, m_cansize - 1);
	int T0 = m_iTmax, Ti;
	double s = 0.005;
	int i = 1;
	while (i < m_iK)
	{
		int n = 0;
		Ti = T0 - i * (m_iTmax - m_iTmin) / m_iK;
		while (n < 2000)
		{
			int _random = distribution(generator);   //取一个随机数
			std::vector<std::string> pro = split("\t", m_Pcandidates[_random]->first);
			score += m_Pali->update(pro[0], pro[1], Ti, s);
			out << score << "\n";
			n++;
		}
		std::cout << "iterator" << i << ",alignment score :" << score << std::endl;
		i = i + 1;
	}
	std::cout << "iterator done..." << std::endl;
	std::cout << "writing alignment..." << std::endl;
	m_Pali->writeAlignment("result2.txt");
	std::cout << "all finish" << std::endl;
}