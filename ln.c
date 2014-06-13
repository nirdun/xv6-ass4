#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3){
    printf(2, "Usage: ln old new\n");
    exit();
  }
  if(argv[1][0] == '-' && argv[1][1]=='s')
  {
	  if(symlink(argv[2], argv[3]) < 0)
	      printf(2, "link -s %s %s: failed\n", argv[2], argv[3]);
  }
  else if(link(argv[1], argv[2]) < 0)
    printf(2, "link %s %s: failed\n", argv[1], argv[2]);
  exit();
}
