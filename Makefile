CC					= c++

CC_FLAGS			= -Wall -Werror -Wextra -std=c++98

NAME				= ircserv

OBJS_DIR			= srcs/objs

INC_DIR				= includes/

SRCS_DIR			= srcs/

OBJECTS_PREFIXED	= $(addprefix $(OBJS_DIR)/, $(OBJS))

OBJS				= $(SRCS:.cpp=.o)

<<<<<<< HEAD
SRCS				=	main.cpp \
						Utils.cpp \
						Server.cpp

=======
SRCS				=	Client.cpp \
						main.cpp \
						Server.cpp

INC					=	$(INC_DIR)Client.hpp \
						$(INC_DIR)Server.hpp \
						$(INC_DIR)Utils.hpp

>>>>>>> lNW/master
all: $(NAME)

$(NAME): $(OBJECTS_PREFIXED)
	$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

<<<<<<< HEAD
$(OBJS_DIR)/%.o: $(SRCS_DIR)%.cpp Makefile $(shell find . -type f -name "*.hpp") | $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@ -I
=======
$(OBJS_DIR)/%.o: $(SRCS_DIR)%.cpp Makefile $(INC) | $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@ -I $(INC_DIR)

>>>>>>> lNW/master
clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
