#include "types.h"
#include "stat.h"
#include "user.h"

/* ATTENTION: to ensure correct compilation of the base code, 
   stub functions for the system call user space wrapper functions are provided. 
   REMEMBER to disable the stub functions (by commenting the following macro) to 
   allow your implementation to work properly. */


/* IMPORTANT INSTRUCTION: the code below should not be changed. 
    Failure to follow this instruction will lead to zero point 
	for this part */

int 
main(int argc, char * argv[])
{
    if (argc < 2) {
        // No parameters provided
        printf(1, "No parameter provided.\n");
        exit();
    }

	int i = atoi(argv[1]);
	
    if(i != 0 && i != 1)
        printf(1, "Available options: 0 is default scheduler, 1 is strided scheduler");
    
    set_sched(i);

    /* if(i == 0){
        printf(1, "adopting RR %d", ut);
    } else if(i == 1){
        printf(1, "adopting stride %d", ut);
    }
    */
    exit(); //return 0;
}
