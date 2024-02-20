#include "invertedIndex.h"
int search_DB(wlist_t **head, char *word)
{
    int index=tolower(word[0])%97;
    wlist_t *tmp=head[index];
    while(tmp)
    {
        if(strcmp(word,tmp->word))
        {
            tmp = tmp->link;
        }
        else
        {
            printf("Word %s is found in the Database and is present in %d file(s)\n" , tmp->word , tmp->f_count);

	        table_link_t *Thead = tmp->t_link;

	        while(Thead)
	        {
	    	    printf("In File  %s\t%d times \n", Thead->f_name , Thead->w_count);
		        Thead = Thead->link;
	        }
	        return SUCCESS;
        }
    }
    return printf("Error: word %s is not found in the Database\n",word);

}