#include "includes.h"

char *unset(t_minishell *shell)
{
    delete_elem("_",shell->shell);
    return("");
}