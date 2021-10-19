


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Size 10
int main()
{
    float a = 10.0;
    double arr[Size] = {};
    double array_store[Size]={};
    for (int i=0;i<Size;i++)
    {
        arr[i] = ((double)rand()/(double)(RAND_MAX)) * a;
    }
    for(int i = 0;i<Size;i++)
    {
        printf("%f \n",arr[i]);
    }
    size_t num;
    FILE *write_ptr;
    double buffer[Size];
    write_ptr = fopen("unsorted_array.bin","wb");  // w for write, b for binary

    fwrite(&buffer,sizeof(buffer),1,write_ptr);

    fclose(write_ptr);
    printf("File write is complete\n");
    FILE *ptr;
    double are[Size];
    ptr = fopen("unsorted_array.bin","rb");  // r for read, b for binary
    num = fread(are[Size],sizeof(are),1,ptr);
    printf("%f: ",num);
    // for(int i=0;i<Size;i++)
    // {
    //         printf("%f \n",array_store[i]);
    // }
    fclose(ptr);
}