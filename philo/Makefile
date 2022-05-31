SOURCES = 	main.c main_helpers.c time_helpers.c initiate_variables.c \
			thread_helpers.c philo_thread.c
OBJECTS =	$(SOURCES:.c=.o)
HEADER = 	philo.h
CC = 		gcc
NAME =		philo
FLAGS =		-Wall -Wextra -Werror #-g -fsanitize=thread
VPATH = 	obj:src:hdr

.PHONY:		all re clean fclean

all:		$(NAME)

$(NAME):	$(OBJECTS)
			$(CC) $(FLAGS) $(addprefix obj/,$(OBJECTS)) $(INCLUDES) -o $@

%.o:		%.c $(HEADER)
			@mkdir -p obj
			$(CC) $(FLAGS) $< -c -o obj/$@

clean:		
			rm -rf obj/

fclean:		clean
			rm -rf $(NAME)

re:			fclean all
