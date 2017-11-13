#ifndef ReadPPI_h
#define ReadPPI_h

#include <string>
#include <igraph.h>
#include <unordered_map>


class ReadPPI
{
public:
	ReadPPI(std::string netname, int num_nets);
	~ReadPPI();
	std::unordered_map<std::string, std::vector<double>> top_vec;
	
private:
	int m_iNumNets;
	
};

#endif