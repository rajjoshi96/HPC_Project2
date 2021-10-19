#include <mpi.h>
#include<stdio.h>
#include<stdlib.h>
#define FILENAME    "matrix.txt"
#define WIDTH       2
#define HEIGHT      6


int main() {

    int rank, world_size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);


    int matrix[HEIGHT][WIDTH];

    /**
     * The MASTER process reads the file
     */
    if (rank == 0) { 
        FILE *fp = fopen(FILENAME, "r");

        char line[100];
        int i = 0;
        while (fgets(line, 100, fp)) {
            sscanf(line, "%d %d", &matrix[i][0], &matrix[i][1]);
            i++;
        }
    }

    //Broadcast it to all processes
    MPI_Bcast(matrix, HEIGHT * WIDTH, MPI_INT, 0, MPI_COMM_WORLD);

    //just for demo purposes each process prints its array orderly
    int p = 0, i = 0, j = 0;
    for (p = 0; p < world_size; p++) {
        MPI_Barrier(MPI_COMM_WORLD);
        if (p == rank) {
            printf("----------\n proc:%d received:\n", rank);
            for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                    printf("%d\t", matrix[i][j]);
                }
                printf("\n");
            }
        }
    }


    MPI_Finalize();
    return 0;
}