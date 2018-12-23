#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#include <string.h>


#define MAX_SIZE 40
#define LOGIN_SIZE 9   /* les chaînes sont AZT donc il vaut mieux un caractère de plus... */
#define BUFFER_LEN 256
#define ODD 666
#define EVEN 667

typedef struct { 
  char login[LOGIN_SIZE];
  int uid;
  int gid;
  char name[MAX_SIZE];
} identifiant_t;

MPI_Datatype MPI_IDENTIFIANT_T;
int my_id, nb_proc;

void affiche(identifiant_t tab[], int nb)
{
  int i;

  for(i=0 ; i<nb ; i++)
    printf("%s %d %d %s\n",
	   tab[i].login,
	   tab[i].uid, 
	   tab[i].gid,
	   tab[i].name);
}

void affiche_local(int tag,identifiant_t tab[], int nb)
{
  int i;
  
  printf("\t P%d, étape %d\t", my_id,tag);
  for(i=0 ; i<nb; i++)
    printf("%d ",tab[i].uid);
  printf("\n");
  fflush(stdout);
}

int compare_uid(const void *a, const void *b)
{
  if(((identifiant_t *)a)->uid < ((identifiant_t *)b)->uid) return -1;
  else if(((identifiant_t *)a)->uid ==((identifiant_t *)b)->uid) return 0;
  else return 1;
}

void begin_odd(identifiant_t *tab, int taille)
{
  MPI_Status status;

  if(my_id%2==1) { if(my_id!=nb_proc-1)
    MPI_Recv(tab+taille,taille,MPI_IDENTIFIANT_T,my_id+1,ODD,MPI_COMM_WORLD,&status); }
  else { if(my_id!=0)
    MPI_Send(tab,taille,MPI_IDENTIFIANT_T,my_id-1,ODD,MPI_COMM_WORLD); }
}

void begin_even(identifiant_t *tab, int taille)
{
  MPI_Status status;

  if(my_id%2==0) { if(my_id!=nb_proc-1)
    MPI_Recv(tab+taille,taille,MPI_IDENTIFIANT_T,my_id+1,EVEN,MPI_COMM_WORLD,&status); }
  else { if(my_id!=0)
    MPI_Send(tab,taille,MPI_IDENTIFIANT_T,my_id-1,EVEN,MPI_COMM_WORLD); }
}

void end_odd(identifiant_t *tab, int taille)
{
  MPI_Status status;

  if(my_id%2==1) { if(my_id!=nb_proc-1)
    MPI_Send(tab+taille,taille,MPI_IDENTIFIANT_T,my_id+1,ODD,MPI_COMM_WORLD); }
  else { if(my_id!=0)
    MPI_Recv(tab,taille,MPI_IDENTIFIANT_T,my_id-1,ODD,MPI_COMM_WORLD,&status); }
}

void end_even(identifiant_t *tab, int taille)
{
  MPI_Status status;

  if(my_id%2==0) { if(my_id!=nb_proc-1)
    MPI_Send(tab+taille,taille,MPI_IDENTIFIANT_T,my_id+1,EVEN,MPI_COMM_WORLD); }
  else { if(my_id!=0)
    MPI_Recv(tab,taille,MPI_IDENTIFIANT_T,my_id-1,EVEN,MPI_COMM_WORLD,&status); }
}

void odd_even(identifiant_t *tab, int taille)
{
  int i;
  MPI_Barrier(MPI_COMM_WORLD);

/*    printf("\n"); */
  for(i=0; i<nb_proc ; i++) {
    if(i%2==1) { /* impaire */
      begin_odd(tab,taille);
      if((my_id%2==1)&&(my_id!=nb_proc-1)) qsort(tab,2*taille,sizeof(identifiant_t),compare_uid) ;
      end_odd(tab,taille);
    } else {     /*  paire  */
      begin_even(tab,taille);
      if((my_id%2==0)&&(my_id!=nb_proc-1)) qsort(tab,2*taille,sizeof(identifiant_t),compare_uid) ;
      end_even(tab,taille);
    }
/*      affiche_local(i,tab,taille); */
  }
}

void mpi_types_initialize()
{
  int count=4;
  int struct_length[4]= {LOGIN_SIZE, 1, 1, MAX_SIZE};
  MPI_Aint struct_offset[4];
  MPI_Datatype struct_types[4];
  identifiant_t id;
  int i;
  
  MPI_Address( &id.login, &struct_offset[0]) ;
  MPI_Address( &id.uid,   &struct_offset[1]) ;
  MPI_Address( &id.gid,   &struct_offset[2]) ;
  MPI_Address( &id.name,  &struct_offset[3]) ;
  
  struct_types[0] = MPI_CHAR ; 
  struct_types[1] = MPI_INT  ;
  struct_types[2] = MPI_INT  ; 
  struct_types[3] = MPI_CHAR  ; 
  
  for(i=3 ; i>=0 ; i--) {
    struct_offset[i] -= struct_offset[0];
  }
  
  MPI_Type_struct( count, struct_length, struct_offset, struct_types, &MPI_IDENTIFIANT_T );
  MPI_Type_commit( &MPI_IDENTIFIANT_T );
}

void parse(char *filename, identifiant_t *tab[], int *nb)
{
  FILE *input=fopen(filename,"r");
  char buffer[BUFFER_LEN];
  char *login;
  char *uid;
  char *gid;
  char *name;  
  int i=0;

  if (!input) {
    fprintf(stderr,"Erreur d'ouverture de %s\n",filename);
    exit(1);
  }

  fgets(buffer,BUFFER_LEN,input);
  sscanf(buffer,"%d",nb);
  *tab=calloc(*nb,sizeof(identifiant_t));
  while (fgets(buffer,BUFFER_LEN,input))
    {
      login = strtok(buffer,"|\n");
      uid   = strtok(NULL,"|\n");
      gid   = strtok(NULL,"|\n");
      name  = strtok(NULL,"|\n");

      strcpy((*tab)[i].login,login);
      (*tab)[i].uid = atoi(uid);
      (*tab)[i].gid = atoi(gid);
      strcpy((*tab)[i].name,name);
      i++;
    }

}


int main(int argc, char **argv) 
{
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
 
/*    printf("Je suis le processus P%d et nous sommes %d au total.\n", */
/*  	 my_id, nb_proc); */
  mpi_types_initialize();
  {
    identifiant_t *tab;
    identifiant_t *to_sort;
    int nb,taille;

    if(my_id==0) parse(argv[1],&tab,&nb);

    MPI_Bcast(&nb, 1, MPI_INT, 0, MPI_COMM_WORLD);

    taille = nb/nb_proc;

    to_sort=calloc(2*(taille),sizeof(identifiant_t));

    MPI_Scatter(tab, taille, MPI_IDENTIFIANT_T, 
		to_sort,taille, MPI_IDENTIFIANT_T,
		0, MPI_COMM_WORLD);


/*      affiche_local(-1,to_sort,taille); */
    odd_even(to_sort,taille);
    MPI_Gather (to_sort, taille, MPI_IDENTIFIANT_T, 
		tab,taille, MPI_IDENTIFIANT_T,
		0, MPI_COMM_WORLD);
    if(my_id==0) affiche(tab,taille*nb_proc);
  }

  MPI_Finalize();

  return (0);
}

