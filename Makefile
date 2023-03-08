NAME = pipex

SRC = main.c \
	utils.c \

DIR 		= ${addprefix srcs/,${SRC}}

INCLUDE_DIR	= -I ft

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

OBJS		= ${DIR:.c=.o}

FT_LIB	= -L ft -lft

all: $(NAME)

$(NAME): $(OBJS)
	make -C ft
	$(CC) $(CFLAGS) $(OBJS) $(FT_LIB) -o $(NAME) 

.c.o:
	${CC} ${CFLAGS} ${INCLUDE_DIR} -c $< -o ${<:.c=.o}

clean:
	make clean -C ft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
