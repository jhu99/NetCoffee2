#include "ReadBitscore.h"
#include <fstream>
#include <iostream>


ReadBitscore::ReadBitscore(std::string filename, 
	std::unordered_map<std::string, double* > &top_vec, double alph)
{
	m_dAlph = alph;
	m_dMaxBitsc = 0;
	m_dMinBitsc = 1000;
	std::ifstream in(filename);
	if (!in){
		std::cout << "can't open bip net..." << std::endl;
	}//read bitscore from file
	std::string temp[3];
	std::cout << "reading bip network..." << std::endl;
	while (in >> temp[0] && in >> temp[1] && in >> temp[2])
	{
		double value = atof(temp[2].c_str());
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

void ReadBitscore::colected_candidates(double beta,
	std::unordered_map<std::string, score*>::iterator *candidate)
{
	std::cout << "begin select candidates..." << std::endl;
	double res = 0;
	double max = 0, min = 10000;
	int cnt = 0;
	std::unordered_map<std::string, score*>::iterator it;
	for (it = protein_score.begin(); it != protein_score.end(); it++)
	{
		candidate[cnt] = it;
		cnt++;
		double bit = it->second->bitscore;
		double top = it->second->topscore;
		double fin = (bit - m_dMinBitsc) / (m_dMaxBitsc - m_dMinBitsc) * m_dAlph
			+ top * (1 - m_dAlph);
		it->second->finalscore = fin;
		res += fin;
		if (fin > max)
			max = fin;
		if (fin < min)
			min = fin;
	}
	
	//contral the density of conserved proteins from one PPI network
	//beta from 0.5 to 1, 1 means that no candidates of conserved proteins from one PPI network
	if (beta <= 1 && beta >= 0)
	{
		m_dMeanf = beta * max;
	}
	else
	{
		m_dMeanf = res / protein_score.size();
	}
	std::cout << "select finish!" << std::endl;
	std::cout << "mean of final score: " << res / protein_score.size() << std::endl;
}

