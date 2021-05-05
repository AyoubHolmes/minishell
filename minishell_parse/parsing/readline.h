#ifndef READLINE_H
# define READLINE_H

# include "../../includes/minishell.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>

typedef struct s_readline
{
	int					c;
	struct s_readline	*next;
	struct s_readline	*prev;
}						t_readline;

typedef struct s_history
{
	t_readline			*str;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct s_readline_vars
{
	char			s[30];
	int				c;
	char			*finale;
	struct termios	s_termios;
	t_history		*last;
	t_readline		*dup;
}					t_readline_vars;

void			add_history(t_history **str);
void			set_input_mode (void);
t_history		*get_last_history(t_history **str);
t_history		*duplicate_history(t_history **history);
void			add_char(int c, t_readline **str);
int				size_of_readline(t_readline *str);
void			delete_last_readline(t_readline **str);
char			*generate_line(t_readline *str);
void			print_readline(t_readline *str);
t_readline		*duplicate_readline(t_readline **str);
void			reset_readline(t_readline *str);
int				ft_atoi_readline(char **s);
void			termios_config(struct termios *old_attr);
void			ft_backspace(t_readline **dup);
char			*enter_trigger(t_history **last, t_readline *dup,
					t_history **h, struct termios *s_termios);
char			*clear_trigger(int *status, struct termios *s_termios);
void			up_trigger(t_history **h, t_readline **dup);
void			down_trigger(t_history **h, t_readline **dup);
void			arrow_triggers(int key, t_history **h, t_readline **dup);
void			ft_readline_helper1(int c, t_history **h, t_readline **dup);
void			quit_control(t_history **h, t_readline_vars *vars, int *status);
char			*ft_readline(t_history **h);

#endif