// #include "mpi.h"
// #include<stdio.h>
// #include<string.h>
// int main(int argc,char *argv[]){
//     MPI_Init(&argc,&argv);
//     int rank,size,tag=99;
//     MPI_Status status;
//     char msg[20];
//     MPI_Comm_rank(MPI_COMM_WORLD,&rank);
//     if(rank==0){
//         strcpy(msg,"KNOCK KNOCK");
//         MPI_Send(msg,strlen(msg)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);
//         printf("I am process %d sending \"%s\" to process 1. Over!\n", rank, msg);
//     }
//     else if(rank==1){
//         MPI_Recv(msg,20,MPI_CHAR,0,tag,MPI_COMM_WORLD,&status);
//         printf("I am process %d receiving \"%s\". Over!\n", rank, msg);
//     }
//     MPI_Finalize();
//     return 0;

// }





//Teachers program


#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    char msg[20];
    int myrank, tag = 99;
    MPI_Status status; MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 
    if(myrank == 0){
        strcpy(msg, "Knock knock");
        MPI_Send(msg, strlen(msg)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD); printf("I am process %d sending \"%s\" to process 1. Over!\n", myrank, msg);
    }
    else if (myrank == 1){
        MPI_Recv(msg, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status); printf("I am process %d receiving \"%s\". Over!\n", myrank, msg);
    }
    MPI_Finalize();
    return 0;
}



// How to execute the program:

//     1. mpicc -o helloword helloworld.
//     2. mpirun -n 4 helloworld