#include <stdio.h>
#include <mpi/mpi.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535L
double f(double a)
{
    return (double)4.0 / ((double)1.0 + (a * a));
}
int main()
{
    //every process is created before the lauch of the program so every variable here is considered local to
    //its own process
    int n, i;
    double h, pi=0, sum, x, pi_local;
    int rank;
    int nb_process;
    // init for MPI
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank==0){//first we need for just one process to read n and send it to others otherwise we will have 4 scanf
        printf("Enter the number of intervals:(0 quits )");
        scanf("%d", &n);
    }
    //if it's root=0 it will send else it will receive
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    
    // début de la methode

    h = ((double)1.0) / (double)n; //(read only)
    

    sum = 0.0;                     // affected sum
    for (i = 1 + rank * n / nb_process; i <= (rank + 1) * n / nb_process; i++)
    {
        x = h * ((double)i - (double)0.5);
        sum += f(x);
        
    }
    pi_local = h * sum;


    MPI_Reduce(&pi_local,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    
    // fin de la methode
    if(rank==0)
        printf("PI is approximately: %.16f Error is: %.16f\n", pi, fabs(pi - PI));

    MPI_Finalize();
    
    return 0;
}
