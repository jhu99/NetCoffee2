#ifndef simulate_h
#define simulate_h

#include <string>
#include <unordered_map>
#include "Alignment.h"


class sumulate
{
public:
	sumulate(int _K, int _T_max, int _T_min, int can_size,
		std::unordered_map<std::string, score*>::iterator *candidate, Alignment *ali, std::string output);
	~sumulate();
	void start(std::ofstream &out);

private:
	int m_iK;
	int m_iTmax;
	int m_iTmin;
	int m_cansize;
	std::unordered_map<std::string, score*>::iterator* m_Pcandidates;
	Alignment *m_Pali;
	std::string m_Soutput;

};

#endif