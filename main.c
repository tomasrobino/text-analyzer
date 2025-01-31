#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void readFile(char name[]);

int main(void) {
    readFile("test.txt");
    return 0;
}

void readFile(char name[]) {
    FILE* file = fopen(name, "r");
    fseek(file, 0, SEEK_END);
    long position = ftell(file);
    long byteAmount = position;
    printf("byteAmount: %ld\n", byteAmount);
    rewind(file);
    long charAmount = 0;
    long wordLength = 0;
    long wordTotal = 0;
    for (int i = 0; i < byteAmount; i++) {
        const int currentChar = fgetc(file);
        //ASCII 32 is space, 127 is DEL, 160 is NBSP
        if (currentChar > 32 && currentChar != 127 && currentChar != 160) {
            wordLength++;
            charAmount++;
        } else {
            if (wordLength != 0) {
                wordLength = 0;
                wordTotal++;
            }
        }
        ftell(file);
    }
    rewind(file);

    //Creating wordArray, allocating all words
    char** wordArray = malloc(sizeof(char*)*wordTotal);
    long wordCounter = 0;
    wordLength = 0;

    for (int i = 0; i < byteAmount; i++) {
        const int currentChar = fgetc(file);
        //ASCII 32 is space, 127 is DEL, 160 is NBSP
        if (isalpha(currentChar)) {
            wordLength++;
        } else {
            if (wordLength != 0) {
                wordArray[wordCounter] = malloc(wordLength+1);
                position = ftell(file);
                //-1 is EOF, correct position
                if (currentChar == -1) {
                    position++;
                }
                rewind(file);
                fseek(file, position-wordLength-1, SEEK_CUR);
                fread(wordArray[wordCounter], 1, wordLength+1, file);
                wordArray[wordCounter][wordLength] = '\0';
                wordLength = 0;
                wordCounter++;
            }
        }
    }
    puts("");

    printf("charAmount (without spaces, new lines, etc.): %ld\n", charAmount);
    printf("wordTotal: %ld\n", wordTotal);
    printf("words:\n");

    for (int i = 0; i<wordTotal;i++) {
        printf("%s ", wordArray[i]);
    }
    free(wordArray);
    fclose(file);
}