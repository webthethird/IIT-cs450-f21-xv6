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


int main(int argc, char const *argv[])
{
    struct dirent *dirents = (struct dirent*)malloc(200 * sizeof(struct dirent));
    struct inode *inodes = (struct inode*)malloc(200 * sizeof(struct inode));
    struct dirent de;
    struct inode in;
    char* itype;

    mkdir("/test");
    chdir("/test");
    // walkinodetb((uint)1, inods);
    walkdir("/", dirents, inodes);

    for (int i = 0; i < 200; i++) {
        de = dirents[i];
        in = inodes[i];
        switch(in.type) {
            case(1):
            strcpy(itype, "DIR");
            case(2):
            strcpy(itype, "FILE");
            case(3):
            strcpy(itype, "DEV");
            default:
            strcpy(itype, "NONE");
        }
        
        printf(1, "dirents[%d] = {inum: %d, name: %s}\n", i, de.inum, de.name);
        printf(1, "inodes[%d] = {dev: %d, inum: %d, type: %s, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
               i, in.dev, in.inum, itype, in.nlink, in.ref, in.size, in.valid);
    }
    exit();
}