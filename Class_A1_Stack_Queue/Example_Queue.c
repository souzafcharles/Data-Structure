/*
Class title: Data Structure
Lecturer: Prof. Dr. Rodrigo Elias Bianchi
Example adapted by: Charles Fernandes de Souza
Date: August 10, 2021
*/

#include <stdio.h>
#include <stdlib.h>

struct QUEUE {
    int queueCapacity;
    float *data;
    int first;
    int last;
    int numeroItems;
};

void createQueue(struct QUEUE *q, int capacity) {
    q->queueCapacity = capacity;
    q->data = (float*) malloc(q->queueCapacity * sizeof(float ));
    q->first = 0;
    q->last = 0;
    q->numeroItems = 0;
}

void insertNumber(struct QUEUE *q, int number) {
    if (q->last == q->numeroItems -1) {
        q->last = -1;
    }
    q->last++;
    q->data[q->last] = number; 
    q->numeroItems++; 
}

int removeNumber(struct QUEUE *q) {
    int temp = q->data[q->first++]; 
    if(q->first == q->numeroItems) {
        q->first = 0;
    }
    q->numeroItems--;
    return temp;
}

int isEmpty(struct QUEUE *q) {
    return (q->numeroItems==0); 
}

int isFull(struct  QUEUE *q) {
    return (q->numeroItems == q->queueCapacity); 
}

void showQueue(struct QUEUE *q) {
    int count, i;
    for (count=0, i = q->first; count < q->numeroItems; count++) {
        printf("%.2f\n", q->data[i++]);
        if(i == q->queueCapacity){
            i = 0;
        }
    }
    printf("\n\n");
}

int main() {
    struct QUEUE simpleQUEUE;
    createQueue(&simpleQUEUE, 10);

    isFull(&simpleQUEUE);
    showQueue(&simpleQUEUE);

    insertNumber(&simpleQUEUE,2);
    showQueue(&simpleQUEUE);

    insertNumber(&simpleQUEUE,3);
    showQueue(&simpleQUEUE);

    insertNumber(&simpleQUEUE,4);
    showQueue(&simpleQUEUE);

    showQueue(&simpleQUEUE);

    printf("\n");
    system("pause");
    return 0;
}
