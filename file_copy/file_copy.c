#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[])
{
	int chose, fd1, fd2;
	char buff[20];

	while((chose = getopt(argc,argv,"s:d:")) != -1)
	{
		switch(chose)
		{
			case 's':
				fd1 = open(optarg, O_RDONLY);
				if(fd1 < 0)
				{
					printf("open sorce file failed.\n");
					return -1;
				}
				break;
			case 'd':
				fd2 = open(optarg, O_WRONLY|O_CREAT|O_TRUNC, 0755);
				if(fd2 < 0) 
				{
					printf("open dest failed.\n");
					return -1;
				}
				break;
			case '?':
				printf("useless commend:-%c !.\n",optopt);
				return 0;
			case ':':
				printf("%s Lack of options.\n", optopt);
				return 0;
		}
	}

	while((chose = read(fd1, buff, 20)) !=0)
		write(fd2,buff,chose);

	close(fd1);
	close(fd2);
}
