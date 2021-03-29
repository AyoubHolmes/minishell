#include "includes.h"

char *pwd(t_minishell *shell)
{
    char *cwd;

    cwd = malloc(PATH_MAX); 
    ft_putstr(getcwd(cwd, PATH_MAX),1);
    write(1,"\n",1);
    return("");
}
