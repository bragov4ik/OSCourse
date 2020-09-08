#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int n = 0;
    if (argc > 1) {
        char *end;
        n = strtol(argv[1], &end, 10);
    }
    int parent_pid = getpid();
    fork();
    int pid = getpid();
    if (pid == parent_pid) {
        printf("Hello from parent %d\n", pid - n);
    }
    else {
        printf("Hello from child %d\n", pid - n);
    }
    return 0;
}

/* Output without changing n:
Hello from parent 4427
Hello from child 4428
Hello from parent 4429
Hello from child 4430
Hello from parent 4431
Hello from child 4432
Hello from parent 4433
Hello from child 4434
Hello from parent 4435
Hello from child 4436
Hello from parent 4437
Hello from child 4438
Hello from parent 4439
Hello from child 4440
Hello from parent 4441
Hello from child 4442
Hello from parent 4443
Hello from child 4444
Hello from parent 4445
Hello from child 4446
*/
/* Explanation:
Every process has its own unique process number (PID).
So when we do fork, child process gets his own PID. Aparrentely,
every new process gets PID = PID(the previous newest process) + 1
(up to some number of course). Since these processes were created in 
a very short period of time, their PID's go one by one (no other processes 
were created between them).
*/

/* Output with n incremented on each program run
Hello from parent 8139
Hello from child 8140
Hello from parent 8140
Hello from child 8141
Hello from parent 8141
Hello from child 8142
Hello from parent 8142
Hello from child 8143
Hello from child 8144
Hello from parent 8143
Hello from parent 8144
Hello from child 8145
Hello from child 8146
Hello from parent 8145
Hello from child 8147
Hello from parent 8146
Hello from parent 8147
Hello from child 8148
Hello from parent 8148
Hello from child 8149
*/
/* Explanation
It's basically the same as when n = 0, but n is decremented on each step
Also sometimes the order of execution chenges: child executes before its parent
It happens because they run in (pseudo) parallel mode (or not) and one process
happens to be faster than or is scheduled before its parent
*/   