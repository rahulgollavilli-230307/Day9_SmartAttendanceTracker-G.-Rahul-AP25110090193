#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUEUE_SIZE 256

typedef struct {
    char data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} CharQueue;

// Initialize queue
void initQueue(CharQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if queue is empty
int isEmpty(CharQueue *q) {
    return q->size == 0;
}

// Check if queue is full
int isFull(CharQueue *q) {
    return q->size == MAX_QUEUE_SIZE;
}

// Enqueue a character
int enqueue(CharQueue *q, char c) {
    if (isFull(q)) {
        return 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = c;
    q->size++;
    return 1;
}

// Dequeue a character
char dequeue(CharQueue *q) {
    if (isEmpty(q)) {
        return '\0';
    }
    char c = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return c;
}

// Generate random character from a character set
char getRandomChar(const char *charset, int len) {
    return charset[rand() % len];
}

// Generate password using queue
void generatePassword(char *password, int length, int useUpper, int useLower, 
                      int useDigits, int useSpecial) {
    CharQueue queue;
    initQueue(&queue);
    
    // Define character sets
    const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *lowercase = "abcdefghijklmnopqrstuvwxyz";
    const char *digits = "0123456789";
    const char *special = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    
    // Build combined charset
    char charset[128] = "";
    if (useUpper) strcat(charset, uppercase);
    if (useLower) strcat(charset, lowercase);
    if (useDigits) strcat(charset, digits);
    if (useSpecial) strcat(charset, special);
    
    int charsetLen = strlen(charset);
    
    if (charsetLen == 0) {
        password[0] = '\0';
        return;
    }
    
    // Enqueue required characters (one from each selected set)
    if (useUpper) enqueue(&queue, getRandomChar(uppercase, 26));
    if (useLower) enqueue(&queue, getRandomChar(lowercase, 26));
    if (useDigits) enqueue(&queue, getRandomChar(digits, 10));
    if (useSpecial) enqueue(&queue, getRandomChar(special, strlen(special)));
    
    // Fill remaining length with random characters
    while (queue.size < length) {
        enqueue(&queue, getRandomChar(charset, charsetLen));
    }
    
    // Dequeue into temporary array
    char temp[MAX_QUEUE_SIZE];
    int i = 0;
    while (!isEmpty(&queue) && i < length) {
        temp[i++] = dequeue(&queue);
    }
    
    // Shuffle the characters (Fisher-Yates)
    for (int j = i - 1; j > 0; j--) {
        int k = rand() % (j + 1);
        char t = temp[j];
        temp[j] = temp[k];
        temp[k] = t;
    }
    
    // Copy to output
    memcpy(password, temp, length);
    password[length] = '\0';
}

int main() {
    srand((unsigned int)time(NULL));
    
    char password[MAX_QUEUE_SIZE];
    int length;
    int useUpper, useLower, useDigits, useSpecial;
    
    printf("=== Password Generator (Queue-Based) ===\n\n");
    
    printf("Enter password length (8-128): ");
    scanf("%d", &length);
    
    if (length < 8) length = 8;
    if (length > 128) length = 128;
    
    printf("Include uppercase letters? (1=yes, 0=no): ");
    scanf("%d", &useUpper);
    
    printf("Include lowercase letters? (1=yes, 0=no): ");
    scanf("%d", &useLower);
    
    printf("Include digits? (1=yes, 0=no): ");
    scanf("%d", &useDigits);
    
    printf("Include special characters? (1=yes, 0=no): ");
    scanf("%d", &useSpecial);
    
    // Ensure at least one character set is selected
    if (!useUpper && !useLower && !useDigits && !useSpecial) {
        printf("\nNo character sets selected. Using lowercase by default.\n");
        useLower = 1;
    }
    
    generatePassword(password, length, useUpper, useLower, useDigits, useSpecial);
    
    printf("\n----------------------------------------\n");
    printf("Generated Password: %s\n", password);
    printf("Length: %d characters\n", length);
    printf("----------------------------------------\n");
    
    return 0;
}
