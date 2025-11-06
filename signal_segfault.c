/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Benjamin Jankowski
 * 
 * Brief summary of modifications:
 * Added `handle_segfault` method with signal registration to capture segmentation fault events
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handle_segfault() {
    printf("We had a segmentation fault!\n");
    exit(1);
}

int main (int argc, char* argv[]) {
    signal(SIGSEGV, handle_segfault);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}