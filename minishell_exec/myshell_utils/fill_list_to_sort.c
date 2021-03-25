#include "includes.h"

void filling(t_element **ptr,t_element *list)
{
    t_element *shell;

    shell = list;
	while(shell != NULL)
    {
        if(*ptr == NULL)
            *ptr = create_list(shell->obj1,shell->obj2, sizeof(char *));
        else
		    *ptr = add_end(ptr,shell->obj1,shell->obj2, sizeof(char *));
        shell = shell->next;
    }
}