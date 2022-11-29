CC					= c++

CC_FLAGS			= -Wall -Werror -Wextra -std=c++98

NAME				= ircserv

OBJS_DIR			= srcs/objs

INC_DIR				= includes/

SRCS_DIR			= srcs/

OBJECTS_PREFIXED	= 	$(addprefix , $(OBJS))

OBJS				= 	$(SRCS:.cpp=.o)

SRCS				=	$(shell find . -type f -name "*.cpp")

INC					=	$(shell find . -type f -name "*.hpp")

all: $(NAME)

$(NAME): $(OBJECTS_PREFIXED)
	$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)%.cpp Makefile $(INC) | $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re