/**
 * File: send_signal.c
 * Modified by: Benjamin Jankowski
 *
 * Brief summary of program:
 * Sends a SIGUSR1 signal along with a random integer
 * to a specified PID using sigqueue.
 *
 * Usage: ./send_signal <PID>
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        exit(1);
    }

    pid_t target_pid = atoi(argv[1]);
    if (target_pid <= 0) {
        printf("Invalid PID.\n");
        exit(1);
    }

    // Make sure to seed the random function
    // or else the values will be the same every time
    srand(time(NULL));
    int random_value = rand();

    union sigval send_value;
    send_value.sival_int = random_value;

    printf("Sending SIGUSR1 with value %d to PID %d\n", random_value, target_pid);

    if (sigqueue(target_pid, SIGUSR1, send_value) == -1) {
        printf("Could not send signal. The recv process may have died\n");
        exit(1);
    }

    printf("Signal sent successfully.\n");
    return 0;
}