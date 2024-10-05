// By Eymard Alarcon //
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "forky.h"

void fork_pattern_1(int num_things, FILE *file) {
    pid_t pids[num_things];
    for (int i = 0; i < num_things; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            srand(time(NULL) ^ (getpid() << 16));
            int sleep_time = rand() % 8 + 1;
            fprintf(file, "Process %d (PID %d) beginning\n", i + 1, getpid());
            fflush(file);
            sleep(sleep_time);
            fprintf(file, "Process %d (PID %d) exiting\n", i + 1, getpid());
            fflush(file);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < num_things; i++) {
        if (pids[i] > 0) {
            waitpid(pids[i], NULL, 0);
        }
    }
}

void fork_pattern_2(int num_things, FILE *file) {
    for (int i = 0; i < num_things; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            srand(time(NULL) ^ (getpid() << 16));
            int sleep_time = rand() % 8 + 1;
            fprintf(file, "Process %d (PID %d) beginning\n", i + 1, getpid());
            fflush(file);
            sleep(sleep_time);
            if (i + 1 < num_things) {
                pid_t child_pid = fork();
                if (child_pid < 0) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else if (child_pid == 0) {
                    srand(time(NULL) ^ (getpid() << 16));
                    int sleep_time_child = rand() % 8 + 1;
                    fprintf(file, "Process %d creating Process %d\n", i + 1, i + 2);
                    fflush(file);
                    fprintf(file, "Process %d (PID %d) beginning\n", i + 2, getpid());
                    fflush(file);
                    sleep(sleep_time_child);
                    fprintf(file, "Process %d (PID %d) exiting\n", i + 2, getpid());
                    fflush(file);
                    exit(EXIT_SUCCESS);
                }
                waitpid(child_pid, NULL, 0);
            }
            fprintf(file, "Process %d (PID %d) exiting\n", i + 1, getpid());
            fflush(file);
            exit(EXIT_SUCCESS);
        }
        waitpid(pid, NULL, 0);
    }
}
