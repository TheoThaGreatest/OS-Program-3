// Name:
// Program 3
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int LRU(int, int);
int FIFO(int, int);
int Clock(int, int);
int Random(int, int);
void Memory_trace();

int trace[1000]; // Address memory trace
/*******************************************************************************************************************
 * Function: main
 * *****************************************************************************************************************/
int main()
{
	//loop 1000 experiments
		//generate a memory trace
		//loop for working set size from 2 through 20
			//function call
	Memory_trace();
	for(int i = 0; i <=999; i++)
	{
		cout << trace[i] << endl;
	}
	return 0;
}
/******************************************************************************************************************
 * Function: Memory_trace()
 * ****************************************************************************************************************/
void Memory_trace()
{
	int base_address = 0;
	// i is the partition 0 to 9
	for(int i = 0; i <= 9; i++)
	{
		base_address = 25 * (rand() / (RAND_MAX/100 + 1));
		// j is the index from 0 to 99
		for(int j = 0; j <= 99; j++)
		{
			trace[100*i+j] = base_address + (rand() / (RAND_MAX/50 + 1));
		}
	}
}
/***************************************************************************************************************
 * Function LRU
 * *************************************************************************************************************/
int LRU (int working_set_size)
{
	int faults = 0;

	return faults;
}
/*************************************************************************************************************
 * Function FIFO
 * ***********************************************************************************************************/
int FIFO(int working_set_size)
{
	int faults = 0;

	return faults;
}
/*************************************************************************************************************
 * Function: Clock
 * ***********************************************************************************************************/
int Clock(int working_set_size)
{
	int faults = 0;

	return faults;

}
/************************************************************************************************************
 * Function: Random
 * **********************************************************************************************************/
int Random(int working_set_size)
{
	int faults = 0;

	return faults;
}
