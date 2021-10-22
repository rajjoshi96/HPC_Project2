// This code runs perfectly fine for the first two questions of Project 2
// Change the LEN to higher values


#include<sys/time.h>
#include<stdio.h>
#include<stdlib.h>
#define LEN 10000
#define Size 10000


void merge_sort(int i, int j, double a[], double aux[]) {
    if (j <= i) {
        return;     // the subsection is empty or a single element
    }
    int mid = (i + j) / 2;

    // left sub-array is a[i .. mid]
    // right sub-array is a[mid + 1 .. j]
    
    merge_sort(i, mid, a, aux);     // sort the left sub-array recursively
    merge_sort(mid + 1, j, a, aux);     // sort the right sub-array recursively

    int pointer_left = i;       // pointer_left points to the beginning of the left sub-array
    int pointer_right = mid + 1;        // pointer_right points to the beginning of the right sub-array
    int k;      // k is the loop counter

    // we loop from i to j to fill each element of the final merged array
    for (k = i; k <= j; k++) {
        if (pointer_left == mid + 1) {      // left pointer has reached the limit
            aux[k] = a[pointer_right];
            pointer_right++;
        } else if (pointer_right == j + 1) {        // right pointer has reached the limit
            aux[k] = a[pointer_left];
            pointer_left++;
        } else if (a[pointer_left] < a[pointer_right]) {        // pointer left points to smaller element
            aux[k] = a[pointer_left];
            pointer_left++;
        } else {        // pointer right points to smaller element
            aux[k] = a[pointer_right];
            pointer_right++;
        }
    }

    for (k = i; k <= j; k++) {      
        a[k] = aux[k];
    }
}


int main( ) {
    double array[LEN]={};
    float t=10.0;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    double store_time[8];
    // fill it
    for ( int i = 0 ; i < LEN ; i++ ) {
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
    
    double input[LEN]={};
    // read it
    fp = fopen("unsorted_array.bin","rb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fread(&input[i],sizeof(input[i]),1,fp);
    }
    fclose(fp);
    double aux[Size]={};
    // print it
    // for ( int i = 0 ; i < LEN ; i++ ) {
    //     printf(" %f\n", input[i]);
    // }
    float n=LEN;
    merge_sort(0, n - 1, input, aux);
    printf("Printing the sorted array:\n");
    for (int i = 0; i < n; i++){
        printf("%f \n", input[i]);
    }
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Delta = %f \n",delta); 
    return 0;
    //return input;
}






//Code for merge sort

// void merge(int *, int *, int, int, int);
// void mergeSort(int *, int *, int, int);
// void array_gen();
// int main(int argc, char** argv) {
// int world_rank;
// 	int world_size;
	
// 	MPI_Init(&argc, &argv);
// 	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
// 	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		
// 	/********** Divide the array in equal-sized chunks **********/
// 	int size = n/world_size;
	
// 	/********** Send each subarray to each process **********/
// 	int *sub_array = malloc(size * sizeof(int));
// 	MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
	
// 	/********** Perform the mergesort on each process **********/
// 	int *tmp_array = malloc(size * sizeof(int));
// 	mergeSort(sub_array, tmp_array, 0, (size - 1));
	
// 	/********** Gather the sorted subarrays into one **********/
// 	int *sorted = NULL;
// 	if(world_rank == 0) {
		
// 		sorted = malloc(n * sizeof(int));
		
// 		}
	
// 	MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
	
// 	/********** Make the final mergeSort call **********/
// 	if(world_rank == 0) {
		
// 		int *other_array = malloc(n * sizeof(int));
// 		mergeSort(sorted, other_array, 0, (n - 1));
		
// 		/********** Display the sorted array **********/
// 		printf("This is the sorted array: ");
// 		for(c = 0; c < n; c++) {
			
// 			printf("%d ", sorted[c]);
			
// 			}
			
// 		//printf("\n");
// 		printf("\n");
			
// 		/********** Clean up root **********/
// 		free(sorted);
// 		free(other_array);
			
// 		}
	
// 	/********** Clean up rest **********/
// 	free(original_array);
// 	free(sub_array);
// 	free(tmp_array);
	
// 	/********** Finalize MPI **********/
// 	MPI_Barrier(MPI_COMM_WORLD);
// 	MPI_Finalize();
	
// }

// /********** Merge Function **********/
// void merge(int *a, int *b, int l, int m, int r) {
	
// 	int h, i, j, k;
// 	h = l;
// 	i = l;
// 	j = m + 1;
	
// 	while((h <= m) && (j <= r)) {
		
// 		if(a[h] <= a[j]) {
			
// 			b[i] = a[h];
// 			h++;
			
// 			}
			
// 		else {
			
// 			b[i] = a[j];
// 			j++;
			
// 			}
			
// 		i++;
		
// 		}
		
// 	if(m < h) {
		
// 		for(k = j; k <= r; k++) {
			
// 			b[i] = a[k];
// 			i++;
			
// 			}
			
// 		}
		
// 	else {
		
// 		for(k = h; k <= m; k++) {
			
// 			b[i] = a[k];
// 			i++;
			
// 			}
			
// 		}
		
// 	for(k = l; k <= r; k++) {
		
// 		a[k] = b[k];
		
// 		}
		
// }

// /********** Recursive Merge Function **********/
// void mergeSort(int *a, int *b, int l, int r) {
	
// 	int m;
	
// 	if(l < r) {
		
// 		m = (l + r)/2;
		
// 		mergeSort(a, b, l, m);
// 		mergeSort(a, b, (m + 1), r);
// 		merge(a, b, l, m, r);
		
// 		}
		
// }