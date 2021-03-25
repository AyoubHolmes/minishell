NAME = minishell
AR = ar rcs

PARSE = ./minishell_parse
EXEC = ./minishell_exec

$(NAME): 
	@make -sC $(PARSE)
	@make -sC $(EXEC)
	@mv ./minishell_parse/libft.a .
	@mv ./minishell_parse/minishell_parse.a .
	@mv ./minishell_exec/minishell_exec.a .
	@gcc $(FLAGS) minishell_exec.a minishell_parse.a libft.a -o $(NAME)
	


all: $(NAME) 
	
clean:
	@make clean -sC $(PARSE)
	@make clean -sC $(EXEC)
	@rm minishell_parse.a minishell_exec.a libft.a

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)