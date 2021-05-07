#include "minishell.h"

void	args_printer(t_args *args, int fd)
{
	t_args	*p;

	p = args;
	while (p != NULL)
	{
		ft_putstr("arg {", fd);
		if (p->arg[0] != RED1_TOKEN)
			ft_putstr(p->arg, fd);
		ft_putstr("}\n", fd);
		p = p->next;
	}
}

void	simple_cmd_printer(t_simple_cmd *s)
{
	t_simple_cmd	*p;

	p = s;
	while (p != NULL)
	{
		ft_putstr("-------- PIPELINE ----------\n", 1);
		ft_putstr("cmd {", p->out_fd);
		ft_putstr(p->cmd, p->out_fd);
		ft_putstr("}\n", p->out_fd);
		ft_putstr("cmd-id {", p->out_fd);
		ft_putnbr_fd(p->id, p->out_fd);
		ft_putstr("}\n", p->out_fd);
		args_printer(p->args, p->out_fd);
		ft_putstr("in_fd {", p->out_fd);
		ft_putnbr_fd(p->in_fd, p->out_fd);
		ft_putstr("}\n", p->out_fd);
		ft_putstr("out_fd {", p->out_fd);
		ft_putnbr_fd(p->out_fd, p->out_fd);
		ft_putstr("}\n", p->out_fd);
		ft_putstr("err_fd {", p->out_fd);
		ft_putnbr_fd(p->err_fd, p->out_fd);
		ft_putstr("}\n", p->out_fd);
		ft_putstr("----------------\n", p->out_fd);
		p = p->next;
	}
}
