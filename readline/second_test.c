#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <termcap.h>
#include <signal.h>

struct termios saved_attributes;

void    reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void    set_input_mode (void)
{
  struct termios tattr;
  char *name;

  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (1);
    }
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON); /* Clear ICANON and ECHO. */
  tattr.c_lflag &= ~(ECHO); /* Clear ICANON and ECHO. */
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

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
void handler(int sig)
{

    printf("here i am ");
    signal(SIGINT,SIG_IGN);
  
}

int is_up_or_down(int c)
{
  return ((c&0xFF) == 27 && ((c >> 8)&0xFF) == 91 && ((c >> 24)&0xFF) == 0);
}


int main(int argc, char const *argv[])
{
	int ret;
	int column_count;
	int line_count;
	char *cl_cap;
  int c;

	ret = init_term();
  set_input_mode ();
	if (ret == 0)
	{
        while (1)
        {
            //printf("game starts\n");
            column_count = tgetnum("co");
            line_count = tgetnum("li");
            //printf("columns and lines %d ----- %d\n", column_count, line_count);
            // if (!tgetflag("cl"))
            //     printf("no man\n");
            // else
            //     printf("yes man\n");
            // tputs(tgoto(cl_cap, 10, 18), 1, putchar);
            // printf("yes man\n");
            // signal(SIGINT,handler); 
            c = 0;
            read (STDIN_FILENO, &c, 4);
            if (is_up_or_down(c))
            {
              // tputs(tgoto(tgetstr("cm", NULL), 0, 5), 1, putchar);
              cl_cap = tgetstr("le", NULL);
              tputs(cl_cap, 1, putchar);
              if (((c >> 16)&0xFF) == 65)
                write(1, "U", 1);
              else if (((c >> 16)&0xFF) == 66)
                 write(1, "D", 1);
            }
            else
              write(1, &c, 4);
        }
	}
    return 0;
}
// gcc -ltermcap first_test.c
