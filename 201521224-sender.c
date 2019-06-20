#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFF_SIZE 1024

typedef struct{
	long data_type;
	int data_num;
	char data_buff[BUFF_SIZE];
}msg_t;

int main()
{
	int msqid, msqid2;
	int ndx = 0;
	int ndx2 = 0;
	msg_t data;

	if(-1 == (msqid = msgget((key_t)3680, IPC_CREAT | 0666)))
	{
		perror("msgget() error");
		exit(1);
	}

	if(-1 == (msqid2 = msgget((key_t)2600, IPC_CREAT | 0666)))
	{
		perror("msgget() error");
		exit(1);
	}

//	while(1)
//	{
//		data.data_type = (ndx++ % 3) + 1;
//		data.data_num = ndx;

//		sprintf(data.data_buff, "type=%ld, ndx=%d", data.data_type, ndx);
		sprintf(data.data_buff, "Queue1\n");

		if(-1 == msgsnd(msqid, &data, sizeof(msg_t) - sizeof(long), IPC_NOWAIT))
		{
			perror("msgsnd() error");
			exit(1);
		}

		sprintf(data.data_buff, "Queue2\n");

		if(-1 == msgsnd(msqid2, &data, sizeof(msg_t) - sizeof(long), IPC_NOWAIT))
		{
			perror("msgsnd() error");
			exit(1);
		}
		sleep(1);
//	}
	return(0);
}
