NAME = minishell
AR = ar rcs
SRC =	./parsing/main.c\
	./parsing/ft_free.c\
	./parsing/prompt.c \
	./parsing/lexer_helper.c\
	./parsing/lexer.c\
	./parsing/parser.c\
	./parsing/list_debugger.c\
	./parsing/pipeline_exec.c\
	./parsing/readline_helpers.c\
	./parsing/readline_funcs.c\
	./parsing/readline.c\
	./parsing/readline_utils.c\
	./parsing/history_utils.c\
	./parsing/err.c\
	./parsing/arg_correction.c\
	./parsing/get_fd_file.c\
	./parsing/extract_filename.c\
	./parsing/insert_cmd.c\
	./parsing/ft_signal.c\
	./parsing/ft_insert_args.c\
	./minishell_exec/myshell/dispatcher.c\
	./minishell_exec/myshell/env.c\
	./minishell_exec/myshell/ft_system.c\
	./minishell_exec/myshell/echo.c\
	./minishell_exec/myshell/pwd.c\
	./minishell_exec/myshell/cd.c\
	./minishell_exec/myshell/export.c\
	./minishell_exec/myshell/unset.c\
	./minishell_exec/myshell/exit.c\
	./minishell_exec/myshell/my_free.c\
	\
	./minishell_exec/myshell_utils/list_env.c\
	./minishell_exec/myshell_utils/ft_split.c\
	./minishell_exec/myshell_utils/ft_putstr.c\
	./minishell_exec/myshell_utils/fill_list_to_sort.c\
	\
	./minishell_exec/myshell_utils/some_utils.c\
	./minishell_exec/myshell_utils/regex.c\
	./minishell_exec/myshell_utils/regex_handler.c\
	./minishell_exec/myshell_utils/sort_file.c\

OBJECT = $(SRC:.c=.o)
LIBFT = ./parsing/libft
HEADERS = ./includes

$(NAME): $(OBJECT) $(HEADERS)
	@make -C $(LIBFT)
	@gcc -ltermcap $(OBJECT) ./parsing/libft/libft.a -o $(NAME)

%.o: %.c
	@gcc -ltermcap -I $(HEADERS) -o $@ -c $< 2> /dev/null

all: $(NAME)

clean:
	@make fclean -sC $(LIBFT)
	@rm -f $(OBJECT)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)
