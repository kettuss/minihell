NAME		=	minishell

SRCS_FILES	= 	${shell find ./source -name "*.c"}

SRCS_FOLDER	=	source/

SRCS		= 	$(SRCS_FILES)
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

READLINE = -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline

INCLUDE		=	-I./include -I./../libft/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

LIB = ../libft/libft.a

.PHONY:		all clean fclean re bonus

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c -g $< -o $@ 
$(NAME):	$(OBJS)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) $(LIB) ${READLINE} -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

norm:
	norminette