NAME = servemv

smv:
	@echo "-------- servemv --------"
	@echo "cool web server made in c"
	@echo "-------------------------"
	@echo "* make install"
	@echo "  installs the server"
	@echo ""
install:
	make server && sudo cp $(NAME) /usr/bin/$(NAME)

server:
	clang server.c -o $(NAME) -std=c99