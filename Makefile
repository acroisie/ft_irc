CC = c++

CC_FLAGS = -Wall -Werror -Wextra -std=c++98

NAME := ircserv
	
SRCS := $(shell find srcs -type f -name "*.cpp" | cut -c6-)

OBJS := $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME):		$(addprefix srcs/objs/, $(OBJS)) Makefile
			$(CC) $(CC_FLAGS) $(addprefix srcs/objs/, $(OBJS)) -o $(NAME) 
srcs/objs/%.o:		srcs/%.cpp Makefile $(shell find . -type f -name "*.hpp")
				@mkdir -p srcs/objs
					$(CC) $(CC_FLAGS) -c $< -o "$@"

clean :
		rm -rf srcs/objs

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : re clean fclean all .PHONY