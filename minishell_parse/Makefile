NAME = minishell_parse.a
AR = ar rcs
LMLX_FLAG= -L ./minilibx_opengl_20191021 libmlx.a -L ./minilibx_mms_20200219 libmlx.dylib -framework OpenGL -framework AppKit

SRC = 	./parsing/ft_free.c\
		./parsing/main.c\
		./parsing/prompt.c \
		./parsing/get_next_line.c\
		./parsing/lexer.c\
		./parsing/list_funcs.c\
		./parsing/list_debugger.c\
		./parsing/pipeline_exec.c\
		./parsing/readline.c\
		./parsing/readline_utils.c\
		./parsing/history_utils.c\
		./parsing/err.c\

OBJECT = $(SRC:.c=.o)
LIBFT = ./parsing/libft
HEADERS = ../includes

$(NAME): $(OBJECT)
	@make -sC $(LIBFT)
	@cp ./parsing/libft/libft.a .
	@$(AR) $(NAME) $(OBJECT)



%.o: %.c
	@gcc -ltermcap -I $(HEADERS) -o $@ -c $<  2> /dev/null

all: $(NAME) 
	
clean:
	@make clean -sC $(LIBFT)
	@rm -f $(OBJECT)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)