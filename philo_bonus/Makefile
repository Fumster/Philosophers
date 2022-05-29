INCLUDES =		-L./libs/libft -lft
LIBFT =	./libs/libft/libft.a
SOURCES = 	main.c main_helpers.c time_helpers.c initiate_variables.c \
			process_helpers.c philo_thread.c
OBJECTS =	$(SOURCES:.c=.o)
HEADER = 	philo.h
CC = 		gcc
NAME =		philo_bonus
FLAGS =		-Wall -Wextra -Werror #-g -fsanitize=thread
VPATH = 	obj:src:hdr

.PHONY:		all re clean fclean libs

all:		libs $(NAME)

libs:		
			@make -C libs/libft

$(NAME):	$(OBJECTS) $(LIBFT)
			$(CC) $(FLAGS) $(addprefix obj/,$(OBJECTS)) $(INCLUDES) -o $@

%.o:		%.c $(HEADER)
			@mkdir -p obj
			$(CC) $(FLAGS) $< -c -o obj/$@

clean:		
			rm -rf obj/
			@make clean -C libs/libft

fclean:		clean
			rm -rf $(NAME)
			@make fclean -C libs/libft

re:			fclean all
