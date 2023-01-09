#include <mpi/mpi.h>
#include <stdio.h>
/*
Écrire un programme MPI dans lequel le processus 0 lit une donnée insérée par l'utilisateur et
la transmet à tous les autres processus en l'envoyant dans un anneau. Autrement dit, le processus i
devrait recevoir la donnée à partir du processus i - 1 et l'envoyer au processus i + 1, jusqu'à ce
que le dernier processus soit atteint.
*/
int main(int argc,char* argv[]){

    MPI_Init(&argc,&argv);
    int rank;
    int data;
    int nb_proc;
    
    //get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    //get the rank of the process
    MPI_Comm_rank (MPI_COMM_WORLD,&rank);

    if(rank==0){
        scanf("%d",&data);//get data from the user
        MPI_Send((void*)&data,1,MPI_INT,rank+1,1,MPI_COMM_WORLD);
    }
    
    if(rank>0 &&rank<nb_proc-1){
        int local_data;
        MPI_Recv((void*)&local_data,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,NULL);
        
        printf("process number : %d\n",rank);
        printf("Information received %d\n",local_data);

        MPI_Send((void*)&local_data,1,MPI_INT,rank+1,1,MPI_COMM_WORLD);

        
    }

    if(rank==nb_proc-1){
        int local_data;
        MPI_Recv((void*)&local_data,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,NULL);
        printf("process number : %d\n",rank);
        printf("Information received %d\n",local_data);
        
    }
    
   
    MPI_Finalize();
    

}