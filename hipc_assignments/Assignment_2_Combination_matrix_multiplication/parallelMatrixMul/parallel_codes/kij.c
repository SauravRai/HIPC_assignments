//The Parrallel version of Matrix Multiplication

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void kij(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{
	clock_t c_1, c_2;
	float t_1;
	int i,j,k,res1[m1][n2];
	c_1=time(NULL);  // time measure: start mm
	
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
			res1[i][j]=0;
	#pragma omp parallel for private(i,j)
	for(k=0;k<n1;k++)
		for(i=0;i<m1;i++)
		{
			for(j=0;j<n2;j++)
				res1[i][j]+=mat1[i][k]*mat2[k][j];
		}
	printf("The result is:\n");
	for(i=0;i<m1;i++){
		for(j=0;j<n2;j++)
			printf("%d	",res1[i][j]);
		printf("\n");
	}
	
	/* TIME MEASURE + OUTPUT */
 c_2=time(NULL);  // time measure: end mm
 t_1 = (float)(c_2-c_1); // time elapsed for job row-wise
 printf("Execution time for ijk: %f \n",t_1);
}


int main ()
{
/* DECLARING VARIABLES */
int i, j; // indices for matrix multiplication


printf("Max number of threads: %i \n",omp_get_max_threads());
#pragma omp parallel
printf("Number of threads: %i \n",omp_get_num_threads());
	
	int m1,n1,m2,n2;
	printf("Enter the number of rows and columns for first matrix: \n");
	scanf("%d",&m1);
	scanf("%d",&n1);
	printf("Enter the number of rows and columns for second matrix: \n");
	scanf("%d",&m2);
	scanf("%d",&n2);
	if(n1!=m2)
	{
		printf("Error\n");
		return(0);
	}
	int mat1[m1][n1],mat2[m2][n2];
	printf("Enter the first matrix values: \n");
	for(i=0;i<m1;i++)
		for(j=0;j<n1;j++)
			scanf("%d",&mat1[i][j]);
	printf("Enter the second matrix values: \n");
	for(i=0;i<m2;i++)
		for(j=0;j<n2;j++)
			scanf("%d",&mat2[i][j]);
			kij(m1,n1,m2,n2,mat1,mat2);
		return 0;
		}
