//This code runs perfectly for quick sort
// very large number ArraySize = 100000 

//please don't change anything 

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define  TRUE 1
#include "math.h"
#include <time.h>
#include<sys/time.h>
#define Size 10000
int IncOrder(const void *e1, const void *e2 )
{
    return (*((int *)e1) - *((int *)e2));
}

void DisplayError(char *str)
{
    printf("Error: %s \n",str);
}

int Partition(float *arr, int left, int right) 
{
    int i = left, j = right;
    float tmp;
    int pivot = arr[(left + right) / 2];
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
        i++;
        while (arr[j] > pivot)
        j--;
        if (i <= j) 
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    return j;
}

int PowerOf2(int num)
{
    int i;

    i=1;

    while(num>0)
    {
        num--;
        i=i*2;
    }

    return i;
}


int PQuickSort(float *Array,int start,int end,int m,int id,int MyRank)
{
    int j;
    int r;
    int LocalLength;
    float *tmp;
    //int newsize;
    MPI_Status status;
    LocalLength=-1;

    if(m==0)
    {
        if(MyRank==id)

        qsort(Array, end-start, sizeof *Array, IncOrder);
        return 0;
    }

if(MyRank==id)
{
    r=Partition(Array,start,end);
    LocalLength=end-r;
    MPI_Send(&LocalLength,1,MPI_INT,id+PowerOf2(m-1),MyRank,MPI_COMM_WORLD);

    if(LocalLength!=0)

    MPI_Send(Array+r+1,LocalLength,MPI_INT,id+PowerOf2(m-1),MyRank,MPI_COMM_WORLD);
}

    if(MyRank==id+PowerOf2(m-1))
    {
        MPI_Recv(&LocalLength,1,MPI_INT,id,id,MPI_COMM_WORLD,&status);

       if(LocalLength!=0)
        {
             tmp=(float *)malloc(LocalLength*sizeof(float));
             if(tmp==0)
                DisplayError("Malloc memory error!");

MPI_Recv(tmp,LocalLength,MPI_INT,id,id,MPI_COMM_WORLD,&status);
        }
    }

    j=r-1-start;
    MPI_Bcast(&j,1,MPI_INT,id,MPI_COMM_WORLD);
    if(j>0)
        PQuickSort(Array,start,r-1,m-1,id,MyRank);

    j=LocalLength;
    MPI_Bcast(&j,1,MPI_INT,id,MPI_COMM_WORLD);
    if(j>0)
        PQuickSort(tmp,0,LocalLength-1,m-1,id+PowerOf2(m-1),MyRank);

    if((MyRank==id+PowerOf2(m-1)) && (LocalLength!=0))

MPI_Send(tmp,LocalLength,MPI_INT,id,id+PowerOf2(m-1),MPI_COMM_WORLD);

    if((MyRank==id) && (LocalLength!=0))
        MPI_Recv(Array+r+1,LocalLength,MPI_INT,id+PowerOf2(m-1),id+PowerOf2(m-1),MPI_COMM_WORLD,&status);

}

int LogBase2(int num)
{
    int i, j;

    i=1;
    j=2;

    while(j<num)
    {
        j=j*2;
        i++;
    }

    if(j>num)
        i--;

    return i;
}


int main(int argc,char *argv[])
{
    int ArraySize=Size;
    float *Array;
    int MyRank, npes;
    int i;
    int m ;
    float t1,t2,t3;
    srand((unsigned int)time(NULL));
    struct timeval start, end;
    gettimeofday(&start, NULL);
    float store_time[8];
    float array[Size]={};
    float t=10.0;

    //MPI_Status status;
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    MPI_Comm_size(MPI_COMM_WORLD,&npes);

    //if(MyRank==0)
    //{
        // ArraySize=10000;
        // //printf("%d\n",ArraySize);
        // Array=(int *)malloc(ArraySize*sizeof(int));

        // if(Array==0)
        //     printf("Malloc memory error!");

        // srand(396);
        // for(i=0;i<ArraySize;i++)
        // {
        //     Array[i]=(int)rand()%ArraySize;
        // }
        // printf("\n");
    for ( int i = 0 ; i < Size ; i++ ) 
    {
        array[i] =((float)rand()/(float)(RAND_MAX)) * t;
    }

    // write it
    FILE *fp = fopen("testfile1.bin","wb");
    for ( int i = 0 ; i < Size ; i++ ) 
    {
        fwrite(&array[i],sizeof(array[i]),1,fp);
    }

    fp = fopen("unsorted_array.bin","wb");
    for ( int i = 0 ; i < Size ; i++ ) {
        fwrite(&array[i],sizeof(array[i]),1,fp);
    }
    fclose(fp);
        
    float input[Size]={};
        // read it
    fp = fopen("unsorted_array.bin","rb");
    for ( int i = 0 ; i < Size ; i++ ) {
        fread(&input[i],sizeof(input[i]),1,fp);
    }
    fclose(fp);
    //}
    for(int i=0; i<Size;i++)
    {
        printf("%f \n", input[i]);
    }
    m=LogBase2(npes);

    MPI_Bcast(&ArraySize,1,MPI_INT,0,MPI_COMM_WORLD);//&arraysize
        t1=MPI_Wtime();
    PQuickSort(input,0,Size-1,m,0,MyRank);//arraysize
        t2=MPI_Wtime();
        t3=t2-t1;

    if(MyRank==0)
    {
        for(i=0;i<Size-1;i++)
        {
            printf("%10f \n",Array[i]);
        }
        // printf("\n");
    printf("MPI_time :%6.3f\n",t3);

    }
    // gettimeofday(&end, NULL);
    // float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    // printf("Delta = %f \n",delta); 
    MPI_Finalize();
    return 0;
}