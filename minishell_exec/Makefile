NAME = minishell_exec.a
AR = ar rcs
FLAGS = 
SRC  =	myshell/dispatcher.c\
		myshell/env.c\
		myshell/ft_system.c\
		myshell/echo.c\
		myshell/pwd.c\
		myshell/cd.c\
		myshell/export.c\
		myshell/unset.c\
		myshell/exit.c\
		\
		myshell_utils/list_env.c\
		myshell_utils/ft_split.c\
		myshell_utils/ft_putstr.c\
		myshell_utils/fill_list_to_sort.c\
		\
		myshell_utils/some_utils.c\
		#get_next_line/get_next_line_bonus.c\


HEADERS = ../includes

OBJECT = $(SRC:.c=.o)

$(NAME): $(OBJECT)
	@$(AR) $(NAME) $(OBJECT)
	#@gcc $(FLAGS) minishell.a -o miniSHELL

%.o: %.c
	@gcc $(FLAGS) -I $(HEADERS) -D BUFFER_SIZE=1  -o $@ -c $<

all: $(NAME) 
	
clean:
	@rm -f $(OBJECT)
	@rm -f miniSHELL

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)