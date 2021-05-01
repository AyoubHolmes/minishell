#include<stdio.h>
#include<signal.h>

void handle_sigint(int sig)
{
	printf("Caught signal %d\n", sig);
}

int main()
{
	signal(SIGQUIT, handle_sigint);
	while (1) ;
	return 0;
}

/* #include  <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include <unistd.h>

void     INThandler(int);

int  main(void)
{
     signal(SIGINT, INThandler);
     while (1)
          pause();
     return 0;
}

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
} */