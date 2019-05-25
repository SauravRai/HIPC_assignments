//The simple version of the Matrix _ multiplication:
//AUTHOR: SAURAV RAI
//REGD NO: 17558
#include<cuda.h>
#include<stdio.h>
#define BLOCKSIZE 32
void MatrixMultiplication(float *,float *,float *,int);

int main(int argc,char const*argv[]) {
        const int Width = atoi(argv[1]);
    float *M,*N,*P;
    int size = Width*Width*sizeof(float);
   
    cudaMallocHost((void **)&M,size);
    cudaMallocHost((void **)&N,size);
    cudaMallocHost((void **)&P,size);
    
     for(int i = 0; i < (Width*Width) ; i++)
        {
          M[i] = 1;
          N[i] = 1;
          P[i] = 0;
        }
  
    MatrixMultiplication(M, N, P, Width);
    for(int i = 0; i < (Width*Width) ; i++)
      {
        printf("%f \n", P[i]);
      }
    
   cudaFree(M);
   cudaFree(N);
   cudaFree(P);
    return 0;
}

//Matrix multiplication kernel - thread specification
__global__ void MatrixMulKernel(float *Md, float *Nd, float *Pd, int Width)
   {

    //2D Thread ID
    int column = blockIdx.x * BLOCKSIZE + threadIdx.x;
    int row = blockIdx.y * BLOCKSIZE +threadIdx.y;

    //Pvalue stores the Pd element that is computed by the thread
    float Pvalue = 0;

   if(row > Width || column > Width )
      return;
    else
     {  

        for (int k = 0; k < Width ; ++k) 
           {
              Pvalue +=  Md[row *Width + k] * Nd[k *Width + column];
           }
        
       Pd[ row*Width + column] = Pvalue;
    }
  }

void MatrixMultiplication(float *M, float *N, float *P, int Width) {
    int size = Width*Width*sizeof(float);
    float *Md, *Nd, *Pd;

    //Transfer M and N to device memory
    cudaMalloc((void**)&Md, size);
    cudaMemcpy(Md,M,size,cudaMemcpyHostToDevice);
    cudaMalloc((void**)&Nd, size);
    cudaMemcpy(Nd,N,size,cudaMemcpyHostToDevice);

    //Allocate P on the device
    cudaMalloc((void**)&Pd,size);
    unsigned int grid_rows = (Width + BLOCKSIZE -1 ) / BLOCKSIZE;
    unsigned int grid_cols = (Width + BLOCKSIZE -1 ) / BLOCKSIZE;	
     
 
    //Setup the execution configuration
    dim3 dimBlock(BLOCKSIZE,BLOCKSIZE);
    dim3 dimGrid( grid_rows , grid_cols);

    //Launch the device computation threads!
    MatrixMulKernel<<<dimGrid,dimBlock>>>(Md,Nd,Pd,Width);

    //Transfer P from device to host
    cudaMemcpy(P,Pd,size,cudaMemcpyDeviceToHost);

    //Free device matrices
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);

}
