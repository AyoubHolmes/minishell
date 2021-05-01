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
	int				c;
	struct s_readline	*next;
	struct s_readline	*prev;
}						t_readline;	

typedef struct			s_history
{
	t_readline			*str;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

struct termios saved_attributes;

// --------------- history functions -----------

void			add_history(t_history **str);
void    		reset_input_mode (void);
void    		set_input_mode (void);
int     		init_term(void);
void			ft_history_printer(t_history *history);
t_history		*get_last_history(t_history **str);
t_history		*duplicate_history(t_history **history);

// ---------------------------------------------

// --------------- readline functions ----------

void	    add_char(int c, t_readline **str);
int		    size_of_readline(t_readline *str);
void	    delete_last_readline(t_readline **str);
char	    *generate_line(t_readline *str);
void	    print_readline(t_readline *str);
t_readline	*duplicate_readline(t_readline **str);
void		reset_readline(t_readline *str);
void    reset_input_mode (void);

// ---------------------------------------------

// ---------------- DEBUGGING ------------------

void ft_putstr(char *s);
void    ft_prompt();

// ---------------------------------------------

#endif // !READLINE_H