#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFF_SIZE 1024

typedef struct{
	long data_type;
	int data_num;
	char data_buff[BUFF_SIZE];
}msg_t;

int main(int argc, char *argv[])
{
	int msqid;
	msg_t data;
	struct msqid_ds msqstat;

	if(argc < 2)
	{
		perror("parameter for teh msg type is required\n./201521224-receiver1 0\n");
		exit(1);
	}

	if(-1 == (msqid = msgget((key_t)3680, IPC_CREAT | 0666)))
	{
		perror("msgget() error");
		exit(1);
	}

	if(-1 == msgctl(msqid, IPC_STAT, &msqstat))
	{
		perror("msgctl() error");
		exit(1);
	}

	if(-1 == msgrcv(msqid, &data, sizeof(msg_t) - sizeof(long), atoi(argv[1]), IPC_NOWAIT))
	{
		perror("msgrcv() error");
		exit(1);
	}

		
	if(-1 == msgctl(msqid, IPC_STAT, &msqstat))
	{
		perror("msgctl() error");
		exit(1);
	}

	printf("%s", data.data_buff);

	return(0);
}
