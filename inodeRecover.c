/*
test program by:
William Bodell - CWID: A20465701
Josh Greenberg - CWID: A20472596
*/

#include "types.h"
#include "user.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "fcntl.h"

int main(int argc, char const *argv[])
{
  struct dirent *dirents = (struct dirent*)malloc(1000 * sizeof(struct dirent));
  int *inodes = (int *)malloc(200 * sizeof(int));
  struct dirent de;
  int in;
  char* itype;
  int i, d, found;

  //test #1
  mkdir("./foo");
  chdir("foo");
  mkdir("./bar");
  chdir("bar");
  open("./bar.txt", O_CREATE);
  chdir("..");
  chdir("..");
  mkdir("./bam");
  chdir("bam");
  open("./boo.txt", O_CREATE);
  chdir("..");

  //test #2
  /*
  mkdir("./foo");
  */

  //test #3
  /*
  mkdir("./foo");
  chdir("foo");
  mkdir("./foo");
  chdir("foo");
  mkdir("./foo");
  chdir("foo");
  */

  printf(1, "File system initialized.");

  eraseinode(1, 25); //erase the "foo" directory

  printf(1, "Checking file system integrity... (erased an inode)");

  walkinodetb(1, inodes);
  walkdir("/", dirents);

  printf(1, "Successfully walked the inode table and the file system tree.");

  //find the inum that the directory walker found, but that had been deleted from the inode table
  d = 0;
  while ((de = *(dirents + d)).inum != 0) {
    i = 0;
    found = 0;
    while((in = *(inodes + i)) != 0) {
      if (in == de.inum)
      {
        found = 1;
        break;
      }
      i++;
    }
    if (!found)
    {
      printf(1, "Failed to locate inode for directory %s, attaching to inum%d\n", de.name, de.inum);
     fixdirnode(1, de.inum); 
     printf(1, "Okay, fixed directory inode, reattached data blocks.");
    } else {
      printf(1, "Confirmed that inode %d corresponds to file %s\n", de.inum, de.name);
    }
    d += sizeof(struct dirent);
  }

  free(dirents);
  free(inodes);

  exit();
}