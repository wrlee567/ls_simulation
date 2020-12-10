CC=gcc  #compiler
TARGET= UnixLs

all:
	$(CC) ls_imp.c -lm -o $(TARGET)
	

clean:
	rm $(TARGET)