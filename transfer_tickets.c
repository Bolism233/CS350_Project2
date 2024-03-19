#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char * argv[])
{
    if (argc < 3) {
        // No parameters provided
        printf(1, "No parameter provided.\n");
        exit();
    }
	int pid = argv[1];
    int tickets = argv[2];
    if (pid == 0 && argv[1][0] != '0') {
        printf(1, "Error: Invalid argument. Please provide an integer.\n");
        exit();
    }
    if (tickets == 0 && argv[2][0] != '0') {
        printf(1, "Error: Invalid argument. Please provide an integer.\n");
        exit();
    }

    // Check if the conversion failed (i.e., argv[1] is not a valid integer)

    transfer_tickets(pid, tickets);
    exit(); //return 0;
}
