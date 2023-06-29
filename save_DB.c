#include "invertedIndex.h"

/* Function definition to save the database */
int save_DB(wlist_t **head, char *fname)
{
	/* Save the database to a file */
	FILE *fptr = fopen(fname, "w");
	for (int i = 0;i <= 25 ; i++)
	{
	   	int flag = 1;
        wlist_t *tmp = head[i];
        /* Traverse and print the database according to the format */
		while (tmp  != NULL)
		{	  
			/* Print node fields */
            (flag-- == 1) ? fprintf(fptr,"#%d;\n", i) : fprintf(fptr, "%s", "");
		    file_table_t *temp = tmp -> t_link;
			fprintf(fptr, "%s;%d;", tmp -> word, tmp -> f_count);
			/* Traverse and print file table node fields */
			while (temp  != NULL)
			{
				fprintf(fptr, "%s;%d;", temp -> f_name, temp -> w_count);
				temp=temp->link;
			}fprintf(fptr, "%s", "#\n");
			tmp = tmp -> link;
		}
	}
	return SUCCESS;
}
