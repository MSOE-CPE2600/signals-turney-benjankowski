/**
 * File: recv_signal.c
 * Modified by: Benjamin Jankowski
 *
 * Brief summary of program:
 * Waits for a SIGUSR1 signal using sigaction and prints the
 * integer value sent with it.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigusr1(int sig, siginfo_t *info, void *ucontext) {
    if (info == NULL) return;

    int received_value = info->si_value.sival_int;
    printf("Received signal SIGUSR1 with value: %d\n", received_value);
}

int main(void) {
    struct sigaction sa;

    printf("Receiver PID is: %d\n", getpid());

    sa.sa_sigaction = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; // This allows data to be sent with the signal

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        printf("Failed to create signal receiving\n");
        exit(1);
    }

    printf("Waiting for SIGUSR1...\n");
    while (1) {
        sleep(1);
    }
}