/*************************************************************************
    > File Name: calc.h
    > Author: tongxianglong
    > Mail: studentTxl@163.com 
    > Created Time: Sat 18 Nov 2017 03:30:09 PM CST
 *************************************************************************/

#ifndef _CALC_H
#define _CALC_H

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define CMD_SIZE 5
typedef enum
{
	QUIT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD
}ENUM_CALC_TYPE;

typedef struct calcst
{
	int op1;
	int op2;
	ENUM_CALC_TYPE op;
}calcst;

#endif

