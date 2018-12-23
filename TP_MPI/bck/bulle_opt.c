#Version optimisée évitant de parcourir la fin du tableau déjà triée.

void tri_a_bulle(int* t, int const size) 
{
	int en_desordre = 1;
	int i,j,temp;

	for (i = 0; (i < size) && en_desordre; ++i)
	{
		en_desordre = 0;
		for (j = 1; j < (size - i); ++j)
		{
			if (t[j-1] > t[j])
			{
				temp = t[j-1];
				t[j-1] = t[j];
				t[j] = temp;
				en_desordre = 1;
 			}
		}
	}
}

