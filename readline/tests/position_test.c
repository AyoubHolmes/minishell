#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <termcap.h>
#include <signal.h>

void    ft_putstr(char *s)
{
    if (s)
    {
        while (*s)
        {
            write(1, s, 1);
            s++;
        }
    }
}

/* int ft_atoi(char *s, int *i)
{
    
} */

int main(int argc, char const *argv[])
{
    char *s;
    char cmd[]="\033[6n";

    s = malloc(8);
    tputs(tgoto(tgetstr("cm", NULL), 5, 5), 1, putchar);
    write(1, cmd, sizeof(cmd));
    read(0, s, 8);
    printf("\n\rCurrent Line: %c%c\n\r" , s[2] ,s[3] );
    printf("\n\rCurrent Column: %c\n\r" , s[5] );
    return 0;
}
