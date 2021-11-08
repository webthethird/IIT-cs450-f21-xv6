#include "types.h"
#include "user.h"


int main(int argc, char const *argv[])
{
  //1. test if a process can call getSharedPages and then free them and exit
  // char *page = getshpg(0, 1);
  // freeshpg(0);

  //2. test if a process can call getSharedPages, write to those pages, and read from the pages, 
  //then after calling freeSharedPages, it can no longer read from them
  /*
  char *page = getshpg(0, 1);
  char *str1 = strcpy(page, "Testing testing\n");
  printf(1, "%s", str1);
  char *str2 = strcpy(page, "1, 2, 3\n");
  printf(1, "%s", str2);
  freeshpg(0);
  char *str3 = strcpy(page, "boom\n");
  printf(1, "After freeshpg: %s\n", str1);
  */

  //3. test if a process can call getSharedPages, then call getSharedPages with a different key, 
  //do different work on each, then free the first key, read from the second, then free that too
  char *page1 = getshpg(0, 2);
  char *page2 = getshpg(1, 1);
  strcpy(page2, "Testing testing 1, 2, 3");
  freeshpg(0);
  printf(1, "%s\n", page2);
  freeshpg(1);

  //4. test that a process can call getSharedPages twice, then free the first shared page, and then 
  //call getSharedPages again. tests if shbot decrementing works properly
  /*
  char *page1 = getshpg(0, 1);
  char *page2 = getshpg(1, 1);
  strcpy(page2, "Testing testing 1, 2, 3");
  freeshpg(0);
  char *page3 = getshpg(2, 1);
  printf(1, "%s\n", page2);
  freeshpg(1);
  freeshpg(2);
  */

  //5. test if a two processes can call getsharedpages, one can write, and the other can read
  /*
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
  // also test whether child process can write to page after freeing (should cause page fault)
  // if(ret == 0) {
  //   printf(1, "Child reading after freeing: %s\n", page);
  //   strcpy(page, "(this shouldn't be here)");
  // }
  */

  //6. test that two processes can call getsharedpages with different keys and get different pages
  /*
  int ret, key;
  char *page;
  if((ret = fork()) == 0) {
    key = 0;
    page = getshpg(key, 1);
    strcpy(page, "Hello from child");
    sleep(1000);
  } else {
    key = 1;
    page = getshpg(1, 1);
    wait();
    printf(1, "Parent reading: %s\n", page);
  }
  freeshpg(key);
  */

  //7. 
  exit();
}