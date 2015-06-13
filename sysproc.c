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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
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
//definicion de la llamada al sistema date
int
sys_date(void)
{
  struct rtcdate *r; //se crea un puntero a una estructura de tipo rtcdate
  argptr(0, (void*)(&r), sizeof(*r)); //se inicializa la estructura con la direccion de memoria de el parametro ingresado al llamado al sistema
  cmostime(r); //se hace uso de la funcion cmostime para obtener la hora de el sistema
  return 0;
}
//definicion de la llamada al sistema numsyscalls
int
sys_numsyscalls(void)
{
	int num;
	argint(0,&num); //obtengo el argumento de entrada de la llamada al sistema en forma de entero 
	showNumSyscalls(num);//hago uso de la funcion showNumSyscalls para imprimir el numero de veces que se a ejecutado un llamado al sistema
	return 0;
}
