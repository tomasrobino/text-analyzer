#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    int amount;
    char* word;
    struct node_t *next;
} node;

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
    node* head = malloc(sizeof(node));
    head->word = NULL;
    head->next = NULL;
    head->amount = 0;
    node* currentNode = head;
    long charAmount = 0;
    long wordLength = 0;
    long wordTotal = 0;
    for (int i = 0; i < byteAmount; i++) {
        const int currentChar = fgetc(file);
        //ASCII 32 is space, 127 is DEL, 160 is NBSP
        if (isalpha(currentChar)) {
            wordLength++;
            charAmount++;
        } else {
            if (wordLength != 0) {
                char* word = malloc(wordLength+1);
                fread(word, 1, wordLength+1, file);
                word[wordLength] = '\0';
                int end = 0;
                node* prevNode = NULL;
                while (currentNode != NULL && !end) {
                    end = strcmp(word, currentNode->word);
                    if (end) {
                        prevNode = currentNode;
                        currentNode = currentNode->next;
                    }
                }
                //Word not found in list
                if (currentNode == NULL) {
                    node* newNode = malloc(sizeof(node));
                    newNode->amount = 1;
                    newNode->word = word;
                    newNode->next = NULL;
                    //prevNode should never be NULL
                    if (prevNode != NULL) {
                        prevNode->next = newNode;
                    } else exit(99);
                } else {
                    //Word found
                    currentNode->amount++;
                }
                currentNode = head;
                wordLength = 0;
                wordTotal++;
            }
        }
    }
    free(head);
    head = currentNode->next;
    currentNode = currentNode->next;
    rewind(file);
    puts("");

    printf("charAmount (without spaces, new lines, etc.): %ld\n", charAmount);
    printf("wordTotal: %ld\n", wordTotal);
    printf("words:\n");

    for (int i = 0; i<wordTotal;i++) {
        if (currentNode != NULL) {
            printf("word: %s, amount: %d", currentNode->word, currentNode->amount);
            currentNode = currentNode->next;
        }
    }
    while (head != NULL) {
        node* auxNode = head;
        head = head->next;
        free(auxNode);
    }
    fclose(file);
}