NAME	=	philo						

SRCS	=  	philo.c\
			utils.c\
			philo_eat.c\
			philo_time.c\
			philo_sleep.c\
			philo_mutex.c\
			philo_checks.c\
			print_helpers.c\
			council_management.c\
		
OBJS	=	$(SRCS:.c=.o)					

CC	=	cc 								

RM	=	rm -f								

CFLAGS	=	-Wall -Wextra -Werror

all	:	$(NAME)									

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -v -o $(NAME) $(OBJS)

%.o: %.c									
	$(CC) $(CFLAGS) -c $< -o $@

clean	:										
	$(RM) $(OBJS)

fclean	: clean						
	$(RM) $(NAME)

re	:	fclean all							

.PHONY	:	all clean fclean re	
