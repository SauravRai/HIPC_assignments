//THE SHARED MEMORY PROGRAM FOR MATRIX MULTIPLICATION 
//AUTHOR : SAURAV RAI
//REGD NO: 17558
#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>

#define blockD 32   

#define TILE_DIM 32   

  __global__ void MatrixMulKernel(float* , float* , float*,int );
 void MatrixMultiplication(float *, float *, float *,int );


 int main(int argc , const char * argv[])
    {

    const int Width = atoi(argv[1]);
    int size = Width *  Width * sizeof(float);
    
    float *M, *N, *P ;   

    // allocate memory on the CPU
    cudaMallocHost((void **)&M , size);
    cudaMallocHost((void **)&N , size);
    cudaMallocHost((void **)&P , size);
 
 

      // initialize the matrices
   for (int y=0; y < Width; y++)
     {
        for (int x=0; x < Width; x++)
         {
            M[y * Width  + x] = 1; //x + y*wA; 
         }
     }

    for (int y=0; y< Width; y++)
       {
        for (int x=0; x< Width; x++)
          {
             N[y * Width + x] = 1; //x + y*wB; 
          }
       }


    MatrixMultiplication(M, N, P, Width);
   
   for(int i = 0; i < Width * Width ; i++)
	{ 
          printf("%f\n",P[i]);
        } 

   // free the memory allocated on the CPU
    cudaFree( M );
    cudaFree( N );
    cudaFree( P ); 

    return 0;
  }





 __global__ void MatrixMulKernel(float* Md, float* Nd, float* Pd, int Width)
   
{
    float CValue = 0;
    int sum =0;
    int Row = blockIdx.y*TILE_DIM + threadIdx.y;
    int Col = blockIdx.x*TILE_DIM + threadIdx.x;

    __shared__ float Mds[TILE_DIM][TILE_DIM];
    __shared__ float Nds[TILE_DIM][TILE_DIM];

    for (int k = 0; k < (TILE_DIM + Width - 1)/TILE_DIM; k++) {

         if (k*TILE_DIM + threadIdx.x < Width  && Row < Width)
            Mds[threadIdx.y][threadIdx.x] = Md[Row * Width + k*TILE_DIM + threadIdx.x];
         else
             Mds[threadIdx.y][threadIdx.x] = 0.0;

         if (k*TILE_DIM + threadIdx.y < Width && Col < Width)
             Nds[threadIdx.y][threadIdx.x] = Nd[(k*TILE_DIM + threadIdx.y) * Width + Col];
         else
             Nds[threadIdx.y][threadIdx.x] = 0.0;

         __syncthreads();

         if(Row > Width || Col > Width)
           return;

         else
           {
            for (int n = 0; n < TILE_DIM; ++n)
             {
                sum += Mds[threadIdx.y][n] * Nds[n][threadIdx.x];
             }
           CValue = sum;
         __syncthreads();
    }

    if (Row < Width && Col < Width)
        Pd[((blockIdx.y * blockDim.y + threadIdx.y)*Width) +  (blockIdx.x * blockDim.x)+ threadIdx.x] = CValue;
    }
 }





void MatrixMultiplication(float *M, float *N, float *P, int Width)
   {
   int size = Width * Width * sizeof(float);
	   // int size_max = 2 * Width * sizeof(float);
    float *Md, *Nd, *Pd ; 

    // allocate memory on the GPU
    cudaMalloc((void**)&Md, size);
    cudaMalloc((void**)&Nd, size);
    cudaMalloc((void**)&Pd, size);

    // transfer M and N to device memory
    cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
    cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);

    unsigned int grid_rows= (Width + blockD-1)/blockD ;
    unsigned int grid_cols= (Width + blockD -1)/blockD;
 
   // kernel invocation code
    dim3 dimBlock(blockD, blockD);
    dim3 dimGrid( grid_rows,grid_cols);

    //Execute Kernel
    MatrixMulKernel<<<dimGrid, dimBlock>>>( Md, Nd, Pd, Width);

    // transfer P from device    
    
    cudaMemcpy(P,Pd, size,cudaMemcpyDeviceToHost);

    // free the memory allocated on the GPU
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);
    }
