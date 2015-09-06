CC=gcc
OBJ=obj/utils.o obj/signal.o obj/main.o
EXEC=vcd-delay-analyzer
FLAGS=-Iinclude/

all: $(OBJ)
	$(CC) $(FLAGS) -o $(EXEC) $^

obj/%.o: src/%.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f obj/* $(EXEC)
