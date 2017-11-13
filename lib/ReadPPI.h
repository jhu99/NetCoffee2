#include <string>
#include <igraph.h>
#include <unordered_map>

using namespace std;

class ReadPPI
{
public:
	ReadPPI(string netname, int num_nets);
	~ReadPPI();
	unordered_map<string, vector<double>> top_vec;
	
private:
	int m_iNumNets;
	
};

