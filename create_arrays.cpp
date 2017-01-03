#include <fstream>
#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
	// Create the files where we will store our arrays.
	ofstream a;
	ofstream b;
	// Open files.
	a.open("a.txt");
	b.open("b.txt");
	if(a.good() && b.good())
	{
		cout << "Writing to files...\n";
		for(unsigned int i = 0; i < ARRAY_SIZE; ++i)
		{
			a << i << '\n';
			b << 2*i << '\n';
		}
	}
	a.close();
	b.close();
	cout << "Done!" << endl;
	return 0;
}
