CC=gcc  #compiler
TARGET= UnixLs

all:
	$(CC) UnixLs.c infodemo.c -lm -o $(TARGET)
valgrind:
	

clean:
	rm $(TARGET)
