#include <omp.h>
#include <stdio.h>

int main ()  
{
   int nthreads = 10;
   omp_set_num_threads(nthreads);

   #pragma omp parallel
   {
      int id = omp_get_thread_num();

      printf("Hello World du thread = %d", id);
      printf(" avec %d threads\n",omp_get_num_threads());
   }  

   printf("terminé avec %d threads\n",nthreads);

}
 
 

