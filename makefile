BIN=TextToMorse
CC=g++
OBJ=main.o
LIB=-lwiringPi

all: $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LIB)

%.o: src/%.cpp
	$(CC) -c $<

.PHONY: clean
clean:
	rm *.o $(BIN)	
