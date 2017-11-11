/*************************************************************************
    > File Name: cli.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Sat 11 Nov 2017 02:31:13 PM CST
 ************************************************************************/

#include"utili.h"

int main()
{
	int sockCli = socket(AF_INET, SOCK_STREAM, 0);
	if(sockCli == -1)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(SERVER_PORT);
	addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

	socklen_t len = sizeof(struct sockaddr);
	int ret = connect(sockCli, (struct sockaddr*)&addrSer, len);
	if(ret == -1)
	{
		perror("connect");
		exit(1);
	}
	else
	{
		printf("Client Connect Server Success.\n");
	}

	char sendbuf[BUFFER_SIZE];
	char recvbuf[BUFFER_SIZE];
	while(1)
	{
		recv(sockCli, recvbuf, BUFFER_SIZE, 0);
		printf("Ser:>%s\n",recvbuf);
		printf("Cli:>");
		scanf("%s", sendbuf);
		send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
	}

	close(sockCli);

	return 0;
}

