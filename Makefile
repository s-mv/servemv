NAME = servemv

server:
	clang server.c -o $(NAME) -std=c99

install:
	make server && sudo cp $(NAME) /usr/bin/$(NAME)