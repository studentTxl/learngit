/*************************************************************************
    > File Name: ipc.h
    > Author: tongxianglong
    > Mail: studentTxl@163.com 
    > Created Time: Sun 29 Oct 2017 12:07:40 PM CST
 *************************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<sys/shm.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

//////////////////////////////////////////////////
//1  ftok

key_t Ftok(const char *pathname, int proj_id)
{
	key_t key = ftok(pathname, proj_id);
	if(key == -1)
	{
		perror("ftok.");
		exit(1);
	}
	return key;
}

///////////////////////////////////////////////////
//2   semget

int Semget(key_t key, int nsems, int semflg)
{
	int id = semget(key, nsems, semflg);
	if(id == -1)
	{
		perror("semget.");
		exit(1);
	}
	return id;
}

///////////////////////////////////////////////////
//3 Shmget

int Shmget(key_t key, size_t size, int shmflg)
{
	int id = shmget(key, size, shmflg);
	if(id == -1)
	{
		perror("shmget.");
		exit(1);
	}
	return id;
}

void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
	void *addr = shmat(shmid, shmaddr, shmflg);
	if(addr == (void*)-1)
	{
		perror("shmat.");
		exit(1);
	}
	return addr;
}


