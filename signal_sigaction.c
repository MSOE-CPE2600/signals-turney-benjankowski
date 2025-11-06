/**
 * File: signal_sigaction.c
 * Modified by: Benjamin Jankowski
 * 
 * Brief summary of program:
 * Waits for a SIGUSR1 then terminates
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_siguser(int sig, siginfo_t *info, void *ucontext) {
    if (info == NULL) return;

    printf("Signal SIGUSR1 received\n");
    printf("Calling PID: %d\n", info->si_pid);
}

int main(void) {
    // https://www.man7.org/linux/man-pages/man2/sigaction.2.html
    struct sigaction sa;
    sa.sa_sigaction = handle_siguser;
    sigemptyset(&sa.sa_mask); // Ensure no modification to signals
    sa.sa_flags = SA_SIGINFO; // Make sure info is allowed

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Could not register signal handler");
        exit(1);
    }

    while (1) {
        printf("Waiting...\n");
        sleep(1);
    }
}