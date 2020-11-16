SRC:= $(wildcard *.c)
OBJ:= $(patsubst *.c, *.o, $(SRC))
CC:=gcc

main: $(OBJ)
	 $(CC) -o $@ $^

clean:
		rm -f $(OBJ)main