NAME = pipex

SRC = main.c \

DIR 		= ${addprefix srcs/,${SRC}}

HEAD		= -I ft

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

OBJS		= ${DIR:.c=.o}

FT_FLAG		= -L ft -lft

all: $(NAME)

$(NAME): $(OBJS)
	make -C ft
	$(CC) $(CFLAGS) $(FT_FLAG) $(OBJS) -o $(NAME) 

.c.o:
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean:
	make clean -C ft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
