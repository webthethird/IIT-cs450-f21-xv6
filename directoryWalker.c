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
    struct dirent *dest[1000];
    uint dev = 1;
    walkdir(dev, "/", dest);
    exit();
}