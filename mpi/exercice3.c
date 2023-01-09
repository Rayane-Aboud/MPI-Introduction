#include <stdio.h>
#include <mpi/mpi.h>
#include <stdlib.h>
#define MAT_SIZE 4

int main(int argc,char* argv[]){
    int rank;
    int nb_process;
    //all processes have A and y as NULL
    int* A=NULL;
    int* y=NULL;
    int* A_row=NULL;
    int* X=NULL;
    X = (int*) malloc (MAT_SIZE*sizeof(int));

    for (int i=0; i<MAT_SIZE; i++)
       X[i] = i+1;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&nb_process);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0){
        A=(int*)malloc(sizeof(int)*MAT_SIZE*MAT_SIZE);
        y=(int*)malloc(sizeof(int)*MAT_SIZE);
        
        //filling the matrix with random values
        for(int i=0;i<MAT_SIZE*MAT_SIZE;i++){
            A[i]=i*i;
        }
        for(int i=0;i<MAT_SIZE;i++){
            y[i]=0;
        }
        
    }
    A_row = (int*) malloc (MAT_SIZE*sizeof(int));
    MPI_Scatter(A,MAT_SIZE,MPI_INT,A_row,MAT_SIZE,MPI_INT,0,MPI_COMM_WORLD);
    int local_mult=0;
    for(int i=0;i<MAT_SIZE;i++){
        local_mult=local_mult+A_row[i]*X[i];
    }

    MPI_Gather(&local_mult,1,MPI_INT,&y[rank],1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0){
        for (int i=0;i<MAT_SIZE;i++){
            printf("%d\n",y[i]);
            
        }
        //for the process 0 who allocated it
        free(A);
        free(y);
    }
    //for all process
    free(A_row);
    free(X);
    MPI_Finalize();
    return 0;
}