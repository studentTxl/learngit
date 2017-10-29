/*************************************************************************
    > File Name: remove_sem.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Sun 29 Oct 2017 10:41:15 PM CST
 ************************************************************************/

#include"ipc.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("<Waring:Using>: %s pathname proj_id.\n", argv[0]);
		return -1;
	}
	key_t sem_key = Ftok(argv[1], atoi(argv[2]));
	int sem_id = Semget(sem_key, 0, 0);

	int ret = semctl(sem_id, 0, IPC_RMID);
	if(ret == -1)
		printf("remove sem Error.\n");
	else
		printf("remove sem Success.\n");

	return 0;
}

