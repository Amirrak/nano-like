CC= gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
BIN= nano-like

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(BIN)

main.o : $(SRC)
	$(CC) -c $(SRC) $(CFLAGS)

clear :
	rm -f *.o $(BIN)
