#include "minishell.h"

t_element	*fill_list_files(DIR *direc, char *match)
{
	struct dirent	*entry;
	t_element		*files;

	files = NULL;
	entry = readdir(direc);
	while (entry)
	{
		if (match[0] != '.')
		{
			if (entry->d_name[0] == '.')
			{
				entry = readdir(direc);
				continue ;
			}
		}
		if (files == NULL)
			files = create_list(entry->d_name, NULL, 0);
		else
			files = add_end(&files, entry->d_name, NULL, 0);
		entry = readdir(direc);
	}
	return (files);
}
