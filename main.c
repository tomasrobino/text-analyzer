#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    int amount;
    char* word;
    struct node_t *left;
    struct node_t *right;
} node;

void readFile(char name[]);
void printTree(const node* node);

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
    node* head = NULL;
    node* currentNode = head;
    long charAmount = 0;
    long wordLength = 0;
    long wordTotal = 0;
    for (int i = 0; i < byteAmount; i++) {
        const int currentChar = fgetc(file);
        if (isalpha(currentChar)) {
            wordLength++;
            charAmount++;
        } else {
            if (wordLength != 0) {
                char* word = malloc(wordLength+1);
                if (currentChar == -1) {
                    fseek(file, -wordLength, SEEK_CUR);
                } else fseek(file, -wordLength-1, SEEK_CUR);
                fread(word, 1, wordLength+1, file);
                word[wordLength] = '\0';
                for (int j = 0; j<wordLength+1;j++) {
                    word[j] = (char) tolower(word[j]);
                }
                if (head == NULL) {
                    head = malloc(sizeof(node));
                    head->left = NULL;
                    head->right = NULL;
                    head->amount = 1;
                    head->word = word;
                } else {
                    int comparison = 1;
                    node* prevNode = NULL;
                    while (currentNode != NULL && comparison) {
                        comparison = strcmp(word, currentNode->word);
                        if (comparison) {
                            prevNode = currentNode;
                            if (comparison < 0) {
                                currentNode = currentNode->left;
                            } else {
                                currentNode = currentNode->right;
                            }
                        }
                    }
                    //Word not found in list
                    if (currentNode == NULL) {
                        node* newNode = malloc(sizeof(node));
                        newNode->amount = 1;
                        newNode->word = word;
                        newNode->left = NULL;
                        newNode->right = NULL;
                        //prevNode should never be NULL
                        if (prevNode != NULL) {
                            comparison = strcmp(word, prevNode->word);
                            if (comparison < 0) {
                                prevNode->left = newNode;
                            } else {
                                prevNode->right = newNode;
                            }
                        } else free(newNode);
                    } else {
                        //Word found
                        free(word);
                        currentNode->amount++;
                    }
                }
                currentNode = head;
                wordLength = 0;
                wordTotal++;
            }
        }
    }
    rewind(file);
    puts("");
    currentNode = head;

    printf("charAmount (without spaces, new lines, etc.): %ld\n", charAmount);
    printf("wordTotal: %ld\n", wordTotal);
    printf("words:\n");
    printTree(currentNode);
    fclose(file);
}

void printTree(const node* node) {
    if (node == NULL) return;
    printf("word: %s, amount: %d\n", node->word, node->amount);
    if (node->left != NULL ) {
        printTree(node->left);
    }
    if (node->right != NULL) {
        printTree(node->right);
    }
}