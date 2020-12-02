CC=gcc  #compiler
TARGET= UnixLs

all:
	$(CC) UnixLs.c -o $(TARGET)
valgrind:
	

clean:
	rm $(TARGET)
