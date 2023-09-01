#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "signals.h"

// 初始化信号
int initSignals(void) {
    printf("%d> 忽略大部分信号\n", getpid());

    int signum;
    for (signum = 1; signum <= 64; ++signum)
        if (signum != SIGINT && signum != SIGTERM)
            signal(signum, SIG_IGN);

    return 0;
}
