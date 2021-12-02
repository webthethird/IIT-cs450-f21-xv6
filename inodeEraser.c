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
    struct dirent de;
    struct inode in;
    int i, inum;
    
    if(argc < 2) {
        argv[1] = "/";
    }
    
    printf(1, "argc: %d\nargv[1]: %s\n", argc, argv[1]);
    char *eraserhead = "foo";
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

    walkdir(argv[1], dirents);

    i = 0;
    while ((de = dirents[i]).inum != 0) {
        getinode(de.inum, &in);
        
        printf(1, "dirents[%d] = {inum: %d, pinum: %d, name: %s}\n", i/sizeof(struct dirent), de.inum, de.pinum, de.name);
        //if (strcmp(de.name, eraserhead))
        //{
        //  inum = de.inum;
        //}
        i += sizeof(struct dirent);
        printf(1, "inode = {dev: %d, inum: %d, type: %s, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
               in.dev, in.inum, in.type, in.nlink, in.ref, in.size, in.valid);
    }
    free(dirents);
    eraseinode(1, 24);

    //okay let's try it again
    dirents = (struct dirent*)malloc(1000 * sizeof(struct dirent)); //reallocate 
    walkdir(argv[1], dirents);
    printf(1, "\nOkay now again but after deleting the directory inode for foo\n");
    i = 0;
    while ((de = dirents[i]).inum != 0) {
        getinode(de.inum, &in);
        
        printf(1, "dirents[%d] = {inum: %d, pinum: %d, name: %s}\n", i/sizeof(struct dirent), de.inum, de.pinum, de.name);
        i += sizeof(struct dirent);
        printf(1, "inode = {dev: %d, inum: %d, type: %s, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
               in.dev, in.inum, in.type, in.nlink, in.ref, in.size, in.valid);
    }
    free(dirents);

    exit();
}