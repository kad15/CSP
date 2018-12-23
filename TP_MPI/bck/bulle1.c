#define TRUE 1;
#define FALSE 0;

void tri_a_bulle(int t[], int const n) 
{
 	int j   = 0; /* Variable de boucle */
 	int tmp = 0; /* Variable de stockage temporaire */

	/* Booléen marquant l'arrêt du tri si le tableau est ordonné */
	int en_desordre = TRUE; 
	/* Boucle de répétition du tri et le test qui
	 arrête le tri dès que le tableau est ordonné(en_desordre=FALSE) */
	while (en_desordre)
	{
		/* Supposons le tableau ordonné */
		en_desordre = FALSE;
		/* Vérification des éléments des places j et j+1 */
		for (j = 0; j < n-1; j++)
		{
			/* Si les 2 éléments sont mal triés */
			if(t[j] > t[j+1])
			{
				/* Inversion des 2 éléments */
 				tmp = t[j+1];
 				t[j+1] = t[j];
 				t[j] = tmp;

 				/* Le tableau n'est toujours pas trié */
				en_desordre = TRUE;
 			}
		}
	}
}

