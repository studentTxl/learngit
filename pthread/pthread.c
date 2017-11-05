/*************************************************************************
    > File Name: pthread.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri 03 Nov 2017 04:08:46 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define COUNT 10
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *A_fun(void *arg)
{
	int i;
	for(i=1, i<=count, ++i)
	{
		//jiasuo
		pthread_mutex_lock(&mutex)
		if(i%2 == 1)
		{
			printf("%d", i);
		}
		//dengdai
		//

	}
}

void *B_fun(void *arg)
{
	int i;
	for(i=1, i<=count, ++i)
	{
		//jiasuo
		if(i%2 == 0)
		{
			printf("%d", i);
		}
		//jiesuo
	}

}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL,A_fun, NULL);
	pthread_create(&tid2, NULL,B_fun, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}
