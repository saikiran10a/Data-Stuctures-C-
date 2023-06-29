#include "invertedIndex.h"

int main(int argc, char *argv[])
{
	/* Display error message if CLA is not passed */
	if (argc == 1)
	{
		printf(RED "Error : Invalid no. of arguments\n" C_RESET CYN "Usage ./inverted_index <file.txt> <file1.txt> ... \n" C_RESET);
		return FAILURE;
	}
	
	/* If CLA passed, validate the files using validate function */
	file_node_t *fhead = NULL;
	validate_n_store_filenames(&fhead, argv + 1);
	
	/* Check if files are valid or not */
	if (fhead == NULL)
	{
		printf(RED "No files are valid\nPlease pass the valid files\n" C_RESET);
		return FAILURE;
	}
	
	/* Create array of pointers for 26 alphabet, declare variables */
	wlist_t *HT_head[26] = {NULL};
	int option, flag = 1;
	char choice;
	
	/* Use do-while loop to ask choice from user */
	do {
	printf(BLU "1. Create database\n2. Display database\n3. Search database\n4. Update database\n5. Save database\n" C_RESET RED "Enter your choice : " C_RESET);
	
	/* According to the choice call the function */
	while (1)
	{
		/* Ask user to choice the option */
		scanf("%d", &option);
		switch (option)
		{
			case 1:
			{
				/* Create database for the CLA */
				if (flag)
				{
				  	create_DB(fhead, HT_head);
				}
				
				/* Option is repeated print enter */
				else
				{
					printf(RED "Files passed through commandline already added into the database\n" C_RESET);
				}
				flag = 0;
				break;
			}
			case 2:
			{
				/* Fucntion call to display the database*/
			    if(flag==0)
				    display_DB(HT_head);
				 else
				    printf(RED "Database is empty\n" C_RESET);
				break;
			}
			case 3:
			{
				/* Function call to search the given database */
				char str[10];
				printf(MAG "Enter the word to be searched in Database : " C_RESET);
				scanf("%s", str);
				search_DB(HT_head, str);
				break;
			}
			case 4:
			{
				/* Function call to update database */
				char str[50];
				printf(MAG "Enter the filename : " C_RESET);
				scanf("%s", str);
				update_DB(&fhead, HT_head, str);
				break;
			}
			case 5:
			{
				/* Function call to save the database into new file */
				char str[50];
				printf(MAG "Enter the backup filename : " C_RESET);
				scanf("%s", str);
				if ((save_DB(HT_head, str)) == SUCCESS)
				{
					printf(GRN "Successful : Database saved in %s file\n" C_RESET, str);
				}
				break;
			}
		}
		break;
	}
	/* Enter choice to continue the process or not */
	printf("Do you want to continue (Y/y) : ");
	scanf(" %c", &choice);
	}while (choice == 'y' || choice == 'Y');
}

/* Function definition to validate the given file */
void validate_n_store_filenames(file_node_t **fhead, char *filenames[])
{
	int i = 0;
	while (filenames[i] != NULL)
	{
		/* According the file status print the output */
		int status = IsFileValid(filenames[i]);
		if (status == NOT_PRESENT)
		{
			printf(RED "Error : The file %s does not exist\n" C_RESET CYN "So we are not adding this file to the list\n" C_RESET, filenames[i]);
		}
		else if (status == FILE_EMPTY)
		{
			printf(RED "Error : The file %s is empty\n" C_RESET CYN "So we are not adding this file to the list\n" C_RESET, filenames[i]); 
		}
		else
		{
			/* Function call for storing the files */
			if (store_filenames_to_list(filenames[i], fhead) == SUCCESS)
			{
				printf(GRN "Successfull: %s is added to the list\n" C_RESET, filenames[i]);
			}
			else
			{
				printf(RED "Error : %s is repeated\n"C_RESET CYN"So we are not adding to the list\n" C_RESET, filenames[i]);
			}
		}
		/* Increment index */
		i++;
	}
}

/* Function definition to create new node for a file */
file_node_t *create_node(char *fname)
{
	/* Create new node and update the nodes */
	file_node_t *new = malloc(sizeof(file_node_t));
	if (new == NULL)
	{
		return NULL;
	}
	strcpy(new -> f_name, fname);
	new -> link = NULL;
	return new;
}

/* Fucntion definition to store files in list */
int store_filenames_to_list(char *f_name, file_node_t **head)
{
	/* Check if head is null, then store as first node */
	if (*head == NULL)
	{
		*head = create_node(f_name);
		return SUCCESS;
	}
	
	/* If head not null traverse through the list and check if file present or nor */
	file_node_t *temp = *head, *prev = NULL;
	while (temp != NULL)
	{
		if (strcmp(temp -> f_name,f_name))
		{
			prev = temp;
			temp = temp -> link;
		}
		else
		{
			/* If file repeated the return repeated */
			return REPEATED;
		}
	}
	prev -> link = create_node(f_name);
	return SUCCESS;
}

/* Function to check file valid or not */
int IsFileValid(char *filename)
{
	/* Check the file is exist or not */
	/* Not exist, return NOT_PRESENT */
	FILE *fptr = fopen(filename, "r");
	if (fptr != NULL)
	{	    
	    /* If file file is exist, then check file is empty or not */
	    /* If file is empty, then return FILE_EMPTY */
	    fseek(fptr, 0, SEEK_END);
    	if(ftell(fptr) == 0)
        {
            return FILE_EMPTY;
        }
	    /* If file present and not empty then return SUCCESS */
	    fclose(fptr);
	    return SUCCESS;
	}
	else 
	    return NOT_PRESENT;
}
