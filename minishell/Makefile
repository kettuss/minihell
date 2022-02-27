NAME		=	minishell

SRCS_FILES	= 	source/built_in.c source/cd.c source/echo.c source/env_operation.c \
				source/exit.c source/export.c source/free.c source/init_add_env.c \
				source/main.c source/parce.c source/parce_utils.c source/path_cmp.c source/pipes.c \
				source/pipes_process.c source/pipes_utils.c source/pwd.c source/redirect_utils.c \
				source/redirects.c source/redirects_utils_two.c source/signals.c source/sorting_export.c \
				source/split_for_shell.c source/split_for_shell2.c source/unset.c source/utils.c source/space_trimmer.c

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
			$(CC) $(INCLUDE) $(READLINE) $(LIB) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

norm:
	norminette