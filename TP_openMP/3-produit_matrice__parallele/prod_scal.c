#include <stdio.h>
#include <omp.h>


#define SIZE 256
int main () {
double sum , a[ SIZE ], b[ SIZE ];
// Initialization
sum = 0.;
for (int i = 0; i < SIZE ; i ++) {
a[i] = i * 0.5;
b[i] = i * 2.0;
}
// Computation
#pragma omp parallel for reduction(+: sum )
for (int i = 0; i < SIZE ; i ++) {
sum = sum + a[i ]* b[i ];
}
printf (" sum = %g\n" , sum );
return 0;
}
