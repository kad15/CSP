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

int main(int argc, char** argv) {
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);
 // ou   MPI_Init(&argc, &argv);

double ti = MPI_Wtime();
 sleep(1);
 
  // This function indicates the number of processes involved in a communicator. 
  //For MPI_COMM_WORLD, it indicates the total number of processes available
  int nb_total_of_proc;
  MPI_Comm_size(MPI_COMM_WORLD, &nb_total_of_proc);

  // rang du processus dans le groupe "world"
  int rang;
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);

  // nom du processus
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

 double tf = MPI_Wtime();
 printf("MPI_Wtime measured a 1 second sleep to be: %f\n", tf-ti);
  // Print off a hello world message
  printf("Hello du processus %s, mon rang est %d sur un total de %d. Mon temps d''execution est %f secondes\n", processor_name, rang, nb_total_of_proc, tf-ti);//fflush(stdout);

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
