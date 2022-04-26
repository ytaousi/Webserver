NAME = httpServer

PARSE = parseConfigFile.cpp httpWebServer.cpp server.cpp serverRequest.cpp parseUtils.cpp

SRCS = main.cpp httpWebServer.cpp server.cpp serverRequest.cpp

FLAGS = -Wall -Werror -Wextra

all : $(NAME)
	
$(NAME) :
	clang++ --std=c++98 $(SRCS)
parse :
	clang++ --std=c++98 $(PARSE)
clean:
	rm -rf $(NAME)
fclean: clean
	rm -rf $(NAME)
re: clean fclean