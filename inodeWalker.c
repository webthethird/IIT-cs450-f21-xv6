/*
test program by:
William Bodell - CWID: A20465701
Josh Greenberg - CWID: A20472596
*/
#include "types.h"
#include "user.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"


int main(int argc, char const *argv[])
{
    int *inodes = (int *)malloc(200 * sizeof(int));
    mkdir("./foo");
    chdir("foo");
    open("./bar.txt", O_CREATE);
    
    walkinodetb(1, inodes);

    int i = 0;
    while (inodes[i] != 0) {
        printf(1, "Inode %d is allocated.\n", inodes[i]);
        i++;
    }

    /*
    eraseinode(1, i); 
    */

    exit();
}