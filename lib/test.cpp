#include <iostream>
#include "ReadPPI.h"
#include "argparser.h"
#include "ReadBitscore.h"
#include "Alignment.h"
#include "simulate.h"

using namespace std;

std::string str_add(std::string str1, std::string str2);

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


    //ArgParser mf_parser;
    //Option mf_option;
    //
    //// Parser the argument.
    //mf_parser.setName("NetCoffee2", "An application for multiple global network alignment.");
    //mf_parser.setVerion("1.0.006");
    //mf_parser.refOption("help", "Show help information.", mf_option.help);
    //mf_parser.refOption("version", "Show the current version.", mf_option.version);
    //mf_parser.refOption("input", "The path of an input file.", mf_option.inputfilename, "", true);
    //mf_parser.refOption("numnet", "The number of ppi networks", mf_option.numNet,3,true);
    //
    //if(!mf_parser.run(argc, argv))
    //    return 1;
    
	ReadPPI net("int_nets.tab", 3);
	net.calculate_topologyVector();

	cout << "sample vector:" << "Q9EQK5" << endl;
	cout << "(";
	for (int i = 0; i < 5; i++)
	{
		cout << net.top_vec["Q9EQK5"][i] << " ";
	}
	cout << ")" << endl;
	cout << "sample vector:" << "Q80Z64" << endl;
	cout << "(";
	for (int i = 0; i < 5; i++)
	{
		cout << net.top_vec["Q80Z64"][i] << " ";
	}
	cout << ")" << endl;


	unordered_map<std::string, double* > top = net.top_vec;
	ReadBitscore bitscore("int_bit.cf", top, 0.5);
	string* candidates = new string[(bitscore.can_size) * 2];
	bitscore.colected_candidates(candidates);

	Alignment Ali(net.net_protein, bitscore.can_weight, bitscore.m_dMeanf);

	sumulate sim(100, 100, 10, bitscore.can_size, candidates, &Ali);
	sim.start();
	
	return 0;
}
