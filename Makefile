build:
	gcc -o ./bin/main ./src/*.c -Wall -I/opt/homebrew/Cellar/raylib/4.5.0/include -I./include `pkg-config --libs --cflags raylib`

run:
	./bin/main

start:
	make build run

clean:
	rm ./bin/main
