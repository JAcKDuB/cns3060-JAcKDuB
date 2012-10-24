#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

const int SUCCESS = 0;
const int FAILURE = 1;

void FCFS(int count, vector<int> locations);
void SSTF(int count, vector<int> locations);
void elevator(char* locations);


// ****************************************************************

int main(int argc, char* argv[])
{
	int input = 1;
	int temp = 0;
	vector<int> values;

	cout << "Please enter track numbers to seek.  A negative value ends input" << endl;

	while(input >= 0)
	{
		
		//make sure a number in entered
		while(!(cin>>temp))
		{
			cout << "Please input a number." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}

		input = temp;

		if (input >= 0)
		{			
			values.push_back(input);			
		}
	}
	

	FCFS(values.size(), values);
	SSTF(values.size(), values);
	
	//for (int i = 1; i <= argc -1; ++i)
	//{
	//	cout << argv[i] << endl;
	//}

	return 0;
}

// ****************************************************************

void FCFS(int count, vector<int> locations)
{
	int current = 15;
	int next = 0;
	int traversed = 0;
	cout << "\n***************************************************\n" << endl;
	cout << "First Come First Served\n" << endl;
	cout << "Head Movement" << endl;
	for (int i = 0; i <= count - 1; ++i)
	{
		next = locations[i];
		cout << "Tracks " << current << " - " << next;
		traversed = abs(current - next);
		cout << "\t\tTraversed : " << traversed << endl;
		current = next;
	}

}

// ****************************************************************

void SSTF(int count, vector<int> locations)
{
	int current = 15;
	int next = 0;
	int distance = 0;
	int traversed = 0;
	int iterator = 0;
	vector<int> holder = locations;
	cout << "\n***************************************************\n" << endl;
	cout << "Shortest Seek Time First\n" << endl;
	cout << "Head Movement" << endl;

	while (holder.size() > 0)
	{
		distance = abs(holder[0] - current);
		for (int i = 0; i <= holder.size() - 1; ++i)
		{
			if (abs(holder[i] - current) <= distance)
			{
				next = holder[i];
				iterator = i;
			}			
		}
		cout << "Tracks " << current << " - " << next;
		traversed = abs(current - next);
		cout << "\t\tTraversed : " << traversed << endl;
		current = next;
		holder.erase(holder.begin() + iterator);
	}
}

// ****************************************************************

void elevator(char* locations)
{

}

// ****************************************************************
