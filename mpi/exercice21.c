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
        for(int i=1;i<nb_process;i++){
            MPI_Send(&n,1,MPI_INT,i,1,MPI_COMM_WORLD);
        }
    }else{
        MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,NULL);
    }
    
    
    // début de la methode

    h = ((double)1.0) / (double)n; //(read only)
    

    sum = 0.0;                     // affected sum
    for (i = 1 + rank * n / nb_process; i <= (rank + 1) * n / nb_process; i++)
    {
        x = h * ((double)i - (double)0.5);
        sum += f(x);
        
    }
    pi_local = h * sum;
    if (rank == 0)
    {
        double *pi_table = (double *)malloc(sizeof(double) * nb_process);
        pi_table[0] = pi_local;
        for (int i = 1; i < nb_process; i++)
        {
            MPI_Recv(&pi_table[i], 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD,NULL);
        }

        
        for (int i = 0; i < nb_process; i++)
        {
            pi += pi_table[i];
        }
        
    }
    else
    {
        MPI_Send(&pi_local, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
    // fin de la methode
    if(rank==0)
        printf("PI is approximately: %.16f Error is: %.16f\n", pi, fabs(pi - PI));

    MPI_Finalize();
    
    return 0;
}