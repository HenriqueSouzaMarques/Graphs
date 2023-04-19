CC = gcc
FLAGS = -g -Wall -Werror

OBJS = main.o user.o graph.o queue.o
BIN = main

all: $(OBJS)
	$(CC) -o $(BIN) $(FLAGS) $(OBJS) && rm $(OBJS)

main.o: main.c Includes/user.h
	$(CC) -c $(FLAGS) main.c

user.o:	src/user.c Includes/user.h
	$(CC) -c $(FLAGS) src/user.c

graph.o: src/graph.c src/utils.c Includes/graph.h
	$(CC) -c $(FLAGS) src/graph.c

queue.o: src/queue.c Includes/queue.h
	$(CC) -c $(FLAGS) src/queue.c

run:
	./$(BIN)

clean:
	rm $(BIN)