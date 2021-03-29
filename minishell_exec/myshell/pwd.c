#include "minishell.h"

char *pwd(t_minishell *shell)
{
    char *position;

    position = malloc(PATH_MAX); 
    if(getcwd(position, PATH_MAX)!= NULL)
        ft_putstr(position,1);
    free(position);
    write(1,"\n",1);
    return("");
}
