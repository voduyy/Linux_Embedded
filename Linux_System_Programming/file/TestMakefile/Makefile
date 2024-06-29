.PHONY: file_ex clean
CC := gcc
INC_FLAGS:= -I hello.h
%.o: %.c $(INC_FLAGS)
	$(CC) -c -o $@ $< $(INC_FLAGS)
file_ex: main.o hello.o
	$(CC) -o $@ $^  $(INC_FLAGS)
clean: 
	rm -rf *.o \
	file_ex
