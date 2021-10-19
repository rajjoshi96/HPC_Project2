// This code runs perfectly fine for the first two questions of Project 2
// Change the LEN to higher values



#include<stdio.h>
#include<stdlib.h>
#define LEN 5

struct foo {
  double a;
};

int main( ) {
    struct foo array[LEN];
    //        arr[i] = ((double)rand()/(double)(RAND_MAX)) * a;
    float t=10.0;
    // fill it
    for ( int i = 0 ; i < LEN ; i++ ) {
        array[i].a =((double)rand()/(double)(RAND_MAX)) * t;
    }

    // write it
    FILE *fp = fopen("testfile1.bin","wb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fwrite(&array[i].a,sizeof(array[i].a),1,fp);
    }

    // Same again, but write a whole struct instance at once
    fp = fopen("unsorted_array.bin","wb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fwrite(&array[i],sizeof(array[i]),1,fp);
    }
    fclose(fp);
    
    struct foo input[LEN];
    
    // read it
    fp = fopen("unsorted_array.bin","rb");
    for ( int i = 0 ; i < LEN ; i++ ) {
        fread(&input[i],sizeof(input[i]),1,fp);
    }
    fclose(fp);
    
    // print it
    for ( int i = 0 ; i < LEN ; i++ ) {
        printf("Value at index %d is %f\n", i, input[i].a);
    }
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