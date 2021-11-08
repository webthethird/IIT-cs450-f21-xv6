#include "types.h"
#include "user.h"


int main(int argc, char const *argv[])
{
  //test if a process can call getSharedPages and then free them and exit
  // char *page = getshpg(0, 1);
  // freeshpg(0);
  //test if a process can call getSharedPages, write to those pages, that work is readable, and then free them
  
  //test if a process can call getSharedPages, then call getSharedPages with a different key, do different work on each
  //and then free those pages

  //test if a two processes can call getsharedpages, one can write, and the other can read
  int ret;
  char *page;
  if((ret = fork()) == 0) {
    page = getshpg(0, 1);
    strcpy(page, "Hello from child");
    sleep(1000);
  } else {
    page = getshpg(0, 1);
    wait();
    printf(1, "Parent reading: %s\n", page);
  }
  freeshpg(0);
  //test that two processes can call getsharedpages with different keys and get different pages
  
  exit();
}