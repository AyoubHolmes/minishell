#include "includes.h"

char *echo(t_minishell *shell) 
{
     int fd2;
    char *str = NULL;
    int a;
    a = O_TRUNC;// >
    //a = 1;//>>
    if(str == NULL)
    {
        fd2 = 1;
        ft_putstr("piiiiipiiiiip\n",fd2);
        return("");
    }
    else
        fd2 = open(str,  O_WRONLY | O_CREAT | a | O_APPEND, 0666);
    if(fd2 < 0)
    {
        printf("bash: "); 
        printf("%s: ",str);
        printf("%s\n",strerror(errno));
    }
    else
        ft_putstr("piiiiipiiiiip\n",fd2);
    close(fd2);
    return("");
}