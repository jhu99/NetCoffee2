#include <iostream>
#include "ReadPPI.h"
#include "argparser.h"

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
	cout << "sample vector:" << "Q0PHV7" << endl;
	cout << "(";
	for (auto i : net.top_vec["Q0PHV7"])
	{
		cout << i << " ";
	}
	cout << ")" << endl;
	return 0;
}
