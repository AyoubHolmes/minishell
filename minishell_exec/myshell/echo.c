#include "minishell.h"

int compare_n(char *str)
{
    int i;
    int len;
    len = 0;
    len = ft_strlen(str);
    i = 0;
    if(str[i] == '-')
    {
        i++;
        while(str[i] && str[i] == 'n')
            i++;
    }

    if(i == len)
        return(0);
    else
        return(1);
    
}

void    check_echo_args(t_args *elm,int *n)
{
	t_args *tmp;
    int a;

	tmp = elm;
	while(tmp && compare_n(tmp->arg) == 0)
	{
        *n = 1;
        tmp = tmp->next;
    }
    while(tmp)
    {
	    ft_putstr(tmp->arg,1);
	    tmp = tmp->next;
        if(tmp)
            ft_putstr(" ",1);
    }
}

char *echo(t_minishell *shell)
{
    int     n;
    int i;
    int len = 0;

    n = 0;
    check_echo_args(shell->args,&n);
    if(n == 0)
        ft_putstr("\n",1);
    return("");
}