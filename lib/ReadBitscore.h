#ifndef ReadBitscore_h
#define ReadBitscore_h

#include "ReadPPI.h"
#include <string>
#include <unordered_map>

class ReadBitscore
{
public:
	ReadBitscore(std::string filename, ReadPPI &network);
	~ReadBitscore();
	struct score
	{
		double bitscore;
		double topscore;
	};
	std::unordered_map<std::string, score*> protein_score;
	double getScore(std::string pro1, std::string pro2);

private:
	int m_iNumNets;
	double m_dMaxBitsc;
	double m_dMinBitsc;
};

#endif