#include "invertedIndex.h"
int save_DB(wlist_t **head)
{
    // char file_name[NAMELENGTH];
    // printf("Enter the filename you want save in database\n");
    // scanf("%s" , file_name);
    //  FILE *fptr = fopen(file_name , "w");
    //  if (fptr == NULL)
    // {
	// printf("Error: File not available\n");
    //     return FAILURE;
    // }
    // fprintf(fptr,"Files data");

    // for(int i=0;i<SIZE;i++){
    //     wlist_t *temp=head[i];
    //     if(temp!=NULL)
    //     {
    //         fprintf(fptr,"#%d \n", i);
    //     }
    //     while(temp)
    //     {
            
    //         fprintf(fptr,"%s;%d\n", temp->word, temp->f_count);
    //         table_link_t *Thead=temp->t_link;
    //         while (Thead != NULL)
    //         {
    //             fprintf(fptr,"%s;%d;",Thead->f_name, Thead->w_count);
    //             Thead = Thead->link;
    //         }
    //         fprintf(fptr,"\n"); 
    //         temp=temp->link;
    //     }
    //     //printf("\n");
    // }
     char file_name[NAMELENGTH];
    printf("Enter the filename you want save in database\n");
    scanf("%s" , file_name);

    //open the file

    FILE *fptr = fopen(file_name , "w");
    
    if (fptr == NULL)
    {
	printf("Error: File not available\n");
        return FAILURE;
    }
    
    for (int index = 0; index < 27; index++)
    {
        wlist_t* temp = head[index];
        if(temp!=NULL)
        {
            fprintf(fptr,"#%d\n",index);
        }
	//Checking the Wlist empty or not
        while (temp != NULL)
        {
            fprintf(fptr," %s;%d;", temp->word, temp->f_count);
            //printf("hell\n");N
            
            table_link_t * l_temp = temp->t_link;
            while (l_temp != NULL)
            {
                fprintf(fptr,"%s;%d;",l_temp->f_name, l_temp->w_count);
                l_temp = l_temp->link;
            }
            fprintf(fptr,"\n");
            
	        //Moving temp to next node
            temp = temp->link;
        }
    }
    
    printf("Database saved successfully in %s file\n", file_name);
    fclose(fptr);
    return SUCCESS;
}