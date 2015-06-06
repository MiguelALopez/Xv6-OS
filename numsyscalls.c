#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
 int nsyscall = -1;
 if (argc == 2) {
  nsyscall = atoi(argv[1]);
 }
 if (nsyscall == -1) {
	 //~ printf(2,"ola\n");
	 int i;
	 for(i = 1; i <= 23; i++){
		 numsyscalls(i);
	 }
  // mostrar todas las llamadas al sistema
  // con su correspondiente numero de invocaciones
 } else {
	 //~ printf(2, "k ace\n");
  // mostrar la llamada al sistema dada en nsyscall
  // con su correspondiente numero de invocaciones
 }
 exit();
}

