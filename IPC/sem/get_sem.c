/*************************************************************************
    > File Name: getsem.c
    > Author: tongxianglong
    > Mail: studentTxl@163.com 
    > Created Time: Mon 30 Oct 2017 04:50:46 PM CST
 ************************************************************************/

#include"ipc.h"

// ./set_sem mysem 0xff 5

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("<Waring:Using>: %s pathname proj_id.\n", argv[0]);
		return -1;
	}
	key_t sem_key = Ftok(argv[1], atoi(argv[2]));
	int sem_id = Semget(sem_key, 0, 0);

	int sem_val = semctl(sem_id, 0, GETVAL);
	if(sem_val == -1)
		printf("get sem Error.\n");
	else
		printf("sem value = %d\n", sem_val);

	return 0;
}

