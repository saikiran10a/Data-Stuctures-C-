#include "invertedIndex.h"

/* Function definition for searching the word */
int search_DB(wlist_t **head, char *word)
{
	/* Get index value */
	int index;
	if (word[0] >= 'a' && word[0] <= 'z')
	{
		index = word[0] % 97;
	}
	else if (word[0] >= 'A' && word[0] <= 'Z')
	{
		index = word[0] % 65;
	}
	
	/* If node is empty */
	if (head[index] == NULL)
	{
     	printf(RED"Error: Word \"%s\" is not found in the database\n"C_RESET, word);
   	}
  	else
  	{
  		/* Travese and compare */
  		wlist_t *tmp = head[index];     
		while (tmp  != NULL)
		{
			/* If word is found return Success message */
		 	if (strcmp(tmp -> word, word) == 0)
		  	{ 
		   		file_table_t *temp = tmp -> t_link;
				printf(RED "Word" C_RESET GRN " \"%s\"" C_RESET RED " found in the database and it is present in" C_RESET BLU " %d" C_RESET RED " file(s)\n" C_RESET, word, tmp -> f_count);
				/* If word is found in different file, print those files with count */
			  	while (temp  != NULL)
			 	{
			   	  	printf(RED "In file" C_RESET GRN " %s" C_RESET BLU " %d" C_RESET RED " time(s)\n" C_RESET, temp -> f_name, temp -> w_count);
					temp = temp -> link;
			  	}
			  	return SUCCESS;
		 	}
		  	tmp = tmp -> link;   
		}
		/* If word not found */
	  	printf(RED "Error: Word \"%s\" is not found in the database\n" C_RESET, word);
	}
}
