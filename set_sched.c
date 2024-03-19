#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char * argv[])
{
    if (argc != 2) {
        // No parameters provided
        printf(1, "Too much or too few arguments provided.\n");
        exit();
    }

	int i = atoi(argv[1]);
    // Check if the conversion failed (i.e., argv[1] is not a valid integer)
    if (i == 0 && argv[1][0] != '0') {
        printf(1, "Error: Invalid argument. Please provide an integer.\n");
        exit();
    }
    if (i != 0 && i != 1){
        printf(1, "Not 0 or 1\n");
        exit();
    } 
    set_sched(i);
    exit(); //return 0;
}
