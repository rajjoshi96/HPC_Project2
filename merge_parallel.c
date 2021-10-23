// Prpgram runs perfectly, can be submitted


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/time.h>
#include <mpi.h>
#include<math.h>
#define n 10000
#define LEN 10000

void merge(float *, float *, int, int, int);
void mergeSort(float *, float *, int, int);
void array_gen();

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));
    struct timeval start, end;
    gettimeofday(&start, NULL);
    double store_time[8];
	/********** Created populate the array **********/
    float t = 10.0;
	double array[LEN]={};
	double original_array[LEN]={};
	for ( int i = 0 ; i < LEN ; i++ ) 
	{
        array[i] =((double)rand()/(double)(RAND_MAX)) * t;
    }

    // write it
    FILE *fp = fopen("testfile1.bin","wb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fwrite(&array[i],sizeof(array[i]),1,fp);
    }

    fp = fopen("unsorted_array.bin","wb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fwrite(&array[i],sizeof(array[i]),1,fp);
    }
    fclose(fp);
    
    //double input[LEN]={};
    // read it
    fp = fopen("unsorted_array.bin","rb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fread(&original_array[i],sizeof(original_array[i]),1,fp);
    }
    fclose(fp);
	int c;
	srand(time(NULL));
	// for(c = 0; c < n; c++) {
		
	// 	original_array[c] = rand() % n;
		
	// }


	
	/********** Initialize MPI **********/
	int world_rank;
	int world_size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		
	/********** Divide the array in equal-sized chunks **********/
	int size = n/world_size;
	
	/********** Send each subarray to each process **********/
	float *sub_array = malloc(size * sizeof(float));
	MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/********** Perform the mergesort on each process **********/
	float *tmp_array = malloc(size * sizeof(float));
	mergeSort(sub_array, tmp_array, 0, (size - 1));
	
	/********** Gather the sorted subarrays into one **********/
	float *sorted = NULL;
	if(world_rank == 0) {
		
		sorted = malloc(n * sizeof(float));
		
	}
	
	MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/********** Make the final mergeSort call **********/
	if(world_rank == 0) {
		
		float *other_array = malloc(n * sizeof(float));
		mergeSort(sorted, other_array, 0, (n - 1));
		
		/********** Display the sorted array **********/
		printf("This is the sorted array: ");
		for(c = 0; c < n; c++) {
			
			printf("%f \n", sorted[c]);
			
		}
			
		//printf("\n");
		printf("\n");
		gettimeofday(&end, NULL);
		double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
		printf("Delta = %f \n",delta); 
		/********** Clean up root **********/
		free(sorted);
		free(other_array);
			
	}
	
	/********** Clean up rest **********/
	//free(original_array);
	free(sub_array);
	free(tmp_array);
	
	/********** Finalize MPI **********/
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

	
}

/********** Merge Function **********/
void merge(float *a, float *b, int l, int m, int r) {
	
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	
	while((h <= m) && (j <= r)) {
		
		if(a[h] <= a[j]) {
			
			b[i] = a[h];
			h++;
			
		}
			
		else {
			
			b[i] = a[j];
			j++;
			
		}
			
		i++;
		
	}
		
	if(m < h) {
		
		for(k = j; k <= r; k++) {
			
			b[i] = a[k];
			i++;
			
		}
			
	}
		
	else {
		
		for(k = h; k <= m; k++) {
			
			b[i] = a[k];
			i++;
			
		}
			
	}
		
	for(k = l; k <= r; k++) {
		
		a[k] = b[k];
		
	}
		
}

/********** Recursive Merge Function **********/
void mergeSort(float *a, float *b, int l, int r) {
	
	int m;
	
	if(l < r) {
		
		m = (l + r)/2;
		
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);
		
	}
		
}




//The code to be merged
// This code runs perfectly fine for the first two questions of Project 2
// Change the LEN to higher values

