#include "minishell.h"

char *unset(t_minishell *shell)
{
    delete_elem(shell->args->arg,shell->shell);
    return("");
}