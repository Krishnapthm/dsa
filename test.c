#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

// Structure to represent a circular queue
struct CircularQueue {
    char items[MAX_SIZE][30]; // Assuming each name has a maximum of 30 characters
    int front, rear;
};

// Function to initialize a circular queue
void initializeQueue(struct CircularQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if a circular queue is full
bool isFull(struct CircularQueue* queue) {
    return (queue->front == (queue->rear + 1) % MAX_SIZE);
}

// Function to check if a circular queue is empty
bool isEmpty(struct CircularQueue* queue) {
    return (queue->front == -1);
}

// Function to enqueue an item into a circular queue
void enqueue(struct CircularQueue* queue, const char* name) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue %s.\n", name);
    } else {
        if (isEmpty(queue))
            queue->front = 0;
        queue->rear = (queue->rear + 1) % MAX_SIZE;
        strcpy(queue->items[queue->rear], name);
    }
}

// Function to dequeue an item from a circular queue
char* dequeue(struct CircularQueue* queue) {
    char* item = (char*)malloc(30 * sizeof(char));
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return NULL;
    } else {
        strcpy(item, queue->items[queue->front]);
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % MAX_SIZE;
        }
        return item;
    }
}

// Function to display the contents of a circular queue
void displayQueue(struct CircularQueue* queue, const char* queueName) {
    if (isEmpty(queue)) {
        printf("%s queue is empty.\n", queueName);
    } else {
        printf("%s queue contents:\n", queueName);
        int i = queue->front;
        do {
            printf("%s\n", queue->items[i]);
            i = (i + 1) % MAX_SIZE;
        } while (i != (queue->rear + 1) % MAX_SIZE);
    }
}

int main() {
    struct CircularQueue vowelQueue, consonantQueue;
    initializeQueue(&vowelQueue);
    initializeQueue(&consonantQueue);

    char name[30];
    char choice;

    do {
        printf("Enter a name: ");
        scanf("%s", name);

        if ((name[0] == 'a' || name[0] == 'e' || name[0] == 'i' || name[0] == 'o' || name[0] == 'u' || name[0] == 'A' || name[0] == 'E'|| name[0] == 'I'|| name[0] == 'O'|| name[0] == '') &&
            !isFull(&vowelQueue)) {
            enqueue(&vowelQueue, name);
        } else if (!isFull(&consonantQueue)) {
            enqueue(&consonantQueue, name);
        } else {
            printf("Both queues are full. Cannot enqueue %s.\n", name);
        }

        printf("Do you want to enter another name? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    displayQueue(&vowelQueue, "Vowel");
    displayQueue(&consonantQueue, "Consonant");

    return 0;
}
