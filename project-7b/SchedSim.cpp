#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// ****************************************************************

struct Process
{
	int pID;
	int arrival;
	int complete;
	double wait;
	double turnAround;
};

void printProcesses(vector<Process> list);
vector<Process> sortProcesses(vector<Process> list);
void calculateTimes(vector<Process> process);
void calculateTimes2(vector<Process> list);
void SJF(vector<Process> process);
void SRT(vector<Process> process);

// ****************************************************************

int main(int argc, char* argv[])
{
	string myString = "";
	vector<Process> processes;
	vector<Process> SRTprocesses;
	
	//build processes
	while(!cin.eof())
	{
		Process temp;
		getline(cin, myString);
		stringstream stream(myString);
		stream >> temp.pID >> temp.arrival >> temp.complete;
		processes.push_back(temp);
	}

	//calculate process times
	cout << "\n**First Come First Serve**\n";
	calculateTimes(processes);
	SJF(processes);
	SRT(processes);

	return 0;
}

// ****************************************************************

void calculateTimes(vector<Process> process)
{
	vector<Process> holder = process;
	int totalTime = 0;
	float avgWait = 0;
	float avgTurnaround = 0;
	int count = 0;

	//calculate wait and turnaround times
	for (int i = 0; i < holder.size(); ++i)
	{
		holder[i].wait = totalTime - holder[i].arrival;
		totalTime += holder[i].complete;
		holder[i].turnAround = totalTime - holder[i].arrival;
		avgWait += holder[i].wait;
		avgTurnaround += holder[i].turnAround;
		++count;
	}

	//find averages
	avgWait /= count;
	avgTurnaround /= count;

	//print results
	vector<Process> sorted = sortProcesses(holder);

	printProcesses(sorted);
	cout << "Average Wait : " << avgWait << "\tAverage Turnaround : " << avgTurnaround << endl;
}

// ****************************************************************

void calculateTimes2(vector<Process> list)
{
	vector<Process> holder = list;
	int totalTime = 0;
	double avgWait = 0;
	double avgTurnaround = 0;
	int count = 0;

	//calculate wait and turnaround times
	for (int i = 0; i < holder.size(); ++i)
	{
		avgWait += holder[i].wait;
		avgTurnaround += holder[i].turnAround;
		++count;
	}
	
	//find averages
	avgWait /= count;
	avgTurnaround /= count;


	//print results
	vector<Process> sorted = sortProcesses(holder);
	
	printProcesses(sorted);
	cout << "Average Wait : " << avgWait << "\tAverage Turnaround : " << avgTurnaround << endl;
}

// ****************************************************************

void SJF(vector<Process> process)
{
	vector<Process> order;
	vector<Process> ready;
	Process current;
	int eraseMe = 0;
	int pTime = 0;
	int time = 0;
	bool processing = false;
	bool finished = false;
	
	vector<Process> temp = process;
	cout << "\n**Shortest Job First**\n";

	while(!finished)
	{
		// for loop to find next arriving process
		for (int i = 0; i < temp.size(); ++i)
		{
			if (time >= temp[i].arrival)
			{
				// if time <= an arrival time of a process, it has arrived
				//add it to the ready list. Remove from the processing list
				ready.push_back(temp[i]);
				temp.erase(temp.begin() + i);
			}
		}

		//if the process is finished but is still "processing"
		if (pTime == 0 && processing)
		{
			//add it to the finished (order) list and stop processing
			order.push_back(current);
			processing = false;
		}

		//if there is no current process
		if (!processing)
		{
			//and there are processes ready
			if (ready.size() > 0)
			{
				int tempNumb;
				bool first = true;

				// find the shortest complete time and make it the current process
				for(int i = 0; i < ready.size(); ++i)
				{
					
					//get first process to check against
					if (first)
					{
						tempNumb = ready[i].complete;
						first = false;
					}

					if (ready[i].complete <= tempNumb)
					{
						tempNumb = ready[i].complete;
						current = ready[i];
						processing = true;
						//grab its index so it can be removed
						eraseMe = i;
					}
				}
				//add its process time
				pTime = current.complete;

				ready.erase(ready.begin() + (eraseMe));
			}
		}

		++time;
		--pTime;

		if (temp.size() == 0 && ready.size() == 0 && processing == false)
		{
			finished = true;
		}
	}

	calculateTimes(order);
}

// ****************************************************************

void SRT(vector<Process> process)
{
	vector<Process> order;
	vector<Process> ready;
	Process current;
	int waitFound [10];
	int currentIteration = 0;
	int pTime = 0;
	int time = 0;
	bool processing = false;
	bool finished = false;
	bool newAddition = false;
	bool firstProcess = true;

	vector<Process> temp = process;
	cout << "\n**Shortest Remaining Time**\n";

	while(!finished)
	{
		// for loop to find next arriving process
		for (int i = 0; i < temp.size(); ++i)
		{
			if (time >= temp[i].arrival)
			{
				// if time <= an arrival time of a process, it has arrived
				//add it to the ready list. Remove from the processing list
				ready.push_back(temp[i]);
				temp.erase(temp.begin() + i );
				newAddition =  true;
			}
		}

		//if processs time has ended and there is a process processing
		if (pTime == 0 && processing)
		{
			current.turnAround = time - current.arrival;
			order.push_back(current);
			ready.erase(ready.begin() + currentIteration);
			processing = false;
		}

		//if there is no current process, or a new process has arrived
		if (!processing || newAddition)
		{
			//and there are processes ready
			if (ready.size() > 0)
			{
				int tempNumb;
				bool first = true;
				int origComplete = 0;
				int origID = 0;
				int origIteration = 0;
				
				if (!firstProcess && processing)
				{
					//set current process' complete time to reflect work done
					ready[currentIteration].complete = pTime;
					ready[currentIteration].wait = current.wait;

					// in the event of a draw in process times after a new selection
					//	store this info so we can continue to process this.
					origComplete = pTime;
					origID = current.pID;
					origIteration = currentIteration;
				}

				// find the shortest complete time and make it the current process
				for(int i = 0; i < ready.size(); ++i)
				{
					
					//get first process to check against
					if (first)
					{
						tempNumb = ready[i].complete;
						first = false;
					}


					if (ready[i].complete <= tempNumb)
					{						
						tempNumb = ready[i].complete;
						current = ready[i];
						processing = true;

						//grab its index so it can be removed
						currentIteration = i;
						newAddition = false;
					}
					
				}

				//stay on the original process in the event of a draw
				if (current.complete == origComplete)
				{
					if (current.pID != origID)
					{
						current = ready[origIteration];
						currentIteration = origIteration;
					}
				}

				//if this process has never processed
				if (waitFound[current.pID - 1] != current.pID)
				{
					waitFound[current.pID - 1] = current.pID;
					current.wait = time - current.arrival;
				}

				//add its process time
				pTime = current.complete;
			}
		}


		++time;
		--pTime;

		if(firstProcess)
		{
			firstProcess = false;
		}

		if (temp.size() == 0 && ready.size() == 0 && processing == false)
		{
			finished = true;
		}
	}

	calculateTimes2(order);
}

// ****************************************************************

void printProcesses(vector<Process> list)
{

	cout << "PID\t" << "Wait\t" << "Turnaround" << endl;

	for (int i = 0; i < list.size(); ++i)
	{
		cout << list[i].pID << "\t" << list[i].wait << "\t " << list[i].turnAround << endl;
	}
}

// ****************************************************************

vector<Process> sortProcesses(vector<Process> list)
{
	vector<Process> sorted;
	int j = 0;

	for (int i = 1; i <= list.size(); ++i)
	{
		while(list[j].pID != i)
		{
			++j;
		}

		sorted.push_back(list[j]);
		j = 0;
	}

	return sorted;
}

// ****************************************************************
