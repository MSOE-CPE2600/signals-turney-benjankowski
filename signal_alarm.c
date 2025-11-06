/**
 * File: signal_alarm.c
 * Modified by: Benjamin Jankowski
 * 
 * Brief summary of program:
 * Creates and then captures a SIGALRM signal
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_alarm() {
    printf("Alarm was raised\n");
}

int main(void) {
    signal(SIGALRM, handle_alarm);

    // https://linux.die.net/man/3/alarm
    alarm(5); // Schedule an SIGALRM for 5 seconds from now

    for (int i = 0; i < 10; i++) {
        // The sleep will get canceled by the alarm
        // The loop is used to break up the sleeps instead
        sleep(1);
    }

    return 0;
}