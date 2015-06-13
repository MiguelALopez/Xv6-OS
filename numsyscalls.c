#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
 int nsyscall = -1;
 if (argc == 2) {// se ferifica si hay mas de un argumento que acompaña a la funcion
  nsyscall = atoi(argv[1]);//combertimos el argumento que se le pasa a entero
 }
 if (nsyscall == -1) {
	 /*si no hay parametros de entrada se imprimen el numero de veces 
	  * ejecutado de cada llamado al sistema*/
	 int i;
	 for(i = 1; i <= 23; i++){
		 numsyscalls(i);//se hace uso del llamado al sistema el cual se le pasan todos los ID de los syscalls
	 }
 } else {
	 /*si hay un argumento se hace uso del llamado al sistema para que 
	  * retorne el numero de veces que este se a ejecutado*/
	 numsyscalls(nsyscall);
 }
 exit();
}

