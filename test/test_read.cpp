#include <iostream>
#include <igraph.h>
#include "ReadPPI.h"

using namespace std;

int main()
{
	ReadPPI net("int_nets.tab", 3);
	cout << "hello world" << endl;
	return 0;
}