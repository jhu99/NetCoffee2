#include <iostream>
#include "ReadPPI.h"
#include "argparser.h"
#include "ReadBitscore.h"

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
	cout << "sample vector:" << "P62259" << endl;
	cout << "(";
	for (int i = 0; i < 5; i++)
	{
		cout << net.top_vec["P62259"][i] << " ";
	}
	cout << ")" << endl;
	cout << "sample vector:" << "P63101" << endl;
	cout << "(";
	for (int i = 0; i < 5; i++)
	{
		cout << net.top_vec["P63101"][i] << " ";
	}
	cout << ")" << endl;


	ReadBitscore bitscore("int_bit.cf", net);
	cout << "candidate size:" << bitscore.protein_score.size() << endl;
	cout << "bit and top score of P63101 and P62259 :" << endl;
	/*double bit = bitscore.protein_score[str_add("P62259", "P63101")]->bitscore;
	cout << "bit:" << (bit - bitscore.m_dMinBitsc) / (bitscore.m_dMaxBitsc - bitscore.m_dMinBitsc) << endl;
	cout << "top:" << bitscore.protein_score[str_add("P62259", "P63101")]->topscore << endl;*/
	cout << bitscore.getScore("P62259", "P63101") << endl;
	return 0;
}
