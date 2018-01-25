#ifndef ReadBitscore_h
#define ReadBitscore_h

#include <string>
#include <unordered_map>
#include "ProteinRel.h"

class ReadBitscore
{
public:
	ReadBitscore(std::string filename, std::unordered_map<std::string, double* > &top_vec, double alph, double evalue);
	~ReadBitscore();
	std::unordered_map<std::string, score*> protein_score;
	void colected_candidates(double beta, 
		std::unordered_map<std::string, score*>::iterator *candidate);
	double m_dMeanf;
	int can_size;

private:
	double m_dMaxBitsc;
	double m_dMinBitsc;
	double m_dAlph;
	
};

#endif
