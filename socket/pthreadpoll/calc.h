/*************************************************************************
    > File Name: calc.h
    > Author: tongxianglong
    > Mail: studentTxl@163.com 
    > Created Time: Sun 26 Nov 2017 05:39:38 PM CST
 ************************************************************************/

#ifndef _CALC_H
#define _CALC_H

#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

typedef enum {QUIT, ADD, SUB, MUL, DIV, MOD}ENUM_CALC_TYPE;

#define CMD_SIZE 5

typedef struct calcst
{
	int op1;
	int op2;
	ENUM_CALC_TYPE op;
}calcst;

#endif

