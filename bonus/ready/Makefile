SRCS	= utils/free_all.c\
		utils/parser.c\
		utils/main.c\
		utils/processes.c\
		utils/ft_split_ppx.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c\

SRCS_BONUS = bonus_utils/free_all_bonus.c\
		bonus_utils/parser_1_bonus.c\
		bonus_utils/parser_2_bonus.c\
		bonus_utils/proccess_part_1_bonus.c\
		bonus_utils/process_part_2_bonus.c\
		bonus_utils/ft_split_ppx_bonus.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c\
		
OBJS		= ${SRCS:.c=.o}

OBJS_BONUSES 	= ${SRCS_BONUS:.c=.o}

NAME		= pipex

HEADER		= utils/pipex.h

HEADER_BONUS	= bonus_utils/pipex_bonus.h

HEADER_2	= get_next_line/get_next_line.h

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

INCLUDES 	= libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(HEADER_2)
	make -C libft/
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(INCLUDES)

bonus: $(OBJS_BONUSES) $(HEADER_BONUS) $(HEADER_2)
	make -C libft/
	$(CC) $(OBJS_BONUSES) -o $(NAME) $(FLAGS) $(INCLUDES)

clean:
	@rm -rf ${OBJS} ${OBJS_BONUSES}
	@make -C libft/ clean

fclean:	clean
	@rm -rf ${NAME}
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re bonus
