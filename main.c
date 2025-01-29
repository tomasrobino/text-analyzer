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
    position = ftell(file);
    long charAmount = 0;
    long wordCounter = 0;
    long wordTotal = 0;
    for (int i = 0; i < byteAmount; i++) {
        const int currentChar = fgetc(file);
        //ASCII 32 is space, 127 is DEL, 160 is NBSP
        if (currentChar > 32 && currentChar != 127 && currentChar != 160) {
            wordCounter++;
            charAmount++;
        } else {
            if (wordCounter != 0) {
                wordCounter = 0;
                wordTotal++;
            }
        }
        ftell(file);
    }
    printf("charAmount (without spaces, new lines, etc.): %ld\n", charAmount);
    printf("wordTotal: %ld\n", wordTotal);
    fclose(file);
}