void tri_bulle(int tableau[],int longueur)
     {
     int i, inversion;

     do
       {
       inversion=0;

       for(i=0;i<longueur-1;i++)
          {
          if (tableau[i]>tableau[i+1])
             {
             echanger(tableau,i,i+1);
             inversion=1;
             }
          }
       }
     while(inversion);
     }
