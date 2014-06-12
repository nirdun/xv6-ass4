#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char buf[512];

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0)
    write(1, buf, n);
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{

  if(argc != 3){
    printf(2, "miss paramters...\n");
    exit();
  }

  char * path = argv[2];
  char * pass = argv[1];

  if(fprot(path, pass) < 0)
  {
	  printf(2, "error fprot...\n");
  }


  if(fork() == 0)
  {
	  if(funlock(path,pass	) < 0)
	  {
		  printf(2, "error funlock...\n");
	  }

	  int fd;
	  if((fd = open(path, 0)) < 0){
	    printf(2, "cannot open child mode %s\n", path);

	    exit();
	  }
	  cat(fd);
	  close(fd);
  }
  else
  {
	  wait();

	  int fd;
	  if((fd = open(path, 0)) < 0){
		printf(2, "cannot open father mode %s\n", path);
	  }

	  funprot(path,pass);
  }


  exit();
}
