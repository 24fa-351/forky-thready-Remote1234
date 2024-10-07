// By Eymard Alarcon //
#include "forky.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void fork_pattern_1(int number_of_things) {
    pid_t pid;
    for (int i = 1; i <= number_of_things; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            printf("Process %d (PID %d) beginning\n", i, getpid());
            sleep(rand() % 8 + 1);
            printf("Process %d (PID %d) exiting\n", i, getpid());
            exit(0);
        } else {
            printf("Main creating Process %d (PID %d)\n", i, pid);
        }
    }

    for (int i = 0; i < number_of_things; i++) {
        wait(NULL);
    }
}

void fork_pattern_2(int number_of_things) {
    pid_t pid;
    for (int i = 1; i <= number_of_things; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            printf("Process %d (PID %d) beginning\n", i, getpid());
            sleep(rand() % 8 + 1);
            printf("Process %d (PID %d) exiting\n", i, getpid());
            exit(0);
        } else {
            printf("Main creating Process %d (PID %d)\n", i, pid);
            waitpid(pid, NULL, 0);
        }
    }
}
