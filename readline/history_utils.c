#include "readline.h"

void	add_history(char *s, t_history **str)
{
	t_history *p;
	t_history *q;

	if (*str == NULL)
	{
		*str = (t_history *)malloc(sizeof(t_history));
		(*str)->s = strdup(s);
		(*str)->next = NULL;
		(*str)->prev = NULL;
	}
	else
	{
		p = (t_history *)malloc(sizeof(t_history));
		p->s = strdup(s);
		p->prev = *str;
		p->next = NULL;
		(*str)->next = p;
		*str = p;
	}
	p = *str;
	while (p)
	{
		ft_putstr("\n");
		ft_putstr(p->s);
		ft_putstr("       ");
		q = p;
		p = p->prev;
	}
	ft_putstr("\n");
	while (q)
	{
		ft_putstr("\n");
		ft_putstr(q->s);
		ft_putstr("       ");
		q = q->next;
	}
	ft_putstr("\n");
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
  atexit (reset_input_mode);
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON | ECHO | ISIG);
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