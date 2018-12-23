#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef float(*criterion)(float, float);

float rosenbrock (float x,float y)
{
    float a=1.0 - x;
    float b=y - x*x;
    return (a*a + 100.0*b*b);
}
double randUniform()
{
    return (2.0 * ((double)rand()/(double)RAND_MAX) - 1.0);
}
double randNormal()
{
    static int useY = 0;
    double x,r;
    static double y;

    if(useY)
    {
        useY = 0;
        return y;
    }
    do
    {
        x = randUniform();
        y = randUniform();
        r = x * x + y * y;
    } while(r >= 1.0);
    r = sqrt((-2.0 * log(r)) / r);
    x *= r;
    y *= r;
    useY = 1;
    return x;
}

int recuit (int n, double Tf, double *x0, double T0, criterion f)
{
    double x[2];
    for (int k=0; k<2 ;k++)
    {
        x[k]=x0[k];
    }
    double T = T0;
    double y[2];
    while (T > Tf)
    {
        printf("%f\n",T);
        int i = 0;

        while(i < n)
        {

            for (int j=0;j<2;j++)
            {
                y[j] = x[j] + randNormal() * sqrt(T);

            }

            if (f(y[0],y[1]) < f(x[0],x[1]))
                {
                    for (int k=0;k<2;k++)
                    {
                       x[k]=y[k];
                    }
                    i++;

                }
            else{

                double delta = f(x[0],x[1]) - f(y[0],y[1]);
                double p = exp(delta/T);
                double toss = (double)rand() / (double)RAND_MAX;
                if (toss < p)
                {
                    for (int l=0; l<2; l++)
                    {
                        x[l]= y[l];
                    }
                        i++;
                    }
                }
            }
            T = 0.95*T;
        }
    printf("(abscisse = %f ,ordonnée = %f)",x[0],x[1]);
}

int main ()
{
    omp_set_num_threads(8);
    #pragma omp parallel
    {
    }
    double x0[2];
    x0[0]=-1.0;
    x0[1]=1.0;
    double Tf = 0.001;
    double T0 = 10. ;
    int n = 1000;
    recuit (n,Tf,x0,T0,rosenbrock);
}
