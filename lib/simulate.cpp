#include "simulate.h"
#include <fstream>
#include <time.h>
#include <iostream>

sumulate::sumulate(int _K, int _T_max, int _T_min, int can_size,
	std::string* candidate, Alignment *ali)
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
	float score = 0;
	
	int T0 = m_iTmax, Ti;
	float s = 0.005;
	int i = 1;
	srand(time(NULL));
	while (i < m_iK)
	{
		int n = 0;
		Ti = T0 - i * (m_iTmax - m_iTmin) / m_iK;
		while (n < 20)
		{
			clock_t start = clock();

			std::string p1, p2;
			int _random = rand() % (m_cansize * 2 - 1);   //取一个随机数
			if (_random % 2 == 0)
			{
				p1 = m_Pcandidates[_random];
				p2 = m_Pcandidates[_random + 1];
			}
			else
			{
				p1 = m_Pcandidates[_random - 1];
				p2 = m_Pcandidates[_random];
			}

			score += m_Pali->update(p1, p2, Ti, s);
			out << score << "\n";
			n++;
		}
		std::cout << "iterator" << i << ",alignment score :" << score << std::endl;
		i = i + 1;
	}
	std::cout << "iterator done..." << std::endl;
	std::cout << "writing alignment..." << std::endl;
	m_Pali->writeAlignment("result1.txt");
	std::cout << "all finish" << std::endl;
}