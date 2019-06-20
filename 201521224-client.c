// Client

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "echo_socket"

typedef struct _Msg {
	int type;
	int operator;
	double value[2];
}Msg;

int main()
{
	int s, t, len;
	struct sockaddr_un remote;
	Msg msg;
	char str[100];

	if((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	printf("Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);

	if(connect(s, (struct sockaddr *)&remote, len) == -1)
	{
		perror("connect");
		exit(1);
	}

	printf("Connected.\n");

	
	while(printf("> "), fgets(str, 100, stdin), !feof(stdin))
	{
		msg.type = 1;
		msg.operator = 2;
		msg.value[0] = 24;
		msg.value[1] = 14;

		if(send(s, &msg, sizeof(Msg), 0) == -1)
		{
			perror("send");
			exit(1);
		}

		if((t=recv(s, &msg, sizeof(Msg), 0)) > 0)
		{

			str[t] = '\0';
			printf("echo> %s", str);
		} else {
			if(t < 0)	perror("revcv");
			else		printf("Server closed connection\n");
			exit(1);
		}
	}

	close(s);

	return 0;
}
