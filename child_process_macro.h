#ifndef CHILD_PROCESS_MACRO_H
#define CHILD_PROCESS_MACRO_H

#define SAFE_CHILD_SPAWN(CHILD_PROCESS_JOB, PARENT_PROCESS_JOB)                \
  do {                                                                         \
    pid = fork();                                                              \
    if (pid == -1) {                                                           \
      printf("error - error while opening new process\n");                     \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
    if (pid == 0) {                                                            \
      CHILD_PROCESS_JOB;                                                       \
    } else {                                                                   \
      PARENT_PROCESS_JOB;                                                      \
    }                                                                          \
  } while (0)

#define SAFE_WAIT(NEXT_JOB)                                                    \
  do {                                                                         \
    waitpid(pid, &status, 0);                                                  \
    if (pid == -1) {                                                           \
      printf("error - process wait error\n");                                  \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
    if (!WEXITSTATUS(status)) {                                                \
      NEXT_JOB;                                                                \
    } else if (WIFSIGNALED(status)) {                                          \
      printf("Process was terminated because of signal %d\n",                  \
             WTERMSIG(status));                                                \
    } else if (WIFSTOPPED(status)) {                                           \
      printf("Process stopped (signal %d)\n", WSTOPSIG(status));               \
    } else {                                                                   \
      printf("Process did not end normally.\n");                               \
    }                                                                          \
  } while (0)

#endif