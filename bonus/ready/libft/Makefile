SRCS 	= 	ft_bzero.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_substr.c\
		ft_strtrim.c\
		ft_strrchr.c\
		ft_strnstr.c\
		ft_strncmp.c\
		ft_strmapi.c\
		ft_strlen.c\
		ft_memcmp.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strjoin.c\
		ft_striteri.c\
		ft_strdup.c\
		ft_strchr.c\
		ft_split.c\
		ft_atoi.c\
		ft_putstr_fd.c\
		ft_putnbr_fd.c\
		ft_putendl_fd.c\
		ft_putchar_fd.c\
		ft_memset.c\
		ft_memmove.c\
		ft_memcpy.c\
		ft_memchr.c\
		ft_itoa.c\
		ft_isprint.c\
		ft_isdigit.c\
		ft_isascii.c\
		ft_isalpha.c\
		ft_isalnum.c\
		ft_calloc.c\

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CC	= cc

HEADER	= libft.h

LIBCC	= ar rc

CFLAGS	= -Wall -Wextra -Werror

.c.o:	$(HEADER)
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	${LIBCC} $(NAME) $(OBJS)

clean:
	@rm -rf ${OBJS}

fclean:	clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus