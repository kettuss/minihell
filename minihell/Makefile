NAME = minihell

HEADER = -I /include/minishell.h

SRC = ${shell find ./source -name "*.c"}

LIBFT = ../libft/libft.a

FLAGS = -Wall -Wextra -Werror -g

READLINE = -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/include/readline -lreadline

OBJ = ${SRC:.c=.o}

all : ${NAME}

%.o : %.c $(HEADER)
	gcc ${FLAGS} -c $< -o $@

${NAME} : ${SRC} ${OBJ}
	$(MAKE) -C ../libft
	gcc ${FLAGS} ${HEADER} ${SRC} ${READLINE} $(LIBFT) -o ${NAME}

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re