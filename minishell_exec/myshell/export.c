#include "includes.h"

char *export_(t_minishell *shell_)
{
	t_element *p;
	p = NULL;
	filling(&p,shell_->shell);
	sort_l(p);
	while (p != NULL)
	{
		printf("declare -x %s=\"%s\"\n", p->obj1,p->obj2);
		p = p->next;
	}
	return("");
}