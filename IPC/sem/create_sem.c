#include"ipc.h"
#include<sys/sem.h>

// ./create_sem mysem 0xff n

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("<Waring:Using> %s pathname proj_id init_val.\n>",argv[0]);
		return -1;
	}
	key_t sem_key = Ftok(argv[1], atoi(argv[2]));
	printf("sem key = %x\n", sem_key);

	int  sem_id = Semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0755);
	printf("sem id = %d\n", sem_id);

	union semun init;
	init.val = atoi(argv[3]);
	semctl(sem_id, 0, SETVAL, init);

	return 0;
}
