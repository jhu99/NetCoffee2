#ifndef Alignment_h
#define Alignemnt_h

#include "ProteinRel.h"
#include <list>
#include <unordered_map>
#include <vector>
#pragma once

class Alignment
{
public:
	Alignment(std::unordered_map<std::string, int>* net_pro,
		std::unordered_map<std::string, score*>* can_weight, double mean);
	~Alignment();
	double getMatchScore(std::vector<std::string>* match);
	void writeAlignment(std::string output);
	int scenarios(std::string pro1, std::string pro2);
	int judge(std::string pro1, std::string pro2);
	double update(std::string pro1, std::string pro2, int T_i, float m_ds);
	bool doit(float _dat, int T_i, float m_ds);
	

private:
	std::unordered_map < std::string, std::list<std::vector<std::string>* >::iterator > m_unmA;
	std::list<std::vector<std::string>*> alignmrnt;
	std::unordered_map<std::string, int>* m_unmNetPro;
	std::unordered_map<std::string, score*>* m_unmWeight;
	double m_dMean;
};

#endif
