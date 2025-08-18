TARGET = bin/http_server

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default

default: $(TARGET)
	./$(TARGET)


$(TARGET): $(OBJ)
	gcc $^ -o $@ 

$(OBJ): obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude -g

clean:
	rm -f obj/*.o
	rm -f bin/*