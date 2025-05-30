NAME = philo
CC = cc
SRC_DIR = source
OBJS_DIR  = objects

HEADERS	:= -I ./include 
CFLAGS = -Wall -Wextra -Werror -g 

SRCS =	main.c \
		$(SRC_DIR)/ft_atoi.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)
all: $(NAME)


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) 
	@$(CC) $(OBJS)  $(HEADERS) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re fclean clean