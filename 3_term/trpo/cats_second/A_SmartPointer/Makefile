CC=clang
CFALGS=-Wall -Werror -g -fsanitize=address

all: main.cpp SmartPointer.hpp
	$(CC) -Wall -Werror -g -fsanitize=address main.cpp -o sp.exe

clean: 
	del sp.exe
