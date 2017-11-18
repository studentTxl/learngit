/*************************************************************************
    > File Name: ser.c
    > Author: tongxianglong
    > Mail: studentTxl@163.com 
    > Created Time: Sat 11 Nov 2017 11:20:19 AM CST
 ************************************************************************/

#include"utili.h"
#include"calc.h"

void process_hander(int sockConn);

int main(int argc, char *argv[])
{
	int sockSer = socket(AF_INET, SOCK_STREAM, 0);
	if(sockSer == -1)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addrSer, addrCli;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(SERVER_PORT);
	addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

	socklen_t len = sizeof(struct sockaddr);
	int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
	if(ret == -1)
	{
		perror("bind");
		exit(1);
	}

	ret = listen(sockSer, LISTEN_QUEUE_SIZE);
	if(ret == -1)
	{
		perror("listen");
		exit(1);
	}
	
	len = sizeof(struct sockaddr);
	int sockConn;
	while(1)
	{
		sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
		if(sockConn == -1)
		{
			perror("Accept Client Connect Error.");
			continue;
		}
		else
		{
			printf("*************************\n");
			printf("* ip = %s", inet_ntoa(addrCli.sin_addr));
			printf("* port = %d\n", ntohs(addrCli.sin_port));
			printf("*************************\n");

			pid_t pid =fork();
			if(pid == 0)
			{
				process_hander(sockConn);
			}
			else if(pid > 0)
			{
				close(sockConn);
			}
			else
			{
				perror("fock process.");
			}
		}
	}

	close(sockSer);
	return 0;
}


void process_hander(int sockConn)
{
	int ret_byte_size;
	int result;
	calcst oper;
	while(1)
	{
		ret_byte_size = recv(sockConn, &oper, sizeof(oper), 0);
		if(ret_byte_size < 0)
		{
			perror("recv data error.\n");
			continue;
		}
		if(oper.op == ADD)
			result = oper.op1 + oper.op2;
		else if(oper.op == SUB)
			result = oper.op1 - oper.op2;
		else if(oper.op == MUL)
			result = oper.op1 * oper.op2;
		else if(oper.op == DIV)
			result = oper.op1 / oper.op2;
		else if(oper.op == MOD)
			result = oper.op1 % oper.op2;
		else if(oper.op == QUIT)
		{
			printf("Client Quit\n");
			break;
		}

		ret_byte_size = send(sockConn, &result, sizeof(result), 0);
		if(ret_byte_size < 0)
		{
			perror("send data error");
			continue;
		}
	}
	close(sockConn);
}

