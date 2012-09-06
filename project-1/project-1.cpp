#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{	
	cout << "Jon Warner\nCS3060\n" << endl;

	for (int i = 1; i <= argc; ++i)
	{
		cout << argv[i] << endl;
	}
	
	return 0;
}
