#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "caesar.h"
#include "child_process_macro.h"

#define DECRYPTED_PREFIX "decrypted-"

void compareFiles(const char *firstFile, const char *secondFile);

int main(int argc, char *argv[]) {

  pid_t pid;
  int status;
  char buffer[80];
  int cipherOffset;
  char decriptedFileName[255];

  if (argc != 3) {
    printf("error - wrong number of arguments");
    exit(EXIT_FAILURE);
  }

  if (sscanf(argv[2], "%i", &cipherOffset) != 1) {
    printf("error - argument not an integer");
  }

  // Build the decrypted file name.
  strcpy(decriptedFileName, DECRYPTED_PREFIX);
  strcat(decriptedFileName, argv[1]);

  SAFE_CHILD_SPAWN(encrypt(argv[1], (int)cipherOffset),
                   SAFE_WAIT(SAFE_CHILD_SPAWN(
                       decrypt(argv[1], (int)cipherOffset),
                       SAFE_WAIT(compareFiles(argv[1], decriptedFileName)))));

  return 0;
}

void compareFiles(const char *firstFile, const char *secondFile) {

  printf("Comparing files:\n");
  printf("%s with %s\n\n", firstFile, secondFile);

  FILE *fp1 = fopen(firstFile, "r");
  FILE *fp2 = fopen(secondFile, "r");

  if (fp1 == NULL || fp2 == NULL) {
    printf("error - while opening compare files\n\n");
    exit(0);
  }

  char ch1 = getc(fp1);
  char ch2 = getc(fp2);

  while (ch1 != EOF && ch2 != EOF) {

    if (ch1 != ch2) {
      printf("Compared files are NOT equal!\n\n");
      exit(EXIT_FAILURE);
    }

    ch1 = getc(fp1);
    ch2 = getc(fp2);
  }

  // closing both files
  fclose(fp1);
  fclose(fp2);

  printf("Compared files are equal!\n\n");
}
