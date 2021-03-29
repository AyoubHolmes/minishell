#include "includes.h"

char *env_(t_minishell *shell_) 
{
	t_element *p;
	p = shell_->shell;
	while (p != NULL)
    {
		if (p->obj2)
		{
			ft_putstr(p->obj1,1);
			ft_putstr("=",1);
			ft_putstr(p->obj2,1);
			ft_putstr("\n",1);
		}
		p = p->next;
	}
	return("");
}