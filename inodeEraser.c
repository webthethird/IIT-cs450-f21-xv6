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
#include "stat.h"


int main(int argc, char const *argv[])
{
    struct dirent *dirents = (struct dirent*)malloc(1000 * sizeof(struct dirent));
    int *inodes = (int *)malloc(200 * sizeof(int));
    struct dirent de;
    struct inode in;
    char* itype;
    int i, d, found;
    
    if(argc < 2) {
        argv[1] = "/";
    }
    
    printf(1, "argc: %d\nargv[1]: %s\n", argc, argv[1]);

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

    walkinodetb(1, inodes);
    walkdir(argv[1], dirents);

    i = 0;
    printf(1, "inode walker results:\n------------------------------------------------------\n");
    while(*(inodes + i) != 0){
        getinode(*(inodes + i), &in);
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
        printf(1, "{dev: %d, inum: %d, type: %s, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
               in.dev, in.inum, itype, in.nlink, in.ref, in.size, in.valid);
        
        d = 0;
        found = 0;
        while((de = *(dirents + d)).inum != 0){
            if((int)de.inum == in.inum) {
                found = 1;
                break;
            }
            d += sizeof(struct dirent);
        }
        if(found){
            printf(1, "found matching dirent in directory walker results:\n{inum: %d, parent's inum: %d, name: %s}\n\n", de.inum, de.pinum, de.name);
        } else {
            printf(1, "Could not find a matching directory entry for inum = %d in the directory walker results\n\n");
        }

        i++;
    }
    free(dirents);
    free(inodes);

    //do the nonsense
    //struct stat *erasable;
    //stat("foo", erasable);
    //printf(1, "trying to erase inode #%d\n", erasable->ino);

    //eraseinode(1, erasable->ino);
    printf(1, "just before the erase");
    eraseinode(1, 25);
    printf(1, "successfully erased inode 24");

    //okay let's try it again
    struct dirent *dirents2 = (struct dirent*)malloc(1000 * sizeof(struct dirent)); //reallocate 
    int *inodes2 = (int *)malloc(200 * sizeof(int));
    printf(1, "walking\n");
    walkinodetb(1, inodes2);
    printf(1, "successfully walked inode table");
    walkdir(argv[1], dirents2);
    printf(1, "successfully walked directory");


    i = 0;
    printf(1, "inode walker results:\n------------------------------------------------------\n");
    while(*(inodes2 + i) != 0){
        getinode(*(inodes2 + i), &in);
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
        printf(1, "{dev: %d, inum: %d, type: %s, nlink: %d, ref: %d, size: %d, valid: %d}\n", 
               in.dev, in.inum, itype, in.nlink, in.ref, in.size, in.valid);
        
        d = 0;
        found = 0;
        while((de = *(dirents2 + d)).inum != 0){
            if((int)de.inum == in.inum) {
                found = 1;
                break;
            }
            d += sizeof(struct dirent);
        }
        if(found){
            printf(1, "found matching dirent in directory walker results:\n{inum: %d, parent's inum: %d, name: %s}\n\n", de.inum, de.pinum, de.name);
        } else {
            printf(1, "Could not find a matching directory entry for inum = %d in the directory walker results\n\n", de.inum);
        }

        i++;
    }
    free(dirents2);
    free(inodes2);

    exit();
}