/*************************************************************************
    > File Name: cli.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Sat 18 Nov 2017 03:43:34 PM CST
 ************************************************************************/
#include"calc.h"
// ./cli ip port

int main(int argc, char *argv[])
{
	int sockCli = socket(AF_INET, SOCK_STREAM, 0);
	if(sockCli == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_addr.s_addr = inet_addr(argv[1]);
	addrSer.sin_port = htons(atoi(argv[2]));

	socklen_t len = sizeof(struct sockaddr);
	int ret = connect(sockCli, (struct sockaddr *)&addrSer, len);
	if(ret == -1)
	{
		perror("connect");
		close(sockCli);
		return -1;
	}
	else
	{
		printf("Connect Server Success.\n");
	}

	calcst oper;
	int result;
	int ret_byte_size;
	char cmd[CMD_SIZE];
	while(1)
	{
		printf("please input cmd:>");
		scanf("%s", cmd);
		printf("please input op1 andd op2:>");
		scanf("%d %d",&oper.op1, &oper.op2);
		if(strcmp(cmd,"add") == 0)
			oper.op = ADD;
		else if(strcmp(cmd,"sub") == 0)
			oper.op = SUB;
		else if(strcmp(cmd,"mul") == 0)
			oper.op = MUL;
		else if(strcmp(cmd,"div")== 0)
			oper.op = DIV;
		else if(strcmp(cmd,"mod") == 0)
			oper.op = MOD;
		else if(strcmp(cmd,"quit") == 0)
			break;
		
		ret_byte_size = send(sockCli, &oper, sizeof(oper), 0);
		if(ret_byte_size < 0)
		{
			perror("send data error.\n");
			continue;
		}
		ret_byte_size = recv(sockCli, &result, sizeof(result), 0);
	    if(ret_byte_size < 0)
		{
			perror("recv data error.\n");
			continue;
		}
		printf("result = %d\n", result);
	}

	close(sockCli);
	printf("system quit ...\n");
	return 0;
}
