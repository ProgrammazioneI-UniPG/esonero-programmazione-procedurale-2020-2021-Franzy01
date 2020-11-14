#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Array dimension (is equal to the maximum string size + 1, because of the terminator character '\0')
#define arrayDim 129

//Arrays for the message and the key
char plainText[arrayDim], key[arrayDim];

//Functions prototypes
int randNumber(int, int);
void crypt(void);

//Random number generator
int randNumber(int min, int max){
  return rand() % (max - min + 1) + min;
}

//Crypting and print function
void crypt(void){
  for(int i = 0; i < strlen(plainText); i++)
    plainText[i] = plainText[i] ^ key[i];
  printf("%s\n", plainText);
}

//MAIN function
int main(void){
  time_t tm;
  srand((unsigned) time(&tm));
  char c;
  int choice;
  //Message input
  printf("Enter a message with up to %d characters. Excess characters will be ignored.\nMESSAGE: ", arrayDim - 1);
  fgets(plainText, arrayDim, stdin);
  //Remove unwanted characters
  if(plainText[strlen(plainText) - 1] == '\n')
    plainText[strlen(plainText) - 1] = '\0';
  else
    while((c = getchar()) != '\n' && c != EOF);
  //Key input
  printf("Choose an option:\n1. Enter a key manually.\n2. Create a random encryption key.\n");
  do{
    printf("CHOICE: ");
    scanf("%d", &choice);
    getchar();
    switch(choice){
      case 1:
        if(strlen(plainText) == arrayDim - 1)
          printf("Enter a key with a length of %d characters. Excess characters will be ignored.\n", arrayDim - 1);
        else
          printf("Enter a key with a length between %lu and %d characters. Excess characters will be ignored.\n", strlen(plainText), arrayDim - 1);
        do{
          printf("KEY: ");
          fgets(key, arrayDim, stdin);
          //Remove unwanted characters
          if(key[strlen(key) - 1] == '\n')
            key[strlen(key) - 1] = '\0';
          else
            while((c = getchar()) != '\n' && c != EOF);
          if(strlen(key) < strlen(plainText))
            printf("[ERROR]: The key length must be equal or greater than %lu.\n", strlen(plainText));
        }while(strlen(key) < strlen(plainText));
        break;
      case 2:
        for(int i = 0; i < strlen(plainText); i++)
          key[i] = (char) randNumber(32, 127);
        printf("Generated key: %s\n", key);
        break;
      default:
        printf("[ERROR]: Enter 1 or 2.\n");
    }
  }while(choice != 1 && choice != 2);
  //Crypting and outputs
  printf("Crypted message: ");
  crypt();
  printf("Original message: ");
  crypt();
}
