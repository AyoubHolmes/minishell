#include "minishell.h"

t_element	*fill_list_files(DIR *direc)
{
	struct dirent *entry;
	t_element *files;

	files = NULL;
	entry = readdir(direc);
	while(entry)
	{
		if (files == NULL)
			files = create_list(entry->d_name, NULL, 0);
		else
			files = add_end(&files, entry->d_name, NULL, 0);
		entry = readdir(direc);
	}
	return (files);
}
