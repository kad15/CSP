// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// An intro MPI hello world program that uses MPI_Init, MPI_Comm_size,
// MPI_Comm_rank, MPI_Finalize, and MPI_Get_processor_name.
//
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) 
{
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);
 // ou   MPI_Init(&argc, &argv);

double ti = MPI_Wtime();
 //sleep(1);
 
  // This function indicates the number of processes involved in a communicator. 
  //For MPI_COMM_WORLD, it indicates the total number of processes available
  int nb; //nb_total_of_proc;
  MPI_Comm_size(MPI_COMM_WORLD, &nb);
  if (nb < 2) printf("nombre de processeurs insuffisant : 2 au minimum.\n");
  // rang du processus dans le groupe "world"
  int rang;
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);

  // nom du processus
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

/* 
char buf[4096];
char *tmp;
int r;
char * mess = "message";
int rang=10;
sprintf(buf,"%s %d","message ", rang);
printf("buf = %s\n", buf);
sscanf(buf, "%s %d",&tmp, &r ); 
printf("le rang est %d\n", r);

//strcpy(buf, "toto");
//printf("%s\n", buf);

*/


char buf[4096];
char * mess = "rangProcessExpediteur = ";
//char *tmp;
//int r;

//MPI_Ssend(buf, 4096, MPI_BYTE, (rang + 1) % nb , 0, MPI_COMM_WORLD);
//sprintf(buf,"%s %d",mess, rang);
 
  // reception par le process n-1 et envoi au process n+1 
  if (rang != 0) {
    MPI_Recv(buf, 4096, MPI_BYTE, rang - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Le process %d a recu   %d du process %d\n", rang, buf, rang - 1);
    printf(buf," :  buf contient  %s\n",buf);
    sprintf(buf,"%s %d\n",mess, rang);
  } 
  else 
  {
    sprintf(buf,"%s %d\n",mess, rang);
  }

// envoi du message au pc (rang+1) module le nb de pc=10


  MPI_Ssend(buf, 4096, MPI_BYTE, (rang + 1)%nb , 0, MPI_COMM_WORLD);

  if (rang == 0) 
  {
    MPI_Recv(buf, 4096, MPI_BYTE, nb - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Le process %d a recu   %d du process %d\n", rang, buf, nb - 1);
    printf(buf," :  buf contient  %s\n",buf);
  }

 double tf = MPI_Wtime();


  printf("Hello du processus %s, mon rang est %d sur un total de %d. Mon temps d''execution est %f secondes\n", processor_name, rang, nb, tf-ti);
//fflush(stdout);

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();

}
