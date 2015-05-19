#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "uptime: %d s\n", (uptime()/100));
		
	exit();
}
