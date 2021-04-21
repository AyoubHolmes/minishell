#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int init_term()
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
		printf("NO ACCESS TO TERMCAPS DB\n");
		return(-1);
	}
	if (ret == 0)
	{
		printf("Terminal type %s not found\n", term_type);
		return(-1);
	}
	return(0);
}

int main(int argc, char const *argv[])
{
	int ret;
	int column_count;
	int line_count;
	char *cl_cap;

	ret = init_term();
	if (ret == 0)
	{
		cl_cap = tgetstr("md", NULL);
		tputs(cl_cap, 1, putchar);
		cl_cap = tgetstr("us", NULL);
		tputs(cl_cap, 1, putchar);
		cl_cap = tgetstr("cm", NULL);
		printf("game starts\n");
		column_count = tgetnum("co");
		line_count = tgetnum("li");
		printf("columns and lines %d ----- %d\n", column_count, line_count);
		if (!tgetflag("cl"))
			printf("no man\n");
		else
			printf("yes man\n");
		tputs(tgoto(cl_cap, 10, 18), 1, putchar);
		printf("yes man\n");
	}
    return 0;
}
// gcc -ltermcap first_test.c
