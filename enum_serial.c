#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 10000

int main()
{
	int i,j;
	int list[MAX],rank_list[10000] = {0},sort_list[10000] = {0};

	int a = 10;
	for(i=0; i<MAX; i++)
		list[i] = ((int)rand()/(int)(RAND_MAX)) * a;


	for(i=0; i<MAX; i++)
	{
		for(j=0; j<i; j++)
		{
			if(list[i] >= list[j])
				rank_list[i]++;
			else
				rank_list[j]++;
		}	
	}	

	printf("\nRank for each item in the unsorted list\n");
	printf("\n\tElement\tRank\n");
	for(i=0; i<MAX; i++)
		printf("\t%d \t%d\n",list[i],rank_list[i]+1);
	

	for(i=0; i<MAX; i++)
		sort_list[(int)rank_list[i]] = list[i];

	printf("\nSorted listed according to the rank\n\t");
	for(i=0; i<MAX; i++)
		printf("%d \n",sort_list[i]);
	printf("\n");			
	return 0;
}