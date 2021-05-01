#include "readline.h"

void	add_history(t_history **history)
{
	t_history *p;

	if (*history == NULL)
	{
		*history = (t_history *)malloc(sizeof(t_history));
		(*history)->str = NULL;
		(*history)->next = NULL;
		(*history)->prev = NULL;
	}
	else if ((*history)->str)
	{
		p = (t_history *)malloc(sizeof(t_history));
		p->str = NULL;
		p->prev = *history;
		p->next = NULL;
		(*history)->next = p;
		*history = p;
	}
}

t_history	*duplicate_history(t_history **history)
{
	t_history *dup;
	t_history *p;

	p = *history;
	dup = (t_history *)malloc(sizeof(t_history));
	dup->str = duplicate_readline(&(*history)->str);
	return dup;
}

t_history		*get_last_history(t_history **str)
{
	t_history *p;

	p = *str;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_history_printer(t_history *history)
{
	t_history *p;

	p = history;
	ft_putstr("HISTORY PRINTER\n");
	while (p && p->str)
	{
		print_readline(p->str);
		ft_putstr("\n");
		p = p->prev;
	}
}

void    reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void    set_input_mode (void)
{
  struct termios tattr;
  char *name;

  if (!isatty (STDIN_FILENO))
	{
	  fprintf (stderr, "Not a terminal.\n");
	  exit (1);
	}
  tcgetattr (STDIN_FILENO, &saved_attributes);
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ECHO | ICANON | ISIG);
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

int init_term(void)
{
	int ret;
	char *term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		printf("TERM NOT SET\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		printf("NO ACCESS TO TERMCAPS DATABASE\n");
		return(-1);
	}
	if (ret == 0)
	{
		printf("Terminal type %s not found\n", term_type);
		return(-1);
	}
	return(0);
}