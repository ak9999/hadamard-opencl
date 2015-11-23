#include <fstream>
#include <iostream>
#include "functions.h"

using namespace std;

int main(int argc, char * argv[])
{

	/**
	* Create the files where we will store our arrays.
	*/
	ofstream a;
	ofstream b;

	// Open files in append mode.
	a.open("a.txt");
	b.open("b.txt");

	if(a.good() && b.good())
	{
		cout << "Opening files..." << endl;
		
		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			a << i << endl;
			b << 2*i << endl;
		}
	}

	a.close();
	b.close();

	cout << "Done!" << endl;
	
	return 0;
}