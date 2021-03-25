#include "includes.h"
int ft_find_elem(char *elm1,char *elm2,t_element **shell_)
{
	t_element *list;

	list = *shell_;
	if(list == NULL)
		return(0);
	while(list->next)
	{
		if(strcmp(list->next->obj1,elm1) == 0)
			{
				list->next->obj2 = elm2;
				return(1);
			}
		list = list->next;
	}
	return(0);
}
char *ft_cases(char *case_,int id,char *oldpwd,char *pwd)
{
	printf("%d\n",id);
	if(strcmp(case_,"~") == 0 ||strcmp(case_,"~/") == 0)
		return("/Users/shikma");
	else if(strcmp(case_,"-") == 0 && id == 3)
		printf("bash: cd: OLDPWD not set\n");
	else if(strcmp(case_,"-") == 0 && id == 1)
		return(oldpwd);
	return(pwd);
}
char *cd(t_minishell *shell) 
{
		char *s = shell->args->arg;
		char *oldpwd;
		DIR *folder = opendir(s);
		char cwd[PATH_MAX];
		int i;
		if(folder == NULL)
		{
			ft_putstr("bash: cd: ",1);
			ft_putstr(s,1);
			ft_putstr(": No such file or directory\n",1);
			return("");
		} 
		else
		{
   			if (getcwd(cwd, sizeof(cwd)) != NULL)
				oldpwd = ft_strdup(cwd);
			i = ft_find_elem("OLDPWD",oldpwd,&shell->shell);
			s = ft_cases(s,3,oldpwd,cwd);
			if(i == 0)
				shell->shell = add_end(&shell->shell,"OLDPWD",oldpwd, sizeof(char *));
			chdir(s);
		}
		return("");
}