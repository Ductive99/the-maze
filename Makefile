build:
	gcc -Wall -Werror -Wextra -pedantic -o game src/*.c -Iinclude `sdl2-config --cflags --libs` -lm

run:
	./game

clean:
	rm game
	
