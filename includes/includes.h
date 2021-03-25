#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include  <signal.h>
#include <sys/stat.h>
#include "get_next_line_bonus.h"
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include "minishell.h"



//char **ft_split(char const *s, char c);
char *ft_system(t_minishell *shell);
void ft_putstr(char *str,int fd);
char *echo(t_minishell *shell);
char *pwd(t_minishell *shell);
char *cd(t_minishell *shell);
char *export_(t_minishell *shell);
char *unset(t_minishell *shell);
char *env_(t_minishell *shell);
char *exit_(t_minishell *shell);
//void fill_dispatcher(t_minishell shell);
char *clear_(t_minishell *shell);
//void fill_list(char **var,t_minishell *shell);
t_element	*create_list(void *elt1,void *elt2, size_t data_size);
t_element	*add_end(t_element **liste, void *elt1,void *elt2, size_t data_size);
void delete_elem(char *elm,t_element *shell_);
void sort_l(t_element *list);
void filling(t_element **p,t_element *list);
#endif