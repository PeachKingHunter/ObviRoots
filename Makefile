all: main

# Usefull commands
run: main
	./main

clean:
	rm main

# Variables
sources = src/Polynome.c
headers = src/Polynome.h

# Compile
main: src/main.c $(sources) $(headers)
	gcc -Wall -o main src/main.c $(sources) $(headers) -lraylib

# TODO: Compile for Windows
