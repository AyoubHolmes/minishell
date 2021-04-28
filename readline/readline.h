#ifndef READLINE_H
#define READLINE_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <termcap.h>
#include <signal.h>

typedef struct			s_readline
{
	char				c;
	struct s_readline	*next;
}						t_readline;	

typedef struct			s_history
{
	char				*s;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

struct termios saved_attributes;

// --------------- history functions -----------

void	add_history(char *s, t_history **str);
void    reset_input_mode (void);
void    set_input_mode (void);
int     init_term(void);

// ---------------------------------------------

// --------------- readline functions ----------

void	    add_char(char c, t_readline **str);
int		    size_of_readline(t_readline *str);
void	    delete_last_readline(t_readline **str);
char	    *generate_line(t_readline *str);
void	    print_readline(t_readline *str);
t_readline  *create_readline(char *s);
t_readline *reset_readline(t_readline *str);

// ---------------------------------------------

// ---------------- DEBUGGING ------------------

void ft_putstr(char *s);
void    ft_prompt();

// ---------------------------------------------

#endif // !READLINE_H