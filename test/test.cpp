#include <iostream>
#include <array>
#include "ReadPPI.h"
#include "argparser.h"
#include "ReadBitscore.h"
#include "Alignment.h"
#include "simulate.h"

using namespace std;


struct Option{
    std::string inputfilename;
    int numNet;
    std::string outputfilename;
    bool help;
    bool version;
    Option(){
    }
};

int main(int argc, const char * argv[])
{

	/*ReadPPI net("image_net.txt", 1);

	net.calculate_topologyVector();
	cout << "sample vector:" << "a" << endl;
	cout << "(";
	for (int i = 0; i < 5; i++)
	{
	cout << net.top_vec["a"][i] << " ";
	}
	cout << ")" << endl;
	cout << "sample vector:" << "b" << endl;
	cout << "(";
	for (int i = 0; i < 5; i++)
	{
	cout << net.top_vec["b"][i] << " ";
	}
	cout << ")" << endl;
	*/


    ArgParser mf_parser;
    Option mf_option;
    
    // Parser the argument.
    mf_parser.setName("NetCoffee2", "An application for multiple global network alignment.");
    mf_parser.setVerion("1.0.006");
    mf_parser.refOption("help", "Show help information.", mf_option.help);
    mf_parser.refOption("version", "Show the current version.", mf_option.version);
    mf_parser.refOption("input", "The path of an input file.", mf_option.inputfilename, "", true);
    mf_parser.refOption("numnet", "The number of ppi networks", mf_option.numNet,3,true);
    
    if(!mf_parser.run(argc, argv))
        return 1;
    
	ReadPPI net(mf_option.inputfilename, mf_option.numNet);
	net.calculate_topologyVector();

	unordered_map<std::string, double* > top = net.top_vec;
	ReadBitscore bitscore("int_bit.cf", top, 0.5);

	unordered_map<string, score*>::iterator *candidates = new
		unordered_map<string, score*>::iterator[bitscore.protein_score.size()];
	bitscore.colected_candidates(1, candidates);
	
	Alignment Ali(&net.net_protein, &bitscore.protein_score, bitscore.m_dMeanf);
	cout << bitscore.m_dMeanf << endl;
	sumulate sim(100, 100, 10, bitscore.can_size, candidates, &Ali);
	sim.start();
	

	
	return 0;
}
