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

  char *p;
  
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  
  return p;

}

void
find(char *path)
{
  char buf[512],buf2[512], *p;
  int fd, run=0;
  struct dirent de;
  struct stat st;
  
  if((fd = open(path, 0)) < 0){
    printf(2, "find: cannot open %s\n", path);
    return;
  }
  
  if(fstat(fd, &st) < 0){
    printf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
  
  if(st.type==T_FILE || st.type==T_DIR)
  {
	char* FileName = fmtname(path);

	int Isprint = 1;
	if((n && (strcmp(FileName,name)!=0)) ||
	   (t && type =='d' && st.type!=T_DIR) ||
	   (t && type =='f' && st.type!=T_FILE) ||
	   ((s == 1) && st.size != size) ||
	   ((s == 2) && st.size <= size) ||
	   ((s == 3) && st.size >= size))
	{
		Isprint = 0;
	}

	if (Isprint)
		printf(1, "%s %d %d %d\n", FileName, st.type, st.ino, st.size);
  }
  
  if(st.type==T_DIR)
  {
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "find: path too long\n");
      return;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de))
    {
      run++;
      if(de.inum == 0 || run<3)
        continue;

      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;

	  strcpy(buf2,buf);
	  find(buf2);
    }
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

  for(i=1; i<argc; i++)
  {
	  if(strcmp(argv[i],"-follow")==0)
	  {
		  f=1;
	  }
	  else if(strcmp(argv[i],"-help")==0)
	  	  {
		  	  printf(1,"find PATH [OPTIONS] [PREDS]\n-follow Dereference symbolic links\n-help Help\n-name filename\n-size (+/-)n\n-type c d-directory, f-regular file, s-symbolic link\n");
		  	  exit();
	  	  }
	  else if(strcmp(argv[i],"-name")==0)
	  	  {
		  	  n=1;
		  	  strcpy(name,argv[++i]);
	  	  }
	  else if(strcmp(argv[i],"-size")==0)
	  	  {
		  	  if(argv[++i][0]=='+')
		  	  {
		  		  s=2;
		  		  size=atoi(&argv[i][1]);
		  	  }
		  	  else if(argv[i][0]=='-')
		  	  {
		  		  s=3;
		  		size=atoi(&argv[i][1]);
		  	  }
		  	  else
		  	  {
		  		  s=1;
		  		size=atoi(&argv[i][0]);
		  	  }
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
