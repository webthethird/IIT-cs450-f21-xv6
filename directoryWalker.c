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
    struct dirent *dirents = (struct dirent*)malloc(5000 * sizeof(struct dirent));
    // struct inode *inodes = (struct inode*)malloc(200 * sizeof(struct inode));
    struct dirent de;
    struct inode in;
    int i, j;
    
    if(argc < 2) {
        argv[1] = "/";
    }
    
    printf(1, "argc: %d\nargv[1]: %s\n", argc, argv[1]);
    
    // mkdir("./foo");
    // chdir("foo");
    // mkdir("./bar");
    // chdir("bar");
    // open("./bar.txt", O_CREATE);
    // chdir("..");
    // chdir("..");
    // mkdir("./bam");
    // chdir("bam");
    // open("./boo.txt", O_CREATE);

    //test #4
    mkdir("./foo");
    chdir("foo");
    for(j = 0; j < 100; j++) {
        printf(1, "%d\n", j);
        mkdir((char*)j);
    }
    chdir("..");
        
    walkdir(argv[1], dirents);

    i = 0;
    while ((de = dirents[i]).inum != 0) {
    // for (int i = 0; i < 200 * sizeof(de); i += sizeof(de)) {
        // de = dirents[i];
        getinode(de.inum, &in);
        
        printf(1, "dirents[%d] = {inum: %d, pinum: %d, name: %s}\n", i/sizeof(struct dirent), de.inum, de.pinum, de.name);
        i += sizeof(struct dirent);
        printf(1, "inode = {dev: %d, inum: %d, type: %d, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
               in.dev, in.inum, in.type, in.nlink, in.ref, in.size, in.valid);
    }
    exit();
}