/*
test program by:
William Bodell - CWID: A20465701
Josh Greenberg - CWID: A20472596
*/
#include "types.h"
#include "user.h"
#include "fs.h"


int main(int argc, char const *argv[])
{
    int inodes[200];
    mkdir("test");
    chdir("test");
    intbwalk(1, inodes);
    int i;
    while (inodes[i] != 0) {
        printf("Inode %d is allocated.\n", inodes[i]);
        i++;
    }
    exit();
}