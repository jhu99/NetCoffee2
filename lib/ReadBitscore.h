#ifndef ReadBitscore_h
#define ReadBitscore_h

#include <string>
#include <unordered_map>

class ReadBitscore
{
public:
	ReadBitscore(std::string filename, std::unordered_map<std::string, double* > &top_vec, double alph);
	~ReadBitscore();
	struct score
	{
		double bitscore;
		double topscore;
		double finalscore;
	};
	std::unordered_map<std::string, double> can_weight;
	void colected_candidates(std::string*);
	double m_dMeanf;
	int can_size;

private:
	int m_iNumNets;
	double m_dMaxBitsc;
	double m_dMinBitsc;
	double m_dAlph;
	std::unordered_map<std::string, score*> protein_score;
};

#endif