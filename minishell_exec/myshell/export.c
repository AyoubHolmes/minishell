#include "includes.h"

char *export_(t_minishell *shell_)
{
	t_element *p;
	p = NULL;
	filling(&p,shell_->shell);
	sort_l(p);
	while (p != NULL)
	{				
		ft_putstr("declare -x ", 1);
		ft_putstr(p->obj1,1);
		if (p->obj2)
		{
			ft_putstr("=\"",1);
			ft_putstr(p->obj2,1);
			ft_putstr("\"",1);
		}
		ft_putstr("\n",1);
		p = p->next;
	}
	return("");
}