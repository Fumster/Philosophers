INCLUDES =		-L./libs/libft -lft
LIBFT =	./libs/libft/libft.a
SOURCES = 	main.c main_helpers.c time_helpers.c initiate_variables.c \
			thread_helpers.c philo_thread.c
OBJECTS =	$(SOURCES:.c=.o)
OBJECTS_B =	$(SOURCES_B:.c=.o)
HEADER = 	philo.h
CC = 		gcc
NAME =		philo
BONUS =		philo_b
FLAGS =		-Wall -Wextra -Werror -g -fsanitize=thread
VPATH = 	obj:src:hdr

.PHONY:		all re clean fclean libs

all:		libs $(NAME)

libs:		
			@make -C libs/libft

$(NAME):	$(OBJECTS) $(LIBFT)
			$(CC) $(FLAGS) $(addprefix obj/,$(OBJECTS)) $(INCLUDES) -o $@

bonus:		libs $(BONUS)
	
$(BONUS):	$(OBJECTS_B) $(LIBFT)
			$(CC) $(FLAGS) $(addprefix obj/,$(OBJECTS_B)) $(INCLUDES) -o $(BONUS)

%.o:		%.c $(HEADER)
			@mkdir -p obj
			$(CC) $(FLAGS) $< -c -o obj/$@

clean:		
			rm -rf obj/
			@make clean -C libs/libft

fclean:		clean
			rm -rf $(NAME)
			rm -rf $(BONUS)
			@make fclean -C libs/libft

re:			fclean all
