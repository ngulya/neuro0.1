NEURO = neuro

CC = gcc

FILE = 	./btc.o\
		./for_btc.o

OBJ = $(FILE:.o=.c)

all: fclean comp 

comp:
	@$(CC) $(OBJ) -lm -o $(NEURO)

fclean:
	@-/bin/rm -f $(NEURO)

re: fclean all