#include "includes.h"

char *pwd(t_minishell *shell)
{
    char *s; 
    ft_putstr(getcwd(s, 0),1);
    write(1,"\n",1);
    return("");
}
