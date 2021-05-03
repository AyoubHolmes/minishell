#include "readline.h"
#include "../../includes/minishell.h"
#define UP 4283163
#define DOWN 4348699

struct termios old_attr;

void	termios_config(struct termios *old_attr)
{
	struct termios	new_attr;
	char			*term_type;
	int				ret;
	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_putstr_fd("\r\033[0KTERM must be set (see 'env').\n", 1);
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_putstr_fd("\r\033[0KCould not access to the termcap database..\n", 1);
	if (ret == 0)
		ft_putstr_fd("\r\033[0KIs not defined in termcap database.\n", 1);
	if (tcgetattr(STDIN_FILENO, old_attr) < 0)
		ft_putstr_fd("Error tcgetattr\n", 1);
	new_attr = *old_attr;
	new_attr.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) < 0)
		ft_putstr_fd("\r\033[0KError tcsetattr.\n", 1);
}

void func(int c)
{
    ft_putstr_fd("Hello world", 1);;
}

int main()
{
    long c;

    signal(SIGSEGV, func);
    char *str;

    str[1] = 'a';
    termios_config(&old_attr);
    c =0;
    read(1, &c, 6);
    ft_putnbr_fd((int)c, 1);
    if (c == UP)
        ft_putstr_fd("UP", 1);
    if (c == DOWN)
        ft_putstr_fd("DOWN", 1);

}