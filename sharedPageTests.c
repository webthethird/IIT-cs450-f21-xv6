#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
  //test if a process can call getSharedPages and then free them and exit
  char *page = getSharedPages(0, 1);
  freeSharedPages(0);
  //test if a process can call getSharedPages, write to those pages, that work is readable, and then free them

  //test if a process can call getSharedPages, then call getSharedPages with a different key, do different work on each
  //and then free those pages

  //test if a two processes can call getsharedpages, one can write, and the other can read

  //test that two processes can call getsharedpages with different keys and get different pages
  
  return 0;
}