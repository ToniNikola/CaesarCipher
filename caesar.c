#include "caesar.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPTED_PREFIX "encrypted-"

#define DECRYPTED_PREFIX "decrypted-"

char encryptCharacter(char character, int offset);
char decryptCharacter(char character, int offset);

void encrypt(const char *fileName, int offset) {

  printf("\n");

  char ch;
  char buff[255];
  char encriptedFileName[255];

  FILE *pOriginal;
  FILE *pEncripted;

  // Build the encriptedFileName
  strcpy(encriptedFileName, ENCRYPTED_PREFIX);
  strcat(encriptedFileName, fileName);

  printf("Encryption of file: \"%s\" STARTED.\n", fileName);

  pOriginal = fopen(fileName, "r+");
  pEncripted = fopen(encriptedFileName, "w+");

  if (pEncripted == NULL) {
    printf("Error while creating encrypted file.\n");
    exit(EXIT_FAILURE);
  }

  if (pOriginal == NULL) {
    printf("Error while reading original file.\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(buff, 255, pOriginal) != NULL) {
    for (int i = 0; buff[i] != '\0'; ++i) {
      ch = buff[i];

      buff[i] = encryptCharacter(ch, offset);
    }
    fputs(buff, pEncripted);
  }

  fclose(pOriginal);
  fclose(pEncripted);

  printf("Encryption ended successful!\n\n");

  exit(EXIT_SUCCESS);
}

void decrypt(const char *fileName, int offset) {

  char ch;
  char buff[255];
  char encryptedFileName[255];
  char decryptedFileName[255];

  FILE *pDecrypted;
  FILE *pEncrypted;

  // Build the encryptedFileName
  strcpy(encryptedFileName, ENCRYPTED_PREFIX);
  strcat(encryptedFileName, fileName);

  // Build the decryptedFileName
  strcpy(decryptedFileName, DECRYPTED_PREFIX);
  strcat(decryptedFileName, fileName);

  printf("Decryption of file: \"%s\" STARTED.\n", encryptedFileName);

  pEncrypted = fopen(encryptedFileName, "r+");
  pDecrypted = fopen(decryptedFileName, "w+");

  if (pEncrypted == NULL) {
    printf("Error while reading encrypted file.");
    exit(EXIT_FAILURE);
  }

  if (pDecrypted == NULL) {
    printf("Error while creating decrypted file.");
    exit(EXIT_FAILURE);
  }

  while (fgets(buff, 255, pEncrypted) != NULL) {
    for (int i = 0; buff[i] != '\0'; ++i) {

      ch = buff[i];

      buff[i] = decryptCharacter(ch, offset);
    }
    fputs(buff, pDecrypted);
  }

  fclose(pEncrypted);
  fclose(pDecrypted);

  printf("Decryption ended successful!\n\n");

  exit(EXIT_SUCCESS);
}

char encryptCharacter(char character, int offset) { return character + offset; }
char decryptCharacter(char character, int offset) { return character - offset; }