CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
SRC = logic.c calc.c
OBJ = $(SRC:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c logic.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) all
