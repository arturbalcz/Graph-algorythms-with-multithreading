// PW_lab1_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <ctime>

using namespace std; 

#define NUM_THREADS 4

int rand_r(unsigned int *seed)
{
	unsigned int next = *seed;
	int result;
	next *= 1103515245;
	next += 12345;
	result = (unsigned int)(next / 65536) % 2048;
	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;
	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;
	*seed = next;
	return result;
}

int ra[4][10];

int main()
{
	double start, end; 

	unsigned int seed[4]; 
	seed[0]	= time(NULL);
	seed[1] = time(NULL)+10;
	seed[2] = time(NULL)+100;
	seed[3] = time(NULL)+1000;

	omp_set_num_threads(NUM_THREADS); 

	int nt, nt_p; 

	//start = omp_get_wtime();

#pragma omp parallel for 
//#pragma omp parallel
	for(int i=0; i<10000; i++)
	{	
		int nt = omp_get_thread_num(); 
		int res = rand_r(&seed[nt])%10;
		ra[nt][res]++; 
	}


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << ra[i][j] << "\t"; 
		}
		cout << endl; 
	}


	//end = omp_get_wtime() - start;

	//cout << end << endl;


    return 0;
}

