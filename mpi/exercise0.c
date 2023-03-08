#include <mpi/mpi.h>
#include <stdio.h>
/*
    MPI_COMM_WORLD : un des communicateurs entre processus
    MPI_Init (&argc, &argv) : initialise l'envitronnement + communicateur
    MPI_Finalize () : désactjve MPI
    int MPI_Comm_size (MPI_Comm comm, int *size):retourne dans size taille de communicateur ,retourne nb processus formant le communicateur
    MPI_Comm_rank (MPI_Comm comm, int *rank) : rank<- rang de proc appelant
    int MPI_Wtime (): temps ecoulé sur le processus appelant
    ---------------------------------------------------------------------------------------------------------------------------------------------------
    int MPI_send(void* buf, //pointer to l'espace memoire à envoyer (théoriquement un tableau)
             int count, //nombre de valeur (taille de ce tableau)
             MPI_Datatype datatype,//type de tableau
             int dest,//numéro de processus destinataire
             int tag,//id du message
             MPI_Comm comm //communicateur considéré
             )<----bloquante

    int MPI_Resv(
        void *buf,//pointer to data (tableau)
        int count,//taille du tableau
        MPI_Datatype datatype,//type du tableau
        int source,//numero de processus envoyeur could be 'MPI_ANY_SOURCE'
        int tag,//id du message could be MPI_ANY_TAG
        MPI_Comm comm,//communicateur 
        MPI_Status *ptr_status//status.MPI_TAG:valeur de tag,status.MPI_SOURCE:numero du processus envoyant :this is used in the case of MPI_ANY_SOURCE,MPI_ANY_TAG
    )<-- bloquante
    ---------------------------------------------------------------------------------------------------------------------------------------------------
    MPI_Isend(
        void* buf,
        int count,
        MPI_Datatype datatype,
        int dest,
        int tag,
        MPI_Comm comm,
        MPI_Request *request, //id de la requete
    )//non bloquante : Retourne avant que le buffer de réception ne soit rempli

    int MPI_Irecv(
        void *buf,
        int count,
        MPI_Datatype datatype,
        int source,
        int tag,
        MPI_Comm comm,
        MPI_Request *request
    )
    
    int MPI_Wait (MPI_Request *request, MPI_Status *status)//did the message that i sent arrived yet if no I block


    MPI_Isend (&buf, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &request);
    Instruction 1;
    Instruction 2;
    ...
    Instruction N;
    MPI_Wait (&request, &status);

    ---------------------------------------------------------------------------------------------------------------------------------------------------

    int MPI_Bcast(
        void* buf,
        int count,
        MPI_Datatype datatype,
        int root,   //num de proc envayant
        MPI_Comm comm   
    )<--- it's a send receive function which means any process that is not root knows that he must receive

    ---------------------------------------------------------------------------------------------------------------------------------------------------
    int MPI_Scatter (
        void *sendbuf,  //tableau initiale à diviser
        int sendcount,  //taille du tabeau initiale
        MPI_Datatype sendtype, 
        void *recvbuf,  //tableau après division
        int recvcount,  //taille du tableau après division
        MPI_Datatype recvtype,
        int root, //sender
        MPI_Comm comm
        
    )<---goal is to send parts of a buffer and devide and give each part to process

    int MPI_Gather (

        void *sendbuf,
        int sendcount, 
        MPI_Datatype sendtype,
        void *recvbuf,
        int recvcount,
        MPI_Datatype recvtype,
        int root, 
        MPI_Comm comm
        
    )<--goal is to send data from multiple process to one table

    
    int MPI_Reduce (
        void *local_buf,
        void *global_buf,//which we find it in proc 0 
        int count, //longueur du message
        MPI_Datatype datatype,
        MPI_Op operation,//MPI_MAX,MPI_MIN,MPI_SUM,MPI_PROD,MPI_LANDMPI_LOR,MPI_LXOR
        int root, 
        MPI_Comm comm
        )<--send with operation

    
    ---------------------------------------------------------------------------------------------------------------------------------------------------

    MPI_Barrier (MPI_COM_WORLD)//synchronisation globale

    ---------------------------------------------------------------------------------------------------------------------------------------------------
    MPI_Comm_split (
        MPI_Comm comm,
        int color, 
        int key, 
        MPI_comm *newcomm
        )<-- division du communicateur
 
*/
int main(int argc,char* argv[]){

    MPI_Init(&argc,&argv);
    printf("Hello world");
    MPI_Finalize();

}
