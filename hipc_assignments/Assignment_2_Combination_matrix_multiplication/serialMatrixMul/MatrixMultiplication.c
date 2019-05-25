#include<stdio.h>
#include<stdlib.h>
void ijk(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{
	int i,j,k,res1[m1][n2],r=0;
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
			res1[i][j]=0;
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
		{
			r=0;
			for(k=0;k<n1;k++)
				r+=mat1[i][k]*mat2[k][j];
			res1[i][j]=r;
		}
	printf("The result is:\n");
	for(i=0;i<m1;i++){
		for(j=0;j<n2;j++)
			printf("%d	",res1[i][j]);
		printf("\n");
	}
}

void ikj(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{

	int i,j,k,res1[m1][n2];
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
			res1[i][j]=0;
	for(i=0;i<m1;i++)
		for(k=0;k<n1;k++)
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
}

void jki(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{
	int i,j,k,res1[m1][n2];
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
			res1[i][j]=0;
	for(j=0;j<n2;j++)
		for(k=0;k<n1;k++)
		{
			for(i=0;i<m1;i++)
				res1[i][j]+=mat1[i][k]*mat2[k][j];
		}
	printf("The result is:\n");
	for(i=0;i<m1;i++){
		for(j=0;j<n2;j++)
			printf("%d	",res1[i][j]);
		printf("\n");
	}

}

void jik(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{
	int i,j,k,res[m1][n2],r=0;
	for(j=0;j<n2;j++)
		for(i=0;i<m1;i++)
		{
			r=0;
			for(k=0;k<n1;k++)
				r+=mat1[i][k]*mat2[k][j];
			res[i][j]=r;
		}
	printf("The result is:\n");
	for(i=0;i<m1;i++){
		for(j=0;j<n2;j++)
			printf("%d	",res[i][j]);
		printf("\n");
	}

}

void kij(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{
	int i,j,k,res1[m1][n2];
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
			res1[i][j]=0;
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
}

void kji(int m1,int n1, int m2, int n2, int mat1[m1][n1], int mat2[m2][n2])
{
	int i,j,k,res1[m1][n2];
	for(i=0;i<m1;i++)
		for(j=0;j<n2;j++)
			res1[i][j]=0;
	for(k=0;k<n1;k++)
		for(j=0;j<n2;j++)
		{
			for(i=0;i<m1;i++)
				res1[i][j]+=mat1[i][k]*mat2[k][j];
		}
	printf("The result is:\n");
	for(i=0;i<m1;i++){
		for(j=0;j<n2;j++)
			printf("%d	",res1[i][j]);
		printf("\n");
	}
}

int main()
{
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
	int mat1[m1][n1],mat2[m2][n2],i,j;
	printf("Enter the first matrix values: \n");
	for(i=0;i<m1;i++)
		for(j=0;j<n1;j++)
			scanf("%d",&mat1[i][j]);
	printf("Enter the second matrix values: \n");
	for(i=0;i<m2;i++)
		for(j=0;j<n2;j++)
			scanf("%d",&mat2[i][j]);
	ijk(m1,n1,m2,n2,mat1,mat2);
	ikj(m1,n1,m2,n2,mat1,mat2);
	jki(m1,n1,m2,n2,mat1,mat2);
	jik(m1,n1,m2,n2,mat1,mat2);
	kij(m1,n1,m2,n2,mat1,mat2);
	kji(m1,n1,m2,n2,mat1,mat2);
}
