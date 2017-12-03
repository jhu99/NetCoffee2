#include "simulate.h"
#include <fstream>
#include <ctime>
#include <random>
#include <iostream>

sumulate::sumulate(int _K, int _T_max, int _T_min, int can_size,
	std::unordered_map<std::string, score*>::iterator *candidate, Alignment *ali, std::string output)
{
	m_iK = _K;
	m_iTmax = _T_max;
	m_iTmin = _T_min;
	m_Pcandidates = candidate;
	m_cansize = can_size;
	m_Pali = ali;
	m_Soutput = output;

}

sumulate::~sumulate()
{

}

void sumulate::start(std::ofstream &out)
{
	std::cout << "# begin iterate..." << std::endl;
	double score = 0;
	
	std::default_random_engine generator(time(NULL));
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
			int _random = distribution(generator);   //get a random number
			std::vector<std::string> pro = split("\t", m_Pcandidates[_random]->first);
			score += m_Pali->update(pro[0], pro[1], Ti, s);
			out << score << "\n";
			n++;
		}
		std::cout << "# iterator" << i << ",alignment score :" << score << std::endl;
		i = i + 1;
	}
	std::cout << "# iterator done..." << std::endl;
	std::cout << "# writing alignment..." << std::endl;
	m_Pali->writeAlignment(m_Soutput);
	std::cout << "# all finish" << std::endl;
}