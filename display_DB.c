#include "invertedIndex.h"
int display_DB(wlist_t **head)
{
    for(int i=0;i<SIZE;i++){
        wlist_t *temp=head[i];
        if(temp!=NULL)
        printf("[%d] \t",i);
        while(temp)
        {
            printf("[%s] %d file(s)  ", temp->word, temp->f_count);
            table_link_t *Thead=temp->t_link;
            while (Thead != NULL)
            {
                printf(": File : %s %d times",Thead->f_name, Thead->w_count);
                Thead = Thead->link;
            }
            printf(" -> NULL");
            printf("\n"); 
            temp=temp->link;
        }
        //printf("\n");
    }
}