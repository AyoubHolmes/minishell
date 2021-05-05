#include "../../includes/minishell.h"
#include "readline.h"

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		ft_putstr_fd("Quit :3\n", 1);
		g_cli.er_id = 131;
	}
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		ft_putstr_fd("\n", 1);
		g_cli.er_id = 130;
	}
	if (g_cli.pid_status == 0)
		exit(0);
}

void	signals_manager(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
}
