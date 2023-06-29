#include "invertedIndex.h"

/* Function definition to create the database */
int create_DB(file_node_t *file_head, wlist_t **head)
{ 
	/* Traverse in file node and call read datafile function */
	while (file_head != NULL)	
	{
		read_datafile(head, file_head -> f_name);
		file_head = file_head -> link;
	}
}

/* Function definition to read datafile */
void read_datafile(wlist_t **head, char *f_name)
{
	/* Take file pointer and open the file in read mode */
	FILE *fptr = fopen(f_name, "r");
	
	char word[BUFF_SIZE];
	int index;
	/* Store the words from file into word array */
	while (fscanf(fptr, "%s", word) != EOF)
	{
		/* Get index value */
		int flag = 1;
		if (word[0] >= 'a' && word[0] <= 'z')
		{
			index = word[0] % 97;
		}
		else if (word[0] >= 'A' && word[0] <= 'Z')
		{
			index = word[0] % 65;
		}
		
		/* If contents are present in the node traverse and call update_word_count function */
		if (head[index] != NULL)
		{
			wlist_t *temp = head[index];
			while (temp != NULL)
			{
				if (strcmp(temp -> word, word))
				{
					temp = temp -> link;
				}
				else
				{
					flag = 0;
					update_word_count(&temp, f_name);
					break;
				}
			}
		}
		/* Insert the node at last function call */
		if (flag)
		{
			insert_at_last_main(&head[index], word, f_name);
		}
	}
	printf(GRN "Successfull: creation of database for the %s\n" C_RESET, f_name);
}

/* Function definition to update word count */
int update_word_count(wlist_t **head, char *fname)
{
	/* Take temp variable of type file table node */
 	file_table_t *temp = (*head) -> t_link, *prev;
	
	/* Traverse and compare the file names, if equal then increment word count */
	while (temp != NULL)
	{
		if (strcmp(temp -> f_name, fname))
		{
			prev = temp;
			temp = temp -> link;
		}
		else
		{
			(temp -> w_count)++;
			return SUCCESS;
		}
	}
	/* Increment file count */
	((*head) -> f_count)++;
	
	/* Create new node if it(temp) reaches NULL, for new file and establish the link with previous file table node */
	file_table_t *new = malloc(sizeof(file_table_t));
	
	if (new == NULL)
	{
		return FAILURE;
	}
	new -> w_count = 1;
	strcpy(new -> f_name, fname);
	new -> link = NULL;
	
	prev -> link = new;
	return SUCCESS;
}

/* Function definition for inserting new node */
int insert_at_last_main(wlist_t **head, char *word, char *f_name)
{
	/* Create new node */
	wlist_t *new = malloc(sizeof(wlist_t));
	
	/* Check if new node is created or not */
	if (new == NULL)
	{
		return FAILURE;
	}
	
	/* Update new node with f_count, word, t_link and link */
	new -> f_count = 1;
	strcpy(new -> word, word);
	new -> link = NULL;
	update_link_table(&new, f_name);
	
	/* Check if file is empty or not, if empty update new node */
	if (*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	
	/* Traverse and update new node and establish link with previous node */
	wlist_t *temp = *head;
	while (temp -> link != NULL)
	{
		temp = temp -> link;
	}
	temp -> link = new;
	return SUCCESS;
}

/* Function definition for updating link table */
int update_link_table(wlist_t **word_node, char *f_name)
{
	/* Create new link table node */
	file_table_t *new = malloc(sizeof(file_table_t));
	
	/* Check if new node is created or not */
	if (new == NULL)
	{
		return FAILURE;
	}
	
	/* Update new node with w_count, f_name and link */
	new -> w_count = 1;
	strcpy(new -> f_name, f_name);
	new -> link = NULL;
	
	/* Update the wlist_t t_link with new table link node */
	(*word_node) -> t_link = new;
	return SUCCESS;
}

