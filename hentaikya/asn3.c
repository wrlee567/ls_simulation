#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "list.h"

struct PCB {
    int PID;
    int priority;
	int state;
	char* msg;

};


int main(int argc, char const *argv[])
{
	void* pr_1 = List_create();
	void* pr_2 = List_create();
	void* pr_3 = List_create();
	void* wait_send = List_create();
	void* wait_rec = List_create();



	char u_input; 
	printf(" Please enter your command ('i' for the information on the commands, 'e' to exit the program): ");
        scanf(&u_input);
	return 0;
}



