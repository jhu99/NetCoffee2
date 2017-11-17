#include "Alignment.h"
#include <fstream>
#include <string>
#include <iostream>
#include <time.h>


std::string str_add(std::string str1, std::string str2);

Alignment::Alignment(std::unordered_map<std::string, std::string> &net_pro,
	std::unordered_map<std::string, double> &can_weight, double mean)
{
	m_dMean = mean;
	m_unmNetPro = net_pro;
	m_unmWeight = can_weight;
	srand(time(NULL));
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
			if (m_unmWeight.find(str_add((*match)[i],(*match)[j])) != m_unmWeight.end())
				res += m_unmWeight[str_add((*match)[i], (*match)[j])];
		}
	}
	/*std::vector<std::string>::iterator it1, it2;
	for (it1 = match->begin(); it1 != match->end(); it1++)
	{
		for (it2 = ++it1; it2 != match->end(); it2++)
		{
			if (m_unmWeight.find(str_add(*it1, *it2)) != m_unmWeight.end())
				res += m_unmWeight[str_add(*it1, *it2)];
		}
	}*/
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
	if (m_unmA.find(pro1) == m_unmA.end() && m_unmA.find(pro2) == m_unmA.end())
	{
		return 1;
	}
	if (m_unmA.find(pro1) != m_unmA.end() && m_unmA.find(pro2) == m_unmA.end())
	{
		return 2;
	}
	if (m_unmA.find(pro1) == m_unmA.end() && m_unmA.find(pro2) != m_unmA.end())
	{
		return 3;
	}
	if (m_unmA.find(pro1) != m_unmA.end() && m_unmA.find(pro2) != m_unmA.end())
	{
		return 4;
	}
	return 5;
}

double Alignment::update(std::string pro1, std::string pro2, int T_i, float m_ds)
{
	double before = 0, after = 0;
	int sce = scenarios(pro1, pro2);
	if (sce == 1)
	{
		std::vector<std::string>* temp = new std::vector<std::string>{ pro1, pro2 };
		alignmrnt.push_back(temp);
		m_unmA[pro1] = temp;
		m_unmA[pro2] = temp;
		after = getMatchScore(temp);
		return after - before;
	}
	else if (sce == 2)
	{
		before = getMatchScore(m_unmA[pro1]);
		std::vector<std::string> temp = *m_unmA[pro1];
		int jud = judge(pro1, pro2);
		if ( jud == -1)
		{
			m_unmA[pro1]->push_back(pro2);
			m_unmA[pro2] = m_unmA[pro1];
			return getMatchScore(m_unmA[pro1]) - before;
		}
		else
		{
			std::string sub = temp[jud];
			temp[jud] = pro2;
			if (doit(getMatchScore(&temp) - before > 0, T_i, m_ds))
			{
				(*m_unmA[pro1])[jud] = pro2;
				m_unmA[pro2] = m_unmA[pro1];
				m_unmA.erase(sub);
				return getMatchScore(&temp) - before;
			}
			return 0;
		}
	}
	else if (sce == 3)
	{
		before = getMatchScore(m_unmA[pro2]);
		std::vector<std::string> temp = *m_unmA[pro2];
		int jud = judge(pro2, pro1);
		if (jud == -1)
		{
			m_unmA[pro2]->push_back(pro1);
			m_unmA[pro1] = m_unmA[pro2];
			return getMatchScore(m_unmA[pro2]) - before;
		}
		else
		{
			std::string sub = temp[jud];
			temp[jud] = pro1;
			if (doit(getMatchScore(&temp) - before > 0, T_i, m_ds))
			{
				(*m_unmA[pro2])[jud] = pro1;
				m_unmA[pro1] = m_unmA[pro2];
				m_unmA.erase(sub);
				return getMatchScore(&temp) - before;
			}
			return 0;
		}
	}
	else if (sce == 4)
	{
		double before1 = getMatchScore(m_unmA[pro1]), after1;
		double before2 = getMatchScore(m_unmA[pro2]), after2;
		std::vector<std::string> temp1 = *m_unmA[pro1];
		std::vector<std::string> temp2 = *m_unmA[pro2];
		int jud1 = judge(pro1, pro2);
		int jud2 = judge(pro2, pro1);
		if (jud1 == -1)
		{
			temp1.push_back(pro2);
			after1 = getMatchScore(&temp1) - before1;
		}
		else
		{
			std::string sub = temp1[jud1];
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
			std::string sub = temp2[jud2];
			temp2[jud2] = pro1;
			after2 = getMatchScore(&temp2) - before2;
		}

		if (after1 >= after2)
		{
			if (doit(after1 - before1 - before2 > 0, T_i, m_ds))
			{
				double dat = after1 - before1;
				if (doit(dat, T_i, m_ds))
				{
					if (jud1 == -1)
					{
						m_unmA[pro1]->push_back(pro2);
						alignmrnt.remove(m_unmA[pro2]);
						for (auto i : *m_unmA[pro2])
						{
							m_unmA.erase(i);
						}
						delete m_unmA[pro2];
						m_unmA[pro2] = m_unmA[pro1];
					}
					else
					{
						std::string sub = (*m_unmA[pro1])[jud1];
						(*m_unmA[pro1])[jud1] = pro2;
						alignmrnt.remove(m_unmA[pro2]);
						for (auto i : *m_unmA[pro2])
						{
							m_unmA.erase(i);
						}
						delete m_unmA[pro2];
						m_unmA[pro2] = m_unmA[pro1];
						m_unmA.erase(sub);
					}
					return after1 - before1 - before2;
				}
				return 0;
			}
			
		}
		else
		{
			if (doit(after2 - before1 - before2 > 0, T_i, m_ds))
			{
				double dat = after2 - before2;
				if (doit(dat, T_i, m_ds))
				{
					if (jud2 == -1)
					{
						m_unmA[pro2]->push_back(pro1);
						alignmrnt.remove(m_unmA[pro1]);
						for (auto i : *m_unmA[pro1])
						{
							m_unmA.erase(i);
						}
						delete m_unmA[pro1];
						m_unmA[pro1] = m_unmA[pro2];
					}
					else
					{
						std::string sub = (*m_unmA[pro2])[jud2];
						(*m_unmA[pro2])[jud1] = pro1;
						alignmrnt.remove(m_unmA[pro1]);
						for (auto i : *m_unmA[pro1])
						{
							m_unmA.erase(i);
						}
						delete m_unmA[pro1];
						m_unmA[pro1] = m_unmA[pro2];
						m_unmA.erase(sub);
					}
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
	for (auto i : *m_unmA[pro1])
	{
		if (m_unmNetPro[i] == m_unmNetPro[pro2])
		{
			if (m_unmWeight[str_add(i, pro2)] > m_dMean)
			{
				return -1;
			}
			return cnt;
		}
		cnt++;
	}
	return -1;
}

bool Alignment::doit(float _dat, int T_i, float m_ds)
{
	if (_dat > 0)
	{
		return true;
	}
	else if (_dat == 0)
	{
		return false;
	}
	else if ((rand() % 100 / (double)101) < exp(_dat / (T_i * m_ds)))
	{
		return true;
	}
	return false;
}