#ifndef simulate_h
#define simulate_h

#include <string>
#include <unordered_map>
#include "Alignment.h"


class sumulate
{
public:
	sumulate(int _K, int _T_max, int _T_min, int can_size,
		std::string* candidate, Alignment *ali);
	~sumulate();
	void start();

private:
	int m_iK;
	int m_iTmax;
	int m_iTmin;
	int m_cansize;
	std::string* m_Pcandidates;
	Alignment *m_Pali;

};

#endif