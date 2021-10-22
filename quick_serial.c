// To submit serial program


///quick sort using pivot as the last element 


#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/time.h>
#define Size 10

// Swap function
void swap(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

// Making n partition(splits) based on the pivot element
int partition (float arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// initial partition function to call sorting and partition function
void quickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//function to print array
void printArray(float arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
    printf("%f \n", arr[i]);
}
int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));
    struct timeval start, end;
    gettimeofday(&start, NULL);
    double store_time[8];
    float a = 10.0;
    float arr[Size] = {};
    // for (int i=0;i<Size;i++)
    // {
    //     arr[i] = ((float)rand()/(float)(RAND_MAX)) * a;
    // }
    double array[Size]={};
    float t=10.0;
    for ( int i = 0 ; i < Size ; i++ ) {
        array[i] =((double)rand()/(double)(RAND_MAX)) * t;
    }

    // write it
    FILE *fp = fopen("testfile1.bin","wb");
    // for ( int i = 0 ; i < Size ; i++ ) {
    //     fwrite(&array[i],sizeof(array[i]),1,fp);
    // }

    // fp = fopen("unsorted_array.bin","wb");
    for ( int i = 0 ; i < Size ; i++ ) {
        fwrite(&array[i],sizeof(array[i]),1,fp);
    }
    fclose(fp);
    float input[Size]={};
    fp = fopen("unsorted_array.bin","rb");
    for ( int i = 0 ; i < Size ; i++ ) {
        fread(&input[i],sizeof(input[i]),1,fp);
    }
    fclose(fp);
    quickSort(input, 0, Size-1);
    printf("The sorted array is: ");
    printArray(input, Size);
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Delta = %f \n",delta);  

    return 0;
}