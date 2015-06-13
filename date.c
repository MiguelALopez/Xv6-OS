#include "types.h"
#include "user.h"
#include "date.h"

int
main(int argc, char *argv[])
{
  
  struct rtcdate r;
  if (date(&r)) { //se hace un llamado al sistema date el cual se le pasa la posicion de memoria de la estructura
				  //en la cual se almacena los valores de la fecha 
    printf(2, "date failed\n");
    exit();
  }
  /*Se imprime en un formato de dia mes y año seguido de la hora minuto y segundo,
  * la hora esta dada en el estandar de tiempo UTC(Coordinated Universal Time)*/
  printf(2, "%d-%d-%d %d:%d:%d UTC\n", r.day, r.month, r.year, r.hour, r.minute, r.second);
  
  exit();
}
