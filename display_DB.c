#include "invertedIndex.h"

/* Fucntion definition to display the database */
int display_DB(wlist_t **head)
{
	/* Loop to check if array of pointers have words */
	for (int i = 0; i <= 25 ; i++)
	{
		int flag = 1;
		wlist_t *tmp = head[i];
		
		/* Loop to traverse the list */
		while (tmp != NULL)
		{
			/* Pattern to print index */
			(flag-- == 1) ? printf(BLU "[%d]" C_RESET, i): printf(" ");
			
			file_table_t *temp = tmp -> t_link;
			
			/* Pattern to printf the words and info */
			printf(GRN "\t[%s]\t" C_RESET RED " %d" C_RESET "  file(s)", tmp ->  word, tmp -> f_count);
			
			/* Loop to traverse every letter node to get related words */
			while (temp != NULL)
			{
				printf("  : File : " GRN "%s" C_RESET " : " RED "%d" C_RESET " time(s)", temp -> f_name, temp -> w_count);
				temp = temp -> link;
			}
			printf(" -> NULL\n");
			tmp = tmp -> link;
		}
	}
}
