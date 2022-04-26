NAME = httpServer

PARSE = parseConfigeFile.cpp httpWebServer.cpp server.cpp serverRequest.cpp serverResponce.cpp

SRCS = main.cpp httpWebServer.cpp server.cpp serverRequest.cpp serverResponce.cpp

FLAGS = -Wall -Werror -Wextra

all : $(NAME)
	clang++ --std=c++98 $(FLAGS) $(SRCS)

parse : $(NAME)
	clang++ --std=c++98 $(PARSE)
clean:
	rm -rf $(NAME)
fclean: clean
	rm -rf $(NAME)
re: clean fclean