#include "minishell.h"

void edit_elem(char *elm1,char *elm2,t_element **shell_)
{
	t_element *list;

	list = *shell_;
	if(list == NULL)
		return;
	while(list->next)
	{
		if(strcmp(list->next->obj1,elm1) == 0)
			{
				list->next->obj2 = elm2;
				return;
			}
		list = list->next;
	}
}

char *ft_cases(char *case_,char *oldpwd,char *pwd)
{
	if(strcmp(case_,"~") == 0 ||strcmp(case_,"~/") == 0)
		return("/Users/shikma");
	else if(strcmp(case_,"-") == 0 && oldpwd == NULL)
	{
		ft_putstr("bash: cd: OLDPWD not set\n",1);
		return (NULL);
	}
	else if(strcmp(case_,"-") == 0 && oldpwd != NULL)
	{
		ft_putstr(oldpwd,1);
		ft_putstr("\n",1);
		return(oldpwd);
	}
	return(case_);
}
char *cd(t_minishell *shell) 
{
	char *s;
	DIR *folder;
	char *cwd;
	char *oldpwd;

	cwd = (char *)malloc(PATH_MAX);
	oldpwd = getcwd(cwd, PATH_MAX);
	s = shell->args->arg;
	s = ft_cases(shell->args->arg, shell->oldpwd->obj2,s);
	if (s != NULL)
	{
		folder = opendir(s);
		chdir(s);
		if(folder == NULL)
		{
			ft_putstr("ayoub-shell: cd: ",1);
			ft_putstr(s,1);
			ft_putstr(": ",1);
			ft_putstr(strerror(errno),1);
			ft_putstr("\n",1);
		}
		else
			shell->oldpwd->obj2 = oldpwd;
		free(cwd);
	}
	return("");
}