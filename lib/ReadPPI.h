#ifndef ReadPPI_h
#define ReadPPI_h

#include <igraph.h>
#include <string>
#include <unordered_map>
#include <vector>

class ReadPPI
{
public:
	ReadPPI(std::string netname, int num_nets);
	~ReadPPI();
	std::unordered_map<std::string, double* > top_vec;
	void calculate_topologyVector();
	std::unordered_map<std::string, std::string> net_protein;

private:
	int m_iNumNets;
	std::vector<igraph_t> m_igraph;
	std::vector<std::string> *m_vecEdges;
	std::unordered_map<std::string, int> *m_umap_vectex;
	std::unordered_map<int, std::string> *m_umap_pro;
	std::vector<std::string> id_nets;
};

#endif
