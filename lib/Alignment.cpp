#include "Alignment.h"
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include "ProteinRel.h"


Alignment::Alignment(std::unordered_map<std::string, int>* net_pro,
	std::unordered_map<std::string, score*>* can_weight, double mean)
{
	m_dMean = mean;
	m_unmNetPro = net_pro;
	m_unmWeight = can_weight;
}

Alignment::~Alignment()
{
	std::list<std::vector<std::string>*>::iterator it;
	for (it = alignmrnt.begin(); it != alignmrnt.end(); it++)
	{
		delete *it;
		*it = NULL;
	}
}

double Alignment::getMatchScore(std::vector<std::string>* match)
{
	double res = 0;
	int size = match->size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (m_unmWeight->find(str_add((*match)[i],(*match)[j])) != m_unmWeight->end())
				res += (*m_unmWeight)[str_add((*match)[i], (*match)[j])]->finalscore;
		}
	}
	return res;
}

void Alignment::writeAlignment(std::string output)
{
	std::ofstream os(output);
	if (!os)
	{
		std::cout << "can open output file..." << std::endl;
	}
	std::list<std::vector<std::string>*>::iterator it;
	for (it = alignmrnt.begin(); it != alignmrnt.end(); it++)
	{
		for (auto i : **it)
		{
			os << i << "\t";
		}
		os << "\n";
	}

}
int Alignment::scenarios(std::string pro1, std::string pro2)
{
	std::unordered_map<std::string, std::vector<std::string>*>::iterator it;
	if (m_unmA.count(pro1) == 0 && m_unmA.count(pro2) == 0)
	{
		return 1;
	}
	if (m_unmA.count(pro1) > 0 && m_unmA.count(pro2) == 0)
	{
		return 2;
	}
	if (m_unmA.count(pro1) == 0 && m_unmA.count(pro2) > 0)
	{
		return 3;
	}
	if (m_unmA.count(pro1) > 0 && m_unmA.count(pro2) > 0)
	{
		return 4;
	}
	return 5;
}

double Alignment::update(std::string pro1, std::string pro2, int T_i, float m_ds)
{
	if (pro2 == "Q9SX31")
	{
		int j = 0;
	}
	std::list<std::vector<std::string>* >::iterator ite;
	double before = 0, after = 0;
	int sce = scenarios(pro1, pro2);
	if (sce == 1)
	{
		if ((*m_unmNetPro)[pro1] == (*m_unmNetPro)[pro2])
		{
			if ((*m_unmWeight)[str_add(pro1, pro2)]->finalscore > m_dMean)
			{
				std::vector<std::string>* temp = new std::vector<std::string>{ pro1, pro2 };
				alignmrnt.push_back(temp);
				ite = alignmrnt.end();
				ite--;
				m_unmA[pro1] = ite;
				m_unmA[pro2] = ite;
				after = getMatchScore(temp);
			}
			return after - before;
		}
		else
		{
			std::vector<std::string>* temp = new std::vector<std::string>{ pro1, pro2 };
			alignmrnt.push_back(temp);
			ite = alignmrnt.end();
			ite--;
			m_unmA[pro1] = ite;
			m_unmA[pro2] = ite;
			after = getMatchScore(temp);
			return after - before;
		}
	}
	else if (sce == 2)
	{
		before = getMatchScore(*m_unmA[pro1]);
		std::vector<std::string> temp = **m_unmA[pro1];
		int jud = judge(pro1, pro2);
		if ( jud == -1)
		{
			(*m_unmA[pro1])->push_back(pro2);
			m_unmA[pro2] = m_unmA[pro1];
			return getMatchScore(*m_unmA[pro1]) - before;
		}
		else
		{
			std::list<std::vector<std::string>* >::iterator it_temp = m_unmA[pro1];
			std::string sub = temp[jud];
			temp[jud] = pro2;
			if (doit(getMatchScore(&temp) - before > 0, T_i, m_ds))
			{
				(**it_temp)[jud] = pro2;
				m_unmA[pro2] = it_temp;
				m_unmA.erase(sub);
				return getMatchScore(&temp) - before;
			}
			return 0;
		}
	}
	else if (sce == 3)
	{
		before = getMatchScore(*m_unmA[pro2]);
		std::vector<std::string> temp = **m_unmA[pro2];
		int jud = judge(pro2, pro1);
		if (jud == -1)
		{
			(*m_unmA[pro2])->push_back(pro1);
			m_unmA[pro1] = m_unmA[pro2];
			return getMatchScore(*m_unmA[pro2]) - before;
		}
		else
		{
			std::list<std::vector<std::string>* >::iterator it_temp = m_unmA[pro2];
			std::string sub = temp[jud];
			temp[jud] = pro1;
			if (doit(getMatchScore(&temp) - before > 0, T_i, m_ds))
			{
				(**it_temp)[jud] = pro1;
				m_unmA[pro1] = it_temp;
				m_unmA.erase(sub);
				return getMatchScore(&temp) - before;
			}
			return 0;
		}
	}
	else if (sce == 4)
	{
		std::list<std::vector<std::string>* >::iterator it_temp1 = m_unmA[pro1];
		std::list<std::vector<std::string>* >::iterator it_temp2 = m_unmA[pro2];
		double before1 = getMatchScore(*m_unmA[pro1]), after1;
		double before2 = getMatchScore(*m_unmA[pro2]), after2;
		std::vector<std::string> temp1 = **m_unmA[pro1];
		std::vector<std::string> temp2 = **m_unmA[pro2];
		int jud1 = judge(pro1, pro2);
		int jud2 = judge(pro2, pro1);
		if (jud1 == -1)
		{
			temp1.push_back(pro2);
			after1 = getMatchScore(&temp1) - before1;
		}
		else
		{
			temp1[jud1] = pro2;
			after1 = getMatchScore(&temp1) - before1;
		}

		if (jud2 == -1)
		{
			temp2.push_back(pro1);
			after2 = getMatchScore(&temp2) - before2;
		}
		else
		{
			temp2[jud2] = pro1;
			after2 = getMatchScore(&temp2) - before2;
		}

		if (after1 >= after2)
		{
			if (doit(after1 - before1 - before2 > 0, T_i, m_ds))
			{
				if (jud1 == -1)
				{
					(*it_temp1)->push_back(pro2);
					for (auto i : **it_temp2)
					{
						m_unmA.erase(i);
					}
					delete *it_temp2;
					alignmrnt.erase(it_temp2);
					m_unmA[pro2] = it_temp1;
				}
				else
				{
					std::string sub = (**it_temp1)[jud1];
					(**it_temp1)[jud1] = pro2;
					for (auto i : **it_temp2)
					{
						m_unmA.erase(i);
					}
					delete *it_temp2;
					alignmrnt.erase(it_temp2);
					m_unmA[pro2] = it_temp1;
					m_unmA.erase(sub);
				}
				return after1 - before1 - before2;	
			}
			return 0;
		}
		else
		{
			if (doit(after2 - before1 - before2 > 0, T_i, m_ds))
			{
				if (jud2 == -1)
				{
					(*it_temp2)->push_back(pro1);

					for (auto i : **it_temp1)
					{
						m_unmA.erase(i);
					}
					delete *it_temp1;
					alignmrnt.erase(it_temp1);
					m_unmA[pro1] = it_temp2;
				}
				else
				{
					std::string sub = (**it_temp2)[jud2];
					(**it_temp2)[jud2] = pro1;
					for (auto i : **it_temp1)
					{
						m_unmA.erase(i);
					}
					delete *it_temp1;
					alignmrnt.erase(it_temp1);
					m_unmA[pro1] = it_temp2;
					m_unmA.erase(sub);
				}
				return after2 - before1 - before2;
			}
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int Alignment::judge(std::string pro1, std::string pro2)
{
	int cnt = 0;
	for (auto i : **m_unmA[pro1])
	{
		if ((*m_unmNetPro)[i] == (*m_unmNetPro)[pro2])
		{
			if (m_unmA.count(str_add(i, pro2)) > 0)
			{
				if ((*m_unmWeight)[str_add(i, pro2)]->finalscore > m_dMean)
				{
					return -1;
				}
			}
			return cnt;
		}
		cnt++;
	}
	return -1;
}

bool Alignment::doit(float _dat, int T_i, float m_ds)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 100);

	if (_dat > 0)
	{
		return true;
	}
	else if (_dat == 0)
	{
		return false;
	}
	else if ((distribution(generator) / (double)101) < exp(_dat / (T_i * m_ds)))
	{
		return true;
	}
	return false;
}