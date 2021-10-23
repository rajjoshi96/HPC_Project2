//#include "stdafx.h"
#include "mpi.h"//mpi.h must be put behind stafx.h
//#include <Windows.h>
#include <stdio.h>
#include <math.h>  
#include <stdlib.h>  


/* 
* Function name: GetRank 
* Function: Calculate the rank of the data belonging to it (the number of numbers smaller than this element) 
* Input: HX_data: pointer to the sequence to be sorted 
* HX_DataSize is the length of the sequence to be sorted 
MyLength is the length of the sequence to be sorted by this processor 
rank: pointer to rank array 
SumID: total number of processors 
MyID: processor ID 
* Output: Return 1 means the program ends normally 
*/ 
int GetRank (int * data, int DataSize, int MyLength, int * rank, int SumID, int MyID)  
{  
	int i, j;  
	int start, end;  

	start = DataSize/SumID * MyID;/* Starting position of part of the data */ 
	end = start + MyLength;/* End position of part of the data */ 

	for (j = start; j <end; j ++) {/* Calculate the rank * of part of the data  */
		rank [j-start] = 0;  
		for (i = 0; i <DataSize; i ++) {  
			if ((data [j]> data [i]) || ((data [j] == data [i]) && (j> i)))  
				rank [j-start] ++;  
		}  
	}  
	return 1;  
}  

/* 
* Function name: GetDataSize 
* Function: Read the length of the sequence to be sorted 
* Input: the length of the sequence to be sorted 
* Output: return the length of the sequence to be sorted 
*/ 
int GetDataSize ()  
{  
	int i;  

		fprintf (stderr, "Please enter the size of the array:"); 
		fflush (stderr);
		scanf ("% d", & i);  
	return i;  
}  


/* 
* Function name: main 
* Function: Main function, to implement enumeration sorting 
* Input: argc is the number of command line parameters; 
* argv is a string array composed of each command line parameter 
* Output: Return 1 means the program ends normally 
*/
int main (int argc, char * argv [])  
{  
	int DataSize, MyLength;/* DataSize: array length; MyLength: data length allocated by the processor */ 
	int * data_in, * data_out;/* Input and output array pointers */ 
	int * rank;/* rank array */ 
	int MyID, SumID;  
	int i, j;
	double starttime, endtime;

	MPI_Status status;                     

	MPI_Init (& argc, & argv);/* MPI initialization */ 
	MPI_Comm_rank (MPI_COMM_WORLD, & MyID);/* Each processor determines its own ID */ 
	MPI_Comm_size (MPI_COMM_WORLD, & SumID);/* Each processor determines the total number of processors */
	fprintf (stderr, "Process% d on %s \n", MyID);
	fflush (stderr);


	if (MyID == 0)/* main processor */ 
		DataSize = GetDataSize ();/* Read the length of the sequence to be sorted */ 

	MPI_Bcast (& DataSize, 1, MPI_INT, 0, MPI_COMM_WORLD);  
	/* The length of the main processor broadcast sequence to be sorted */ 

	/* Divide tasks among processors */ 
	MyLength = DataSize/SumID;                
	if (MyID == SumID-1)/* each processor determines the length of the sequence to be sorted */ 
		MyLength = DataSize-MyLength * (SumID-1);  

	data_in = (int *) malloc (DataSize * sizeof (int));/* allocate space for the sequence to be sorted */ 
	if (data_in == 0) printf ("Malloc memory error!");  


	if (MyID == 0) {                       
		data_out = (int *) malloc (DataSize * sizeof (int));/* The main processor allocates the space of the sorted array */ 
		if (data_out == 0) printf ("Malloc memory error!");  

		rank = (int *) malloc (DataSize * sizeof (int));/* allocate space of rank array */ 
		if (rank == 0) printf ("Malloc memory error!");  
	}  
	else {  
		rank = (int *) malloc (MyLength * sizeof (int));/* allocate space of the rank array */ 
		if (rank == 0) printf ("Malloc memory error!");  
	}  

	if (MyID == 0) {  
		int seed;  
		fprintf (stderr, "Please enter the seed of random number:");
		fflush (stderr);
		scanf ("% d", & seed);/* Get seed of random number */ 
		srand (seed);/* srand initialize random seed */                
		printf ("Get random number\n");  
		fflush (stderr);
		for (i = 0; i <DataSize; i ++) {  
			data_in [i] = ((int) rand ())% 10000;/* Generate random number and output */ 
			//printf ("% 10d", data_in [i]);  
		}  
		//printf ("\nOutput:");  
		printf ("\n");  
	}  

	starttime = MPI_Wtime ();
	/* Broadcast sequence to each processor */ 
	MPI_Bcast (data_in, DataSize, MPI_INT, 0, MPI_COMM_WORLD);  

	/* Each processor calculates the rank of the element */ 
	GetRank (data_in, DataSize, MyLength, rank, SumID, MyID);  

	/* Collect sorted data from each processor */ 
	if (MyID == 0) {  
		for (i = 1; i <SumID; i ++) {  
			if (i == SumID-1)  
				MPI_Recv (rank + MyLength * i, DataSize-MyLength * (SumID-1), MPI_INT, i, 0, MPI_COMM_WORLD, & status);  
			else  
				MPI_Recv (rank + MyLength * i, MyLength, MPI_INT, i, 0, MPI_COMM_WORLD, & status);  
		}  
	}  
	else  
		MPI_Send (rank, MyLength, MPI_INT, 0,0, MPI_COMM_WORLD);  


	/* Relocate each data according to the obtained rank */ 
	if (MyID == 0) {  
		for (i = 0; i <DataSize; i ++)  
			data_out [rank [i]] = data_in [i];  

		printf ("sorted data\n");
		for (i = 0; i <DataSize; i ++) {  
			//printf ("% 10d", data_out [i]);  
		}  
		printf ("\n");  
		endtime = MPI_Wtime ();
		printf ("Time =% f\n", endtime-starttime);
	}  

	MPI_Finalize ();    
	return 0;  
} 