#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int n=0; //Name
int s=0; //Size 1-Exactly, 2-More, 3-Less
int t=0; //type
int f=0; //Follow

char name[10];
int size=0;
char type;


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;
  
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  
  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
find(char *path)
{
  char buf[512],buf2[512], *p;
  int fd, run=0;
  struct dirent de;
  struct stat st;
  
  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }
  
  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  
  if(st.type==T_FILE || st.type==T_DIR)
  {
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
  }
  
  if(st.type!=T_DIR)
  {
	  close(fd);
	  return;
  }
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "find: path too long\n");
      return;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
    	run++;
      if(de.inum == 0 || run<3)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      //if(stat(buf, &st) < 0){
     //   printf(1, "ls: cannot stat %s\n", buf);
      //  continue;
     // }
     // printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
      //if(run>2 && st.type==T_DIR )
      //{
    	  strcpy(buf2,buf);
    	  find(buf2);
     // }


    }


  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;
  if(argc < 2){
    exit();
  }
  if(argc < 3){
    find(argv[1]);
	exit();
  }
  for(i=2; i<argc; i++)
  {
	  if(strcmp(argv[i],"-follow")==0)
	  {
		  f=1;
	  }
	  else if(strcmp(argv[i],"-help")==0)
	  	  {
		  	  printf(1,"something");
	  	  }
	  else if(strcmp(argv[i],"-filename")==0)
	  	  {
		  	  n=1;
		  	  strcpy(name,argv[++i]);
	  	  }
	  else if(strcmp(argv[i],"-size")==0)
	  	  {
		  	  if(argv[++i][0]=='+')
		  		  s=2;
		  	  else if(argv[i][0]=='-')
		  		  	  s=3;
		  	  else
		  		  s=1;
		  	  size=atoi(&argv[i][1]);
	  	  }
	  else if(strcmp(argv[i],"-type")==0)
	  	  {
		  	  t=1;
		  	  type=argv[++i][0];
	  	  }
  }
  find(argv[1]);
  exit();
}
