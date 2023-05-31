CC = gcc
FLAGS = -g -Wall -Werror

OBJS = main.o user.o graph.o stack.o queue.o
BIN = main

all: $(OBJS)
	$(CC) -o $(BIN) $(FLAGS) $(OBJS) && rm $(OBJS)

main.o: main.c Includes/user.h
	$(CC) -c $(FLAGS) main.c

user.o:	src/user.c Includes/user.h
	$(CC) -c $(FLAGS) src/user.c

graph.o: src/graph.c src/queue.c src/stack.c Includes/graph.h
	$(CC) -c $(FLAGS) src/graph.c

queue.o: src/queue.c Includes/queue.h
	$(CC) -c $(FLAGS) src/queue.c

stack.o: src/stack.c Includes/stack.h
	$(CC) -c $(FLAGS) src/stack.c

run:
	./$(BIN)

valgrind:
	valgrind ./$(BIN)

clean:
	rm $(BIN)
