#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>
#define SIZE 8


int main(int argc,char* argv[]){
    int size;
    int rank;
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int C[SIZE][SIZE];
    int C_row[SIZE];
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    //init the matrices A and B
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            A[i][j]=2*i;
            B[i][j]=i*i;
            C[i][j]=0;
        }
        C_row[i]=0;
    }

    for(int j=0;j<SIZE;j++){
        for(int k=0;k<SIZE;k++){
            C_row[j]+=A[rank][k]*B[k][j];
        }
    }

    MPI_Gather(C_row,SIZE,MPI_INT,&C[rank],SIZE,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0){
        printf("[");
        for(int i=0;i<size;i++){
            printf("[");
            for(int j=0;j<size;j++){
                printf("%d ,",C[i][j]);
            }
            printf("]\n");
        }
        printf("]");
    }

    MPI_Finalize();
}
