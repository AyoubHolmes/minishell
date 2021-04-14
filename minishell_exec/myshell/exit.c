#include "minishell.h"
char *exit_(t_minishell *shell) 
{
    int     status;
    pid_t   killReturnValue;
    pid_t   forkReturnValue;
    forkReturnValue = fork();
    if(forkReturnValue > 0){
        ft_putstr_fd("exit\n",shell->err_fd);
        close(shell->out_fd);
	    close(shell->in_fd);
        dup2(shell->old_stdout, 1);
	    dup2(shell->old_stdin, 0);
        exit(EXIT_SUCCESS);
    }
    else if(forkReturnValue == 0) 
    {
        killReturnValue = kill(forkReturnValue, SIGKILL);
        if(killReturnValue)
            waitpid(forkReturnValue, &status, 0);
    }
    return("");
}