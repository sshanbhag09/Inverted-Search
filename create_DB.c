#include "invertedIndex.h"

int create_DB(file_node_t *file_head, wlist_t **head)
{
    
    while (file_head)
    {
        read_datafile(head, file_head -> f_name);
        file_head  = file_head -> link;
    }
}

void read_datafile(wlist_t **head, char *f_name)
{
    FILE *fptr = fopen(f_name, "r");

    char word[BUFF_SIZE], index, flag = 1;
    while (fscanf(fptr, "%s", word) != EOF)
    {
        flag = 1;
        // Only for lower case, TODO: Uppercase and non-alphabet
        if(word[0]>=97)
        index = word[0] - 97;
        else if(word[0]>=65)
        {
            index=word[0] - 65;
        }
        if(!(index >= 0 && index <= 25))
        {
            index=26;
        }
        if (head[index] != NULL)
        {
            wlist_t *temp = head[index]; //Creating local reference

            while (temp)
            {
                //Checking the word matches
                if (strcmp(temp -> word, word))
                {
                    temp = temp -> link;
                }
                else
                {
                    update_word_count(&temp, f_name); // if word found
                    flag = 0;
                    break;
                }
            }
        }
        if (flag == 1)
            insert_at_last_main(&head[index], word, f_name);
    }
    printf("Successfull: Creation of database for file %s\n", f_name);
}
int update_word_count(wlist_t **temp, char *f_name)
{
    /*TODO: Create local reference for table link node
      table_link_t *t = temp -> t_link
      
      Run the loop and check whether filename matching or not
      1) If filename matches, increment the wordcount in respective table link node, return SUCCESS.
      2) If filaname not  matches, you reached end of the list,
      2.1) Create table link node, and insert the node as last in the table link list.
      update_link_table(temp, f_name);
      return SUCCESS
     */
    table_link_t *t= (*temp)->t_link;
    table_link_t *prev=NULL;
    while(t)
    {
        if(strcmp(t->f_name,f_name))
        {
            prev=t;
            t=t->link;
            
        }
        else
        {
            t->w_count++;
            return SUCCESS;
        }
    }
    //if not found;
    (*temp)->f_count++;
    table_link_t *new=malloc(sizeof(table_link_t));
    if(new == NULL)
    {
    	return FAILURE;
    }
    strcpy(new->f_name, f_name);
    new->w_count = 1;
    new->link = NULL;
    prev->link=new;
    return SUCCESS;
}
int insert_at_last_main(wlist_t **head, char *word, char *f_name)
{
    //Create a node
    wlist_t *new = malloc(sizeof(wlist_t));
    wlist_t *tmp=*head;
    //Validate new
    if(new==NULL)
    {
        return FAILURE;
    }
    //Update fields
    new -> f_count = 1;
    strcpy(new -> word,word); //Think how to store the word
    new -> link = NULL;
    new->t_link=NULL;
    update_link_table(&new, f_name);

    //Check the list empty
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    //Traverse and find the last node, insert new as last node
    if (*head == NULL)
    {
        
        *head = new;
        return SUCCESS;
    }
    while(tmp->link!=NULL)
    {
        tmp=tmp->link;
    }
    tmp->link=new;
    return SUCCESS;
    //TODO: Write insert last logic
}


int update_link_table(wlist_t **word_node, char *f_name)
{
    //Create the linktable node
    table_link_t *new = malloc(sizeof(table_link_t));

    //Validate new

    //Update the node fields (wordcount, filename, link)
    new -> w_count = 1;
    new -> link = NULL;
    strcpy(new -> f_name,f_name);

    (*word_node) -> t_link = new;
    return SUCCESS;
}
