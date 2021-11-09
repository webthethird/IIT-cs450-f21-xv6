/*
xv6 modified by:
William Bodell - CWID: A20465701
Josh Greenberg - CWID: A20472596
*/
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Returns a virtual address to the shared page when successful 
// and the process can start writing and reading from the virtual address.
// The first process that calls with a unique key will have the shared pages 
// allocated to the next available virtual pages starting at the high end 
// of the process’ address space. Subsequent calls with the same key from 
// other processes will be able to read and write to the shared pages.
void*
sys_getshpg(void)
{
  int key;
  int numPages;

  if (argint(0, &key) < 0 || argint(1, &numPages) < 0)
  {
    return (void*)-1; //error in passed arguments
  }

  //go to vm.c to do actual shared memory management
  return getshpg(key, numPages);

}

// Removes the calling process from accessing the shared pages  
// associated with the key. When no more process can access the 
// pages associated with a key, those pages will be deallocated.
int
sys_freeshpg(void)
{
  int key;
  
  if (argint(0, &key) < 0)
  {
    return -1; //error in passed argument
  }

  //go to vm.c to do actual shared memory management
  return freeshpg(key);

}
