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
    if (argc != 2) {
        // No parameters provided
        printf(1, "Too much or too few arguments provided.\n");
        exit();
    }
	int pid = atoi(argv[1]);
    if (pid == 0 && argv[1][0] != '0') {
        printf(1, "Error: Invalid argument. Please provide an integer.\n");
        exit();
    }

	
    tickets_owned(pid);
    exit(); //return 0;
}
