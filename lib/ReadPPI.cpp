#include <iostream>
#include <fstream>
#include "ReadPPI.h"

using namespace std;

ReadPPI::ReadPPI(string netname, int num_nets)
{
	m_iNumNets = num_nets;
	igraph_t *m_igraph = new igraph_t[m_iNumNets];
	vector<string> *m_vecEdges = new vector<string>[m_iNumNets];
	unordered_map<string, int> *m_umap_vectex = new unordered_map<string, int>[m_iNumNets];
	unordered_map<int, string> *m_umap_pro = new unordered_map<int, string>[m_iNumNets];
	ifstream in(netname);
	if (!in){
		cout << "can't open net..." << endl;
	}//从文本中读取网络

	string temp[3];
	vector<string> id_nets;
	int i = 0;
	int netId = -1;
	string net = "ID";
	unordered_map<string, int>::iterator ver;
	unordered_map<int, string>::iterator pro;
	cout << "reading network..." << endl;
	while (in >> temp[0] && in >> temp[1] && in >> temp[2])
	{
		if (temp[0] != net)
		{
			netId++;
			net = temp[0];
			id_nets.push_back(net);
			i = 0;
		}
		m_vecEdges[netId].push_back(temp[1]);
		m_vecEdges[netId].push_back(temp[2]);
		if (m_umap_vectex[netId].find(temp[1]) == m_umap_vectex[netId].end())
		{
			m_umap_vectex[netId][temp[1]] = i;
			m_umap_pro[netId][i] = temp[1];
			i++;
		}
		if (m_umap_vectex[netId].find(temp[2]) == m_umap_vectex[netId].end())
		{
			m_umap_vectex[netId][temp[2]] = i;
			m_umap_pro[netId][i] = temp[2];
			i++;
		}
	}

	igraph_vector_t *edge_vec = new igraph_vector_t[m_iNumNets];
	for (int p = 0; p < m_iNumNets; p++)
	{
		igraph_vector_init(&edge_vec[p], m_vecEdges[p].size());
		int k = 0;
		for (auto q : m_vecEdges[p])
		{
			VECTOR(edge_vec[p])[k] = m_umap_vectex[p][q];
			k++;
		}
		igraph_create(&m_igraph[p], &edge_vec[p], m_umap_vectex[p].size(), 0);
		igraph_simplify(&m_igraph[p], 1, 1, 0);
		cout << "number of vertex" << igraph_vcount(&m_igraph[p]) << endl;
		cout << "number of edges" << igraph_ecount(&m_igraph[p]) << endl;


	}
	delete[]m_igraph;
	m_igraph = NULL;
	delete[] m_vecEdges;
	m_vecEdges = NULL;
	delete[] m_umap_pro;
	m_umap_pro = NULL;
	delete[]m_umap_vectex;
	m_umap_vectex = NULL;
}

ReadPPI::~ReadPPI()
{
	

}