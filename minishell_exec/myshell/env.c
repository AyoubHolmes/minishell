#include "includes.h"

char *env_(t_minishell *shell_) 
{
	t_element *p;
	p = shell_->shell;
	while (p != NULL)
    {
		printf("%s=%s\n", p->obj1,p->obj2);
		p = p->next;
	}
	return("");
}