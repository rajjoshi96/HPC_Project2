#include <mpi.h>
#include <stdio.h>
#define N 16
int main(int argc, char **argv){
    int rank, num_of_process;
    MPI_File fh; //Declaring a File Pointer 
    MPI_Status status;
    MPI_Init(&argc, &argv); MPI_Comm_rank(MPI_COMM_WORLD, &rank); MPI_Comm_size(MPI_COMM_WORLD, &num_of_process); int ave_num_of_ints = N / num_of_process;
    int buf[ave_num_of_ints];
    int bufsize_byte = ave_num_of_ints * sizeof(int);
    MPI_File_open(MPI_COMM_WORLD,"matrix", MPI_MODE_RDONLY, MPI_INFO_NULL,&fh); //Combining File Seek & Read in One Step for Thread Safety
    MPI_File_read_at(fh, rank*bufsize_byte, buf, ave_num_of_ints, MPI_INT, &status);
    printf("\nrank: %d, buf[%d]: %d", rank); MPI_File_close(&fh); //Closing a File
    MPI_Finalize();
    return 0;
}