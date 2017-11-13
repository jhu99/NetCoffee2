#include <iostream>
#include <igraph.h>
#include "ReadPPI.h"

using namespace std;

int main()
{
	ReadPPI net("int_nets.tab", 3);
	cout << "sample vector:" << "Q0PHV7" << endl;
	cout << "(";
	for (auto i : net.top_vec["Q0PHV7"])
	{
		cout << i << " ";
	}
	cout << ")" << endl;
	return 0;
}