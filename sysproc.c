#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include <stdbool.h>


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

int sys_shutdown(void)
{
  /* Either of the following will work. Does not harm to put them together. */
  outw(0xB004, 0x0|0x2000); // working for old qemu
  outw(0x604, 0x0|0x2000); // working for newer qemu
  
  return 0;
}

extern int sched_trace_enabled;
extern int sched_trace_counter;
int sys_enable_sched_trace(void)
{
  if (argint(0, &sched_trace_enabled) < 0)
  {
    cprintf("enable_sched_trace() failed!\n");
  }
  
  sched_trace_counter = 0;

  return 0;
}

extern int current_scheduler;
int sys_set_sched(void) {
  int policy;
  if(argint(0, &policy) < 0) {
    cprintf("Error: Failed to retrieve policy value.\n");
    return -1; // Indicate error
  }

  if(policy == 0){
    //default
    cprintf("adopting RR scheduling\n");
    current_scheduler = 0;
    return policy;
  }
  if(policy == 1){
    //stride
    cprintf("adopting stride scheduling\n");
    current_scheduler = 1;
    cprintf("current scheduler: %d\n", current_scheduler);
    return policy;
  }
  return 0;
}

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int sys_tickets_owned(void) {
  int pid;
  bool found = false;
  if(argint(0, &pid) < 0) {
    cprintf("Error: Failed to retrieve policy value.\n");
    return -1; // Indicate error
  }
  struct proc *p;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    // Check if the PID matches
    if (p->pid == pid) {
        // Return the number of tickets owned by the process
        cprintf("%d\n", p->ticket);
        return 0;
    }
    continue;
  }
  if (found == false){
    cprintf("Target pid not found\n");
  }
}

int sys_transfer_tickets(void){
  int pid;
  int tickets;
  if(argint(0, &pid) < 0) {
    cprintf("Error: Failed to retrieve policy value.\n");
    return -1; // Indicate error
  }
  struct proc *p3;
  struct proc *p2;
  int current_pid = sys_getpid();
  bool found = false;
  if(tickets < 0){
    cprintf("target < 0\n");
    return -1;
  }
  for(p3 = ptable.proc; p3< &ptable.proc[NPROC]; p3++){
    // Check if current PID matches
    if(p3->pid == current_pid) {
      if((p3->ticket - 1) < tickets){
        cprintf("tickets too large\n");
        return -2;
      }
      for(p2 = ptable.proc; p2 < &ptable.proc[NPROC]; p2++){
        // Check if target PID matches
        if(p2->pid == pid) {
          found = true;
          p3->ticket -= tickets;
          p2->ticket += tickets;
        }
        continue;
      }
      if (found == false){
        cprintf("Target pid not found\n");
      }
    }
  }
}