#include "minishell.h"

void	args_printer(t_args *args)
{
	t_args *p;

	p = args;
	while (p != NULL)
	{
		ft_putstr_parse("arg {");
		if (p->arg[0] != REDIRECTION1_TOKEN)
			ft_putstr_parse(p->arg);
		ft_putstr_parse("}\n");
		p = p->next;
	}
}

void simple_cmd_printer(t_simple_cmd *s)
{
	t_simple_cmd *p;

	p = s;
	ft_putstr_parse("-------- PIPELINE ----------\n");
	while (p != NULL)
	{
		ft_putstr_parse("----------------\n");
		ft_putstr_parse("cmd {");
		ft_putstr_parse(p->cmd);
		ft_putstr_parse("}\n");
		ft_putstr_parse("cmd-id {");
		ft_putnbr_fd(p->id, 1);
		ft_putstr_parse("}\n");
		args_printer(p->args);
		ft_putstr_parse("in_fd {");
		ft_putnbr_fd(p->in_fd, 1);
		ft_putstr_parse("}\n");
		ft_putstr_parse("out_fd {");
		ft_putnbr_fd(p->out_fd, 1);
		ft_putstr_parse("}\n");
		ft_putstr_parse("err_fd {");
		ft_putnbr_fd(p->err_fd, 1);
		ft_putstr_parse("}\n");
		ft_putstr_parse("----------------\n");
		p = p->next;
	}
}
