#include <sys/types.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "mpic/master.h"

#include <stdio.h>

int RunWorker() {
    FILE* f = fopen("/tmp/mpic.log", "a+");
    if (f == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        fprintf(f, "i=%d pid=%d running\n", i, getpid());
        fflush(f);
        sleep(1);
    }

    fclose(f);
    return 0;
}

// usage : master_workers <process count>
int main(int argc, char* argv[]) {
    mpic::Master& pm = mpic::Master::instance();
    pm.Init(argc, argv);
    return pm.Run(&RunWorker);
}
