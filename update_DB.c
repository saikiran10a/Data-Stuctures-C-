#include "invertedIndex.h"

/* Function to update the database */
int update_DB(file_node_t **file_head, wlist_t **head, char *filename)
{
	/* Declare local variables */
	wlist_t *temp = *head;
	file_node_t *tmp_f = *file_head;
	int flag=0; int i = 0;
	
	/* Print the error according to the file status */
	int status = IsFileValid(filename);
	
	/* Check file present or not */
	if (status == NOT_PRESENT)
	{
	printf(RED "Error : The file %s does not exist\n" C_RESET CYN "So we are not adding this file to the list\n" C_RESET, filename); 
	}
	
	/* Check fiel empty or not */
	else if (status == FILE_EMPTY)
	{
		printf(RED "Error : The file %s is empty\n" C_RESET CYN "So we are not adding this file to the list\n" C_RESET, filename); 
	}
	else
	{
		/* Check if fucntion to sotre filename to list is success or not */
     	if (store_filenames_to_list(filename, &tmp_f) == SUCCESS)
		{
		    while(tmp_f)
            {
              	if ( !strcmp(tmp_f->f_name,filename))
               	{
               		printf(GRN "Successfull: %s is added to the list\n" C_RESET, filename);
                  	create_DB(tmp_f,head);
               	}
           	    tmp_f = tmp_f->link;
          	}
    	}	
    	/* Print error if file is repeated */
		else
		{
			printf(RED "Error : %s is repeated\n" C_RESET CYN"So we are not adding this file to the list\n" C_RESET, filename); 
		}
	}
}
