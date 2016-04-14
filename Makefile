SRC=src/*.c
INC=inc/
BIN=tvm

all:
	gcc $(SRC) -o $(BIN) -I $(INC) -g -Wall

clean:
	rm -f $(BIN)
