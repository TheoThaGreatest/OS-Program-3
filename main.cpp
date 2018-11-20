// Name: Theophilus Ojukwu II
// Program 3
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int LRU(int);
int FIFO(int);
int Clock(int);
int Random(int);
void Memory_trace();

int trace[1000]; // Address memory trace
/*******************************************************************************************************************
 * int main()
 * Author Theophilus Ojukwu II
 * Date 18 November 2018
 * Description: the main function generates the memory trace and 1000 experiments 
 * and runs the algorithms to detct Faults and output the number of faults
 *
 * Parameters:
 * NONE
 * *****************************************************************************************************************/
int main()
{
	int faults[20][4]; // 2D array to hold the number of faults in each working set for each algorithim
	//loop 1000 experiments
	for(int i = 1; i < 1000; i++)
	{
		Memory_trace(); // create a memory trace
		for(int j = 2; j <= 20; i++) 
		{
			faults[j][0] += LRU(j);
			faults[j][1] += FIFO(j);
			faults[j][2] += Clock(j);
			faults[j][3] += Random(j);
		}
	}
	
	for(int s = 2; s < 21; s++)
	{
		cout << "LRU: " << faults[s][0]/1000.0 << "; working set " << s << endl; // print LRU
		cout << "FIFO: " << faults[s][1]/1000.0 << "; working set " << s << endl; // prirnt FIFO
		cout << "Clock: " << faults[s][2]/1000.0 << "; working set " << s << endl;   // Print Clock
		cout << "Random: " << faults[s][3]/1000.0 << "; working set " << s << endl; // Print Random
	}
	
	return 0;
}
/******************************************************************************************************************
 * Void Memory_trace()
 * Author: Theophilus Ojukwu II
 * Date: 18 November 2018
 * Description: This function creates a memory trace of 1000 addresses
 *
 * Parameters:
 * NONE
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
/*****************************************************************************************************************
 * int findLru
 * Author: Theophilus Ojukwu II
 * Date: 18 November 2018
 * Description: This function adis the LRU page replacement algorithim
 *
 * Parameters:
 * int time[]	Holds the time in which thee leat recently used number
 * int n	holds the working set size
 *****************************************************************************************************************/
int findLru(int time[], int n)
{
	int minimum = time[0], pos = 0;
	for(int i = 1; i < n; ++i)// finds the minmimum in the array for least recent
	{
		if(time[i] < minimum) // finds the minmum
		{
			minimum = time[i];
			pos = i;
		}
	}
	return pos; // returns the least recent used position
}
/***************************************************************************************************************
 * int LRU(int workin_set_size)
 * Author: Theophilus Ojukwu II
 * Date: 18 November 2018
 * Description: This function implements the page replacement policy LRU and returns the number of faults found
 *
 * Paramerters:
 * int working_set_size	This holds the woking set size for the number of pages in the working set
 * *************************************************************************************************************/
int LRU (int working_set_size)
{
	int frames[25], time[working_set_size];
	int count = 0, pos = 0, faults = 0;
	for(int i = 0; i < working_set_size; i++)
	{
		frames[i] = -1; 
	}

	for(int i = 0; i < 100; ++i)
	{
		int flag1 = 0, flag2 = 0;
		for(int j = 0; j < working_set_size; ++j)
		{
			if(frames[j] == trace[i]) // if they equal --> no replacement
			{
				count++; // increase count
				time[j] = count; // keep track of the least recent
				flag1 = flag2 = 1;
				break;
			}
		}
		
		if(flag1 == 0)
		{
			for(int j = 0; j < working_set_size; ++j)
			{
				if(frames[j] == -1) // if there is -1 then increse the faults
				{
					count++;
					faults++;
					frames[j] = trace[i];
					time[j] = count;
					flag2 = 1;
					break;
				}
			}
		}

		if(flag2 == 0)
		{
			pos = findLru(time, working_set_size); //finds LRU
			count++; // increase count
			faults++; // number of faults increase
			frames[pos] = trace[i]; 
			time[pos] = count;
		}
	}
	return faults;
}
/*************************************************************************************************************
 * int FIFO(int working_set_size)
 * Author: Theophilus Ojukwu II
 * Date: 18 November 2018
 * Description: This function is an implementation of the page replacement algorithim FIFO(First-In-First-Out)
 * and it returns the number of faults found
 *
 * Parameters:
 * int working_set_size	This holds the working set size of the working set
 * ***********************************************************************************************************/
int FIFO(int working_set_size)
{
	int faults = 0; // holds number of faults
	int temp[working_set_size]; // working set
	for(int i = 0; i < working_set_size; i++) //Within working set
	{
		temp[i] = -1; // set to -1 not to conflict with trace
	}

	for(int i = 0; i < 1000; i++)// For all 1000 trace pages
	{
		int s = 0;
		for(int j = 0; j < working_set_size; j++) // withing the working set
		{
			if(trace[i] == temp[j]) // if they are equal
			{
				s++; // pages were good
				faults--; // There wasn't a problem
			}
		}

		faults++; // this meand there was a problem

		if((faults <= working_set_size) && (s == 0)) // if fault
		{
			temp[i] = trace[i]; // set new value
		}
		else if(s == 0) // if pages aren't good
		{
			// Set new value at different location
			temp[(faults -1) % working_set_size] = trace[i];
		}
	}
	return faults;
}
/*************************************************************************************************************
 * int Clock(int working_set_size)
 * Author: Theophilus Ojukwu II
 * Date: 18 November 2018
 * Description: This function replaces pages using the Clock algorithim and returns the number of faults found
 *
 * Parameters
 * int working_set_size	this holds the size of the working set
 * ***********************************************************************************************************/
int Clock(int working_set_size)
{
	int frame[working_set_size]; // working set
	int faults = 0; // number of faults
	int useBit = 0; // binary bit
	int next = 0; // pointer to the next number
	for(int i = 0; i < working_set_size; i++) // withing the working set
	{
		frame[i] = -1;
	}

	for(int i = 0; i <= 1000; i++)
	{
		useBit = 0;
		for(int k = 0; k < working_set_size; k++)
		{
			if(frame[k] == trace[i]) //if they are the same no need for a replacement
			{
				useBit = 1;
			}
		}
		if (useBit == 0) // if the use bit is zero then replace the current page
		{
			frame[next] = trace[i]; //replacement
			next = (next + 1) % working_set_size; 
			faults++; // increase number of faults
		}
	}
	return faults;
}
/************************************************************************************************************
 * int Random(int working_set_size)
 * Author: Theophilus Ojukwu II
 * Date: 18 November 2019
 * Description: This function implements the page replacement algorithim Random and it returns the number of 
 * faults found
 *
 * Parameters
 * int working_set_size	Holds the working set size of the working set
 * **********************************************************************************************************/
int Random(int working_set_size)
{
	int faults = 0;
	int temp[working_set_size]; // working set

	for(int i = 0; i < working_set_size; i++) // within working set
	{
		temp[i] = -1; // set to -1 so it doesn't conflict with trace
	}

	for(int i = 0; i < 1000; i++) // For all 1000 trace pages
	{
		int s = 0;

		for(int j = 0; j < working_set_size; j++) // within working set
		{
			// randomizes the element in which we check the working set
			if(trace[i] == temp[rand()/ (RAND_MAX/working_set_size + 1)]) // if they are equal
			{
				s++; // pages are good
				faults--; // there wasn't a problem in the first place
			}
		}
		faults++; // problem
		
		if((faults <= working_set_size) && (s == 0)) // if fault
		{
			temp[i] = trace[i]; // set new value
		}
		else if(s == 0)
		{
			// set new value at different location
			temp[(faults - 1) % working_set_size] = trace[i];
		}
	}
	return faults;
}
