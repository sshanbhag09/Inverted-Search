#include "invertedIndex.h"

#include "InvertedIndex.h"

int update_DB(file_node_t** f_head,wlist_t ** head)
{
    int empty;
    char file_name[NAMELENGTH];
    //input
    printf("Enter the filename do you want to add in Database: ");
    scanf("%s", file_name);
    int flag=0;  
    //Validate the file its empty or not
    empty = IsFileValid(file_name);
    if (empty == NOT_PRESENT)
    {
	    printf("The file %s is not available\n", file_name);
	    printf("Hence we are not adding this into File Linked List\n");
	    
    }
    else if (empty == FILE_EMPTY)
    {
	    printf("The file %s is Empty\n", file_name);
	    printf("Hence we are not adding %s into File Linked List\n", file_name);
	    
    }
    else
    {
	    //File is valid then add it to the linked list
       	int result = to_create_list_of_files (f_head, file_name);	        
        if (result == SUCCESS)
	    {
	        printf("Successful in Inserting file %s into the File List\n",file_name);
            flag=1;
        }
	    else if (result == REPEATED)
	    {
	        printf("This file %s is Repeated\n", file_name);
	        printf("So we are not adding %s into file List\n", file_name);
	    
	    }
	    else
	    {
	        printf("Failed to add the file into the List");
	        
	    }   
    }
    //After successful insertion of file into the file linked list
    if(flag==1){
    file_node_t* f_temp = *f_head;
    while (f_temp)
    {	
        //Compare the files of Flist
    	if (!strcmp(f_temp->f_name, file_name))
	    {
	        create_DB(f_temp, head);
	        
	    }
	    f_temp = f_temp->link;
    }
    printf("Database updated successfully!!\n");
    }
}
int to_create_list_of_files (file_node_t** head, char* filename)
{
    file_node_t* temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->f_name, filename) == 0)
        {
            return REPEATED;
        }
        temp = temp->link;
    }

    //Creating new node
    file_node_t* new_file = malloc(sizeof(file_node_t));
    
    //Validating new
    if (new_file == NULL)
    {
        return FAILURE;
    }

    //Updating filename and link part
    strcpy(new_file->f_name, filename);
    new_file->link = NULL;
    if (*head == NULL)
    {
        *head = new_file;
         return SUCCESS;
    }

    temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new_file;
    return  SUCCESS;
}






