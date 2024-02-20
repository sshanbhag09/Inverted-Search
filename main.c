#include "invertedIndex.h"

int main(int argc, char *argv[])
{
    //Check CLA's Passed or not
    if (argc == 1)
    {
        printf("Error : Invalid no.of arguments\nUsage ./inverted_index <file.txt> <file1.txt> ...\n");
        return FAILURE;
    }


    file_node_t *fhead = NULL;
    validate_n_store_filenames(&fhead, argv + 1);

    if (fhead == NULL)
    {
        printf("There is no valid files\nPlease pass the valid file\n");
        return FAILURE;
    }


    int choice;
    char option;
    char word[BUFF_SIZE];
    wlist_t *head[27] = {NULL};

    do
    {
        printf("Select your choice among following options:\n1. Create Database\n2. Display Database\n3. Search Database\n4. Update database\n5. Save Database\nEnter your Choice: ");
        scanf("%d", &choice);
	
        switch (choice)
        {
        
            //create    
            case 1:
 	            create_DB(fhead, head); 	             
                break;        
            //display            
             case 2:
	             display_DB(head);
	             break;
            
            // //search 
            case 3:
 	             //clearing input buffer
	             printf("Enter the word you want to search: ");
	             scanf("%s",word);
	             search_DB(head,word);
	             break;   
            // //update    
	         case 4:
	            update_DB(&fhead, head);
	            break;
                    
              
    	    // //save database
    	    case 5:   
	             save_DB(head);
	             break;        
	        default:
	            break;
	}
    printf("Do you want to continue (y/n): ");
	getchar();        
    scanf("%c",&option);
    } while (option == 'Y'|| option == 'y');
    
    
    
}

void validate_n_store_filenames(file_node_t **fhead, char *filenames[])
{
    int i = 0, status;
    while (filenames[i] != NULL)
    {
        status = IsFileValid(filenames[i]);
        if (status == NOT_PRESENT)
        {
            printf("Error : The file %s is not present\n", filenames[i]);
            printf("So we are not adding into the list\n");
        }
        else if (status == FILE_EMPTY)
        {
            printf("The file %s is an empty file\n", filenames[i]);
            printf("So we are not adding into the list\n");
        }
        else
        {
            if (store_filenames_to_list(filenames[i], fhead) == REPEATED)
                printf("The file %s is repeated\nSo we are not adding into the list\n", filenames[i]);
            else
                printf("Successfull: %s added to the list\n", filenames[i]);
        }
        i++;
    }
}

int IsFileValid(char *f_name)
{
    //1. Check whether the file exist or not.
        //If the file not exist, then return NOT_PRESENT
    FILE* fptr = fopen(f_name, "r");

    //Validating fptr. If fprt NULL then file not available
    if (fptr == NULL)
    {
        return NOT_PRESENT;
    }

    //Check if file empty or not
    fseek(fptr, 0L, SEEK_END);
    if (ftell(fptr) == 0)
    {
        return FILE_EMPTY;
    }
    
    return SUCCESS;
    

    //3. If file not empty, then return SUCCESS
}

file_node_t *create_node(char *fname)
{
    file_node_t *new = malloc(sizeof(file_node_t));
    if (new == NULL)
    return NULL;
    strcpy(new -> f_name,fname);  //Think how to store the filename
    new -> link = NULL;
    return new;
}

int store_filenames_to_list(char *f_name, file_node_t **head)
{
    file_node_t *new;
    //Insert at last operation
    if (*head == NULL)
    {
        new = create_node(f_name);
        *head = new;
        return SUCCESS;
    }

    file_node_t *temp = *head;

    while (temp->link != NULL)
    {
        // TODO: previous pointer, which points to previous node
        if (strcmp(temp -> f_name, f_name) != 0)
            {
                printf("%d",temp->f_name);
                temp = temp -> link;

            }
        else
            return REPEATED;
    }
    temp -> link  = create_node(f_name);
    return SUCCESS;
}











