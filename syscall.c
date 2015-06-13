#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "syscall.h"

//Arreglo encargado de almacenar el numero de veces que se ejecuta un llamado al sistema
int numsyscalls[23]; 

// User code makes a system call with INT T_SYSCALL.
// System call number in %eax.
// Arguments on the stack, from the user call to the C
// library system call function. The saved user %esp points
// to a saved program counter, and then the first argument.

// Fetch the int at addr from the current process.
int
fetchint(uint addr, int *ip)
{
  if(addr >= proc->sz || addr+4 > proc->sz)
    return -1;
  *ip = *(int*)(addr);
  return 0;
}

// Fetch the nul-terminated string at addr from the current process.
// Doesn't actually copy the string - just sets *pp to point at it.
// Returns length of string, not including nul.
int
fetchstr(uint addr, char **pp)
{
  char *s, *ep;

  if(addr >= proc->sz)
    return -1;
  *pp = (char*)addr;
  ep = (char*)proc->sz;
  for(s = *pp; s < ep; s++)
    if(*s == 0)
      return s - *pp;
  return -1;
}

// Fetch the nth 32-bit system call argument.
int
argint(int n, int *ip)
{
  return fetchint(proc->tf->esp + 4 + 4*n, ip);
}

// Fetch the nth word-sized system call argument as a pointer
// to a block of memory of size n bytes.  Check that the pointer
// lies within the process address space.
int
argptr(int n, char **pp, int size)
{
  int i;
  
  if(argint(n, &i) < 0)
    return -1;
  if((uint)i >= proc->sz || (uint)i+size > proc->sz)
    return -1;
  *pp = (char*)i;
  return 0;
}

// Fetch the nth word-sized system call argument as a string pointer.
// Check that the pointer is valid and the string is nul-terminated.
// (There is no shared writable memory, so the string can't change
// between this check and being used by the kernel.)
int
argstr(int n, char **pp)
{
  int addr;
  if(argint(n, &addr) < 0)
    return -1;
  return fetchstr(addr, pp);
}

extern int sys_chdir(void);
extern int sys_close(void);
extern int sys_dup(void);
extern int sys_exec(void);
extern int sys_exit(void);
extern int sys_fork(void);
extern int sys_fstat(void);
extern int sys_getpid(void);
extern int sys_kill(void);
extern int sys_link(void);
extern int sys_mkdir(void);
extern int sys_mknod(void);
extern int sys_open(void);
extern int sys_pipe(void);
extern int sys_read(void);
extern int sys_sbrk(void);
extern int sys_sleep(void);
extern int sys_unlink(void);
extern int sys_wait(void);
extern int sys_write(void);
extern int sys_uptime(void);
extern int sys_date(void);
extern int sys_numsyscalls(void);

static int (*syscalls[])(void) = {
[SYS_fork]        sys_fork,
[SYS_exit]        sys_exit,
[SYS_wait]        sys_wait,
[SYS_pipe]        sys_pipe,
[SYS_read]        sys_read,
[SYS_kill]        sys_kill,
[SYS_exec]        sys_exec,
[SYS_fstat]       sys_fstat,
[SYS_chdir]       sys_chdir,
[SYS_dup]         sys_dup,
[SYS_getpid]      sys_getpid,
[SYS_sbrk]        sys_sbrk,
[SYS_sleep]       sys_sleep,
[SYS_uptime]      sys_uptime,
[SYS_open]        sys_open,
[SYS_write]       sys_write,
[SYS_mknod]       sys_mknod,
[SYS_unlink]      sys_unlink,
[SYS_link]        sys_link,
[SYS_mkdir]       sys_mkdir,
[SYS_close]       sys_close,
[SYS_date]        sys_date,
[SYS_numsyscalls] sys_numsyscalls,
};
//Metodo encargado de retornar el nombre de una llamada al sistema segun su ID
char*
nameSyscalls(int num){
	char *name;
	switch(num){
		case 1: name = "fork"; break;
		case 2: name = "exit"; break;
		case 3: name = "wait"; break;
		case 4: name = "pipe"; break;
		case 5: name = "read"; break;
		case 6: name = "kill"; break;
		case 7: name = "exec"; break;
		case 8: name = "fstat"; break;
		case 9: name = "chdir"; break;
		case 10: name = "dup"; break;
		case 11: name = "getpid"; break;
		case 12: name = "sbrk"; break;
		case 13: name = "sleep"; break;
		case 14: name = "uptime"; break;
		case 15: name = "open"; break;
		case 16: name = "write"; break;
		case 17: name = "mknod"; break;
		case 18: name = "unlink"; break;
		case 19: name = "link"; break;
		case 20: name = "mkdir"; break;
		case 21: name = "close"; break;
		case 22: name = "date"; break;
		case 23: name = "numsyscalls"; break;
		
	}
	return name;
}
//Metodo encargado de imprimir el numero de veces ejecutado un llamado al sistema especifico
void
showNumSyscalls(int num){
	cprintf("numero de llamados de la funcion %s: %d\n",nameSyscalls(num),numsyscalls[num-1]);
}
//Metodo encargado de imprimir el llamado al sistema con sus respectivos argumentos
void
showSyscalls(int num){
  switch(num){
    case 1:{
		cprintf(" llamada %s(void)\n",nameSyscalls(num));}break;
    case 2:{
		cprintf(" llamada %s(void)\n",nameSyscalls(num));}break;
    case 3:{
		cprintf(" llamada %s(void)\n",nameSyscalls(num));}break;
    case 4:{
		int *a;	 argptr(0,(void*)(&a),sizeof(*a));
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),*a);}break;
    case 5:{
		int a;   argint(0,&a);
		char *b; argstr(1,&b);
		int c;   argint(2,&c);
		cprintf(" llamada %s(%d, %s, %d)\n",nameSyscalls(num),a,b,c);}break;
    case 6:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),a);}break;
    case 7:{
		char *a; argstr(0,&a);//jojo
		cprintf(" llamada %s(%s, char**)\n",nameSyscalls(num),a);}break;
    case 8:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d, struct stat*)\n",nameSyscalls(num),a);}break;
    case 9:{
		char *a; argstr(0,&a);
		cprintf(" llamada %s(%s)\n",nameSyscalls(num),a);}break;
    case 10:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),a);}break;
    case 11:{
		cprintf(" llamada %s(void)\n",nameSyscalls(num));}break;
    case 12:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),a);}break;
    case 13:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),a);}break;
    case 14:{
		cprintf(" llamada %s(void)\n",nameSyscalls(num));}break;
    case 15:{
		char *a; argstr(0,&a);
		int b;   argint(1,&b);
		cprintf(" llamada %s(%s, %d)\n",nameSyscalls(num),a,b);}break;
    case 16:{
		int a;   argint(0,&a);
		char *b; argstr(1,&b);
		int c;   argint(2,&c);
		cprintf(" llamada %s(%d, %s, %d)\n",nameSyscalls(num),a,b,c);}break;
    case 17:{
		char *a; argstr(0,&a);
		int b;   argint(1,&b);
		int c;   argint(2,&c);
		cprintf(" llamada %s(%s, %d, %d)\n",nameSyscalls(num),a,b,c);}break;
    case 18:{
		char *a; argstr(0,&a);
		cprintf(" llamada %s(%s)\n",nameSyscalls(num),a);}break;
    case 19:{
		char *a; argstr(0,&a);
		char *b; argstr(1,&b);
		cprintf(" llamada %s(%s, %s)\n",nameSyscalls(num),a,b);}break;
    case 20:{
		char *a; argstr(0,&a);
		cprintf(" llamada %s(%s)\n",nameSyscalls(num),a);}break;
    case 21:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),a);}break;
    case 22:{
		cprintf(" llamada %s(struct rtcdate *r)\n",nameSyscalls(num));}break;
    case 23:{
		int a;   argint(0,&a);
		cprintf(" llamada %s(%d)\n",nameSyscalls(num),a);}break;
    default: cprintf("%d %s: unknown sys call %d\n",proc->pid, proc->name, num);break;
  }  
}

void
syscall(void)
{
  int num;

  num = proc->tf->eax;
  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    numsyscalls[num-1]++; //Se suma en un arreglo el numero de llamadas al sistema
    showSyscalls(num); //Se imprime la llamada al sistema
    proc->tf->eax = syscalls[num]();
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            proc->pid, proc->name, num);
    proc->tf->eax = -1;
  }
}

