/*************************************************************************
    > File Name: ser.c
    > Author: tongxianglong
    > Mail: studentTxl@163.com 
    > Created Time: Tue 31 Oct 2017 04:58:59 PM CST
 ************************************************************************/

#include"ipc.h"
#include<sys/shm.h>

int main()
{
	key_t shm_key = Ftok("myshm", 0xff);
	printf("shm key = %x\n", shm_key);
	int shm_id = Shmget(shm_key, 1024, IPC_CREAT|IPC_EXCL|0755);
	char *addr = (char *)Shmat(shm_id, NULL, 0);

	int sem_id = Semget(shm_key, 2, IPC_CREAT|IPC_EXCL|0755);
	union semun init;
	init.val = 0;
	semctl(sem_id, 0,SETVAL, init);
	semctl(sem_id, 1,SETVAL, init);

	struct sembuf v = {0, 1, 0};
	struct sembuf p = {1,-1, 0};

	while(1)
	{
		printf("Ser:>");
		scanf("%s",addr);
		semop(sem_id, &v, 1);

		semop(sem_id, &p, 1);
		printf("Cli:> %s \n",addr);
	}

	shmdt(addr);

	semctl(sem_id, 0, IPC_RMID);
	semctl(sem_id, 1, IPC_RMID);
	int ret = shmctl(shm_id, IPC_RMID, NULL);
	if(ret == -1)
		printf("remove shm Error.\n");
	else
		printf("remove shm Success.\n");

	return 0;

}

