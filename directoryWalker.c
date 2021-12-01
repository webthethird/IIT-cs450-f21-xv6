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
    // struct inode *inodes = (struct inode*)malloc(200 * sizeof(struct inode));
    struct dirent de;
    struct inode in;
    char* itype;
    int i;

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

    // walkinodetb((uint)1, inods);
    walkdir("/", dirents);

    i = 0;
    while ((de = dirents[i]).inum != 0) {
    // for (int i = 0; i < 200 * sizeof(de); i += sizeof(de)) {
        // de = dirents[i];
        getinode(de.inum, &in);
        // switch(in.type) {
        //     case(1):
        //     strcpy(itype, "DIR");
        //     case(2):
        //     strcpy(itype, "FILE");
        //     case(3):
        //     strcpy(itype, "DEV");
        //     default:
        //     strcpy(itype, "NONE");
        // }
        
        printf(1, "dirents[%d] = {inum: %d, pinum: %d, name: %s}\n", i/sizeof(struct dirent), de.inum, de.pinum, de.name);
        i += sizeof(struct dirent);
        // printf(1, "inodes[%d] = {dev: %d, inum: %d, type: %s, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
        //        i, in.dev, in.inum, itype, in.nlink, in.ref, in.size, in.valid);
    }
    exit();
}