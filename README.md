## Repo for Lab Week 10
Complete assignment as assigned.

Note, no make file is provided. It is suggested you create one to be more efficient building your programs.

### Part 1
**What is a signal disposition?**

When an operating system is given a signal for a process, that process could have multiple
states it's in currently. It could have nothing registered and a default action will be taken,
it could say to ignore the signal, or it could have a function registered to handle it.

**What is a signal handler? What is it used for?**

A signal handler is simply just a function pointer that a program registered with the operating
system to be executed when a signal is sent to it. When the signal is received, the operating system
will stop the process and save its current position where the signal was received, then call the
function registered.

**Name and describe each of the five default dispositions?**

1. Term: Terminate the process
2. Ign: ignore this signal
3. Core: terminate and core dump the process
4. Stop: suspend the process but don't terminate it
5. Cont: resume a process if it's not suspended

**Name and describe one way to programmatically send a signal**

The easiest way is using the `kill` function in C.
```C
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    // Send SIGUSR1 to the PID 1234
    kill(1234, SIGUSR1);
    
    return 0;
}
```

**Name and describe one way to send a signal to a process from the command line**

There is a very similar command called `kill` that does exactly what the function in C does.
`kill -s SIGUSR1 1234`

You can also use `Ctrl + C` to tell the terminal to send a SIGINT to the running process to terminate.

**Different signals and what they do**

`SIGINT`

Tells the process to terminate cleanly

Default: terminate the process

Yes it can be overwritten. Often you may want to clean up memory or open resources before closing.

`SIGTERM`

Request a process to terminate

Default: terminate the process

Yes it can be overwritten. Same as sig int, likely want to clean up code before quitting.

`SIGUSR1`

No meaning, just an open slot for a process to do whatever it wants with.

Default: terminate the process

Yes it can be overwritten. This is used for anything you want really so it is meant to be handled.

`SIGKILL`

Force quit a process

Default: terminate the process

No, it can not be overwritten. This is a signal that is meant to ensure a process terminates even 
if it's not working correctly.

`SIGSTOP`

Will pause a processes execution leaving it at the last position executed.
It remains in memory, but the operating system will stop giving it CPU time on a core.

Default: stop/suspend the process

No, it can not be overwritten. This is a signal that is meant to control processes by the OS
or an administrator and as such a process can't prevent it from happening.

### Part 2
> How to send signals to a process

Signals can be sent by other processes. However, as the terminal we use to interface with 
programs is also a process at `/bin/bash`. It can send signals to the processes it spawns.
This is usually done with key combinations such as `Ctrl + C` to tell the terminal to send 
a signal to the process currently running and sending output to the terminal. 

In a process with C you can use the `kill` method to send a process using its PID a signal 
of your choice.

There is also a dedicated binary called `kill` that allows you to send a process a signal 
from your terminal. Running `kill pid` replacing PID with the process ID will have kill default 
to SIGTERM. You can also use the `-s` flag with kill to specify the name of a signal you wish to send.

For the `signal_handler.c` code. When the program starts it registers that it has a function to 
handle when a certain signal is received. When the operating system detects that the process has
a signal waiting for the program, it can see the function pointer that is registered by the program 
for that signal. Then it can pause that programs execution and instead move it to the function pointer 
defined to handle the signal. When it's done handling its signal, the program simply resumes where 
it left off as if it simply called a function internally.

Also given what the program does at the start as in just looping forever, it now has the 
unintended effect that you can no longer exit the process with `Ctrl + C` as it simply 
handles it and then continues. The process can still be terminated though forcefully with 
a SIGKILL via the `kill` command or by terminating the terminal that executed it.

### Part 3
A `SIGALRM` is an interrupt usually used to schedule an event to happen at a given time.
C has a convenient helper function called `alarm` that can be used to schedule these events
to execute after a given number of seconds. This allows you to for example every 20 seconds
re-check some files for changes, or update some values in memory.

Although segmentation faults seem like something your program has no control over. It is actually
a signal sent to your program. As with any other signal the program "returns" from its current
position as if it called a function, then goes into the registered function given to the operating
system. The function completes and the program resumes. However, given that the line executed
cause a segmentation fault we now find our selves in an infinite loop where the segmentation fault
gives a signal that then calls the `handle_segfault` function. Which then returns, moves back to the
line it left off at, causes another sementation fault, etc, etc.

### Part 4
`signal` is a simple helper function to register functions to handle signals with the operating system.
But it is not consistent between operating systems so is advised to not be used. Instead, a more robust
function should be used called `sigaction`. This supports more options for customising how you wish
to handle calling and handling signals your program receives. To use it a structure is used to give
the function arguments called `sigaction`, here you can place the function that handles the signal
and details like masks and flags. Then `sigaction` can be called similar to `signal` but with the
`sigaction` struct passed in alongside the signal you wish to register.

Then `kill -s SIGUSR1 pid` can be used to send a signal.

### Part 5
Sending data in a signal with `sigqueue` is similar to using `sigaction` for sending signals
however its mor simple. Instead of a struct passed in, it simply takes a signal id and a
`sigval` to send with the signal. Then for the receiving side it's using `sigaction` as before.
It should also be noted that for this example an int was used, however `sigval` is a union that also
allows for a pointer to be sent which could be much more powerful and allow for much more data to be sent.
