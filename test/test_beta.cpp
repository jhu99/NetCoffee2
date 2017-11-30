#include <iostream>
#include <array>
#include "ReadPPI.h"
#include "argparser.h"
#include "ReadBitscore.h"
#include "Alignment.h"
#include "simulate.h"
#include <time.h>

using namespace std;


struct Option{
    std::string inputfilename_net;
	std::string inputfilename_bit;
    int numNet;
    std::string outputfilename;
	double aplh;
	double beta;
    bool help;
    bool version;
    Option(){
    }
};

int main(int argc, const char * argv[])
{


    ArgParser mf_parser;
    Option mf_option;
    
	//Parser the argument
	mf_parser.setName("NetCoffee2", "An application for multiple global network alignment.");
    mf_parser.setVerion("1.0.006");
    mf_parser.refOption("help", "Show help information.", mf_option.help);
    mf_parser.refOption("version", "Show the current version.", mf_option.version);
    mf_parser.refOption("inputnet", "The path of an input file.", mf_option.inputfilename_net, "", true);
	mf_parser.refOption("inputbit", "The path of an input file.", mf_option.inputfilename_bit, "", true);
    mf_parser.refOption("numnet", "The number of ppi networks", mf_option.numNet,3,true);
	mf_parser.refOption("output", "The path of an output file.", mf_option.outputfilename, "", true);
	mf_parser.refOption("alph", "alph for sequence and topology similarity", mf_option.aplh, 0.5);
	mf_parser.refOption("beta", "beta used for the rate of conserved protein in a same network", mf_option.beta, 2);
    
    if(!mf_parser.run(argc, argv))
        return 1;
	clock_t start = clock();

	ReadPPI net(mf_option.inputfilename_net, mf_option.numNet);
	net.calculate_topologyVector();

	unordered_map<std::string, double* > top = net.top_vec;
	ReadBitscore bitscore(mf_option.inputfilename_bit, top, mf_option.aplh);

	cout << "bitscore.protein_score.size():" << bitscore.protein_score.size() << endl;
	unordered_map<string, score*>::iterator *candidates = new
		unordered_map<string, score*>::iterator[bitscore.protein_score.size()];
	bitscore.colected_candidates(mf_option.beta, candidates);
	
	Alignment Ali(&net.net_protein, &bitscore.protein_score, bitscore.m_dMeanf);
	sumulate sim(1000, 100, 10, bitscore.can_size, candidates, &Ali, mf_option.outputfilename);
	sim.start();
	
	delete[] candidates;
	candidates = NULL;
	clock_t ends = clock();
	cout << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC << endl;
	
	return 0;
}
