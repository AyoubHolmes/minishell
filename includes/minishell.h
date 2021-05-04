#ifndef MINISHELL_H
#define MINISHELL_H

# define PIPE_SETTER 1
# define SEMICOLONE_SETTER 2
# define SINGLE_QUOTE_SETTER 4
# define DOUBLE_QUOTE_SETTER 8
# define RED1_SETTER 16
# define RED2_SETTER 32
# define RED3_SETTER 64
# define DOLLAR_SETTER 128

# define PIPE_TOKEN -10
# define SEMICOLONE_TOKEN -20
# define SQ_TOKEN -30
# define DQ_TOKEN -40
# define RED1_TOKEN -50
# define RED2_TOKEN -60
# define RED3_TOKEN -70
# define DOLLAR_TOKEN -80
# define BS_TOKEN -90
# define STAR_TOKEN -100

#define UP_KEY 4283163
#define DOWN_KEY 4348699

# include <stdio.h>
# include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include  <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"

typedef struct	s_element
{
	void				*obj1;
	void				*obj2;
	int					id;
	struct s_element	*next;
}
				t_element;

typedef struct		s_args
{
	char			*arg;
	struct	s_args	*next;
}					t_args;


typedef struct s_simple_cmd
{
	int		id;
	char	*cmd;
	t_args	*args;
	int		out_fd;
	int		in_fd;
	int		err_fd;
	int		err_id;
	struct s_simple_cmd *next;
} t_simple_cmd;

typedef struct s_minishell
{

	char		*line;
	char		c;
	int			is_beginning_of_line;
	int			is_an_escape_character;
	int			status;
	char		*helper;
	t_simple_cmd *simple_cmd;
	char		**enviroment;
	char		*cmd;
    int 		choice;
	t_args		*args;
    t_element	*shell;
    t_element	*paths;
    t_element	*pwd;
    t_element	*home;
	t_element	*oldpwd;
    char		**path;
	int			old_stdout;
	int			old_stdin;
	int			old_stderror;
	int			in_fd;
	int			out_fd;
	int			err_fd;
	int			nb_pipe;
	int			wait_status;
	int			er_id;
	int				*pid_status;
}				t_minishell;

t_minishell	g_cli;

typedef struct		s_regex
{
	struct dirent	*entry;
	char			*file;
	t_args			*tmp;
	int				id;
	DIR				*directory;
	char			*path;
	char			*match;
	char *cmp_tmp;
}					t_regex;

void	ft_putstr_parse(char *str);
void	prompt(int status, int err);
int		get_next_line(char **line);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void    ft_lexer(t_minishell *cli);
void    lexer_debugger(t_minishell *cli);
char	*ft_minisubstr(char const *src, unsigned int start, size_t n);
void	create_simple_cmd(t_minishell *cli, int *i, int *start, t_simple_cmd **simple_cmd);
int		add_simple_cmd_node(t_simple_cmd **simple_cmd, char *cmd, t_minishell *cli);
void	simple_cmd_printer(t_simple_cmd *s);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *src, unsigned int start, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
int     is_a_redirection(char *line);
void	free_simple_cmd(t_simple_cmd **simple_cmd);
void	free_args(t_args **args);
void    ft_lexer_token_helper(char *c, char *line, int setter, int token);
int     is_not_a_string(char c);
int     redirection_is_set(char *c, char *line);
int     is_a_redirection_token(char *line);
int		dispatcher_id(char *cmd);
int		insert_cmd(t_simple_cmd **s, char *cmd);
char	*arg_correction(char *s, t_element *env, int err_id);
char	*add_char_at_beginning(char c, char *s);
char	*extract_filename(char *s, t_element *env, int err_id);
int		get_fd_file(char *cmd, int *i, t_simple_cmd **s, t_element *env);
t_simple_cmd	*create_simple_cmd_node(char *cmd, t_element *env, int *stat, int err_id);

//exec
char **ft_split(char const *s, char c);
void fill_list(char **var,t_minishell *shell);
void fill_dispatcher(t_minishell *shell);
char *ft_system(t_minishell *shell);
void ft_putstr(char *str,int fd);
char *echo_(t_minishell *shell);
char *pwd(t_minishell *shell);
char *cd(t_minishell *shell);
char *export_(t_minishell *shell);
char *unset(t_minishell *shell);
char *env_(t_minishell *shell);
char *exit_(t_minishell *shell);
char *clear_(t_minishell *shell);
t_element	*create_list(void *elt1,void *elt2, int id);
t_element	*add_end(t_element **liste, void *elt1,void *elt2, int id);
void delete_elem(char *elm,t_element *shell_);
void sort_l(t_element *list);
void filling(t_element **p,t_element *list);
void ft_pipe(t_minishell *cli);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *src);
t_element *catch_elem(char *elm1,t_element **shell_);
void	free_element(t_element *list);
void	ft_free_var(void *var);
int	check_identifier(char *str, t_minishell *shell, int id, char *arg);
void check_cli_args(t_args **args);
void	add_args(t_args *args_, char *cmd);
void	delete_arg(t_args **args, char *arg);
char *ft_trim_end(char const *s1,char const *end);
int	ft_find(char *str, char *look_for);
void	reg_handler(t_regex *reg, t_args **args);
int	regex_handler(char *regex, char *file);
int	check_star(char *str);
char	*check_path(char *arg, char **match);
void	check_cli_cmd(char **cmd);
t_element	*fill_list_files(DIR *direc, char *match);
void	replace_star(char **str);
#endif
