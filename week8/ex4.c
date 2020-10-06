#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TEN_MB (10*1024*1024)

int main() {
    int* ptr;
    for (int i = 0; i < 10; i++) {
        ptr = malloc(TEN_MB);
        memset(ptr, 0, TEN_MB);
        struct rusage *info = malloc(sizeof(struct rusage));
        getrusage(RUSAGE_SELF, info);
        printf("%ld\n", (info->ru_maxrss));
        sleep(1);
    }
    return 0;
}

/* Output:
11284
21796
32092
42388
52684
62980
73012
83308
93604
103900
*/

/* Comments:
Here's how ru_maxrss is described in man:
              "This is the maximum resident set size used (in kilobytes).  For
              RUSAGE_CHILDREN, this is the resident set size of  the  largest
              child, not the maximum resident set size of the process tree."
Which is the closest I have to memory usage, since ru_ixrss, ru_idrss, ru_isrss
are unused on Linux (again, according to man) and, apparentely just give 0 because
they're unmaintained.

It increases by about 10 MB each time, so it represents how memory used by this
program grows in time
*/