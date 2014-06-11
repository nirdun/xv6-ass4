#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int WriteBlock(int fd, char * buf, int n)
{
	int i;
	for(i = 0; i <n; ++i)
	{
		int k = write(fd, buf, 512);

		if(k!=512)
		{
			printf(2, "cannot write \n");
			return 0;
		}
	}

	return 1;
}



int
main(int argc, char *argv[])
{
	int fd;
	if((fd = open("./test1check.txt", O_CREATE | O_RDWR)) < 0){
			  printf(2, "cannot open \n");
			}

	char  buf[512] ="1";

	int i;
	for(i = 0; i <512; ++i)
	{
		buf[i] = 1;
	}


	if(WriteBlock(fd,buf, 12))
	{
		printf(1, "Finished writing 6KB \n");

		if(WriteBlock(fd,buf, 128))
		{
			printf(1, "Finished writing 70KB \n");

			if(WriteBlock(fd,buf, 1908))
			{
				printf(1, "Finished writing 1MB \n");

				/*
				WriteBlock(fd,buf, 2048);
				printf(1, "Finished writing 2MB \n");
				WriteBlock(fd,buf, 2048);
				printf(1, "Finished writing 3MB \n");
				WriteBlock(fd,buf, 2048);
				printf(1, "Finished writing 4MB \n");
				WriteBlock(fd,buf, 2048);
				printf(1, "Finished writing 5MB \n");
				WriteBlock(fd,buf, 2048);
				printf(1, "Finished writing 6MB \n");
				WriteBlock(fd,buf, 2048);
				printf(1, "Finished writing 7MB \n");
				if(WriteBlock(fd,buf, 2048))
				{
					printf(1, "Finished writing 8MB \n");

					if(WriteBlock(fd,buf, 200))
					{
						printf(1, "Finished writing more then 8MB \n");
					}
				} */
			}
		}
	}



  exit();
  return 0;
}


