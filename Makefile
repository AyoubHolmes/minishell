NAME = minishell
NAME_BONUS = minishell_bonus
AR = ar rcs
SRC =	./minishell_mandatory/parsing/main.c\
	./minishell_mandatory/parsing/ft_free.c\
	./minishell_mandatory/parsing/prompt.c \
	./minishell_mandatory/parsing/lexer_helper.c\
	./minishell_mandatory/parsing/lexer.c\
	./minishell_mandatory/parsing/parser.c\
	./minishell_mandatory/parsing/list_debugger.c\
	./minishell_mandatory/parsing/pipeline_exec.c\
	./minishell_mandatory/parsing/readline_helpers.c\
	./minishell_mandatory/parsing/readline_funcs.c\
	./minishell_mandatory/parsing/readline.c\
	./minishell_mandatory/parsing/readline_utils.c\
	./minishell_mandatory/parsing/history_utils.c\
	./minishell_mandatory/parsing/err.c\
	./minishell_mandatory/parsing/arg_correction.c\
	./minishell_mandatory/parsing/get_fd_file.c\
	./minishell_mandatory/parsing/extract_filename.c\
	./minishell_mandatory/parsing/insert_cmd.c\
	./minishell_mandatory/parsing/ft_signal.c\
	./minishell_mandatory/parsing/ft_insert_args.c\
	./minishell_mandatory/minishell_exec/myshell/dispatcher.c\
	./minishell_mandatory/minishell_exec/myshell/env.c\
	./minishell_mandatory/minishell_exec/myshell/ft_system.c\
	./minishell_mandatory/minishell_exec/myshell/echo.c\
	./minishell_mandatory/minishell_exec/myshell/pwd.c\
	./minishell_mandatory/minishell_exec/myshell/cd.c\
	./minishell_mandatory/minishell_exec/myshell/export.c\
	./minishell_mandatory/minishell_exec/myshell/unset.c\
	./minishell_mandatory/minishell_exec/myshell/exit.c\
	./minishell_mandatory/minishell_exec/myshell/my_free.c\
	\
	./minishell_mandatory/minishell_exec/myshell_utils/list_env.c\
	./minishell_mandatory/minishell_exec/myshell_utils/ft_split.c\
	./minishell_mandatory/minishell_exec/myshell_utils/ft_putstr.c\
	./minishell_mandatory/minishell_exec/myshell_utils/fill_list_to_sort.c\
	\
	./minishell_mandatory/minishell_exec/myshell_utils/some_utils.c\
	./minishell_mandatory/minishell_exec/myshell_utils/regex.c\
	./minishell_mandatory/minishell_exec/myshell_utils/regex_handler.c\
	./minishell_mandatory/minishell_exec/myshell_utils/sort_file.c\

SRC_BONUS =	./minishell_bonus/parsing/main.c\
	./minishell_bonus/parsing/ft_free.c\
	./minishell_bonus/parsing/prompt.c \
	./minishell_bonus/parsing/lexer_helper.c\
	./minishell_bonus/parsing/lexer.c\
	./minishell_bonus/parsing/parser.c\
	./minishell_bonus/parsing/list_debugger.c\
	./minishell_bonus/parsing/pipeline_exec.c\
	./minishell_bonus/parsing/readline_helpers.c\
	./minishell_bonus/parsing/readline_funcs.c\
	./minishell_bonus/parsing/readline.c\
	./minishell_bonus/parsing/readline_utils.c\
	./minishell_bonus/parsing/history_utils.c\
	./minishell_bonus/parsing/err.c\
	./minishell_bonus/parsing/arg_correction.c\
	./minishell_bonus/parsing/get_fd_file.c\
	./minishell_bonus/parsing/extract_filename.c\
	./minishell_bonus/parsing/insert_cmd.c\
	./minishell_bonus/parsing/ft_signal.c\
	./minishell_bonus/parsing/ft_insert_args.c\
	./minishell_bonus/minishell_exec/myshell/dispatcher.c\
	./minishell_bonus/minishell_exec/myshell/env.c\
	./minishell_bonus/minishell_exec/myshell/ft_system.c\
	./minishell_bonus/minishell_exec/myshell/echo.c\
	./minishell_bonus/minishell_exec/myshell/pwd.c\
	./minishell_bonus/minishell_exec/myshell/cd.c\
	./minishell_bonus/minishell_exec/myshell/export.c\
	./minishell_bonus/minishell_exec/myshell/unset.c\
	./minishell_bonus/minishell_exec/myshell/exit.c\
	./minishell_bonus/minishell_exec/myshell/my_free.c\
	\
	./minishell_bonus/minishell_exec/myshell_utils/list_env.c\
	./minishell_bonus/minishell_exec/myshell_utils/ft_split.c\
	./minishell_bonus/minishell_exec/myshell_utils/ft_putstr.c\
	./minishell_bonus/minishell_exec/myshell_utils/fill_list_to_sort.c\
	\
	./minishell_bonus/minishell_exec/myshell_utils/some_utils.c\
	./minishell_bonus/minishell_exec/myshell_utils/regex.c\
	./minishell_bonus/minishell_exec/myshell_utils/regex_handler.c\
	./minishell_bonus/minishell_exec/myshell_utils/sort_file.c\

OBJECT = $(SRC:.c=.o)

OBJECT_BONUS = $(SRC_BONUS:.c=.o)

LIBFT = ./minishell_mandatory/parsing/libft

LIBFT_BONUS = ./minishell_bonus/parsing/libft

all: $(NAME)

$(NAME): $(OBJECT) $(HEADERS)
	@make -C $(LIBFT)
	@gcc -ltermcap $(OBJECT) ./minishell_mandatory/parsing/libft/libft.a -o $(NAME)

$(NAME_BONUS): $(OBJECT_BONUS) $(HEADERS_BONUS)
	@make -C $(LIBFT_BONUS)
	@gcc -ltermcap $(OBJECT_BONUS)  ./minishell_bonus/parsing/libft/libft.a -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

%.o: %.c
	@gcc -ltermcap  -o $@ -c $< 2> /dev/null


clean:
	@make fclean -sC $(LIBFT)
	@rm -f $(OBJECT) $(OBJECT_BONUS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean $(NAME) $(NAME_BONUS)