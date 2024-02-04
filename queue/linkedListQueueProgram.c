#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;

typedef struct queueNode
{
    element item;
    struct queueNode *link;
} queueNode;

typedef struct 
{
    queueNode *front;
    queueNode *rear;
} queueType;

void error(char *message);
void init(queueType *q);
int queueEmpty(queueType *q);
void addQueue(queueType *q, element item);
element deleteQueue(queueType *q);
element peek(queueType *q);

int main(int argc, char *argv[])
{
    queueType q;
    init(&q);
    addQueue(&q, 1);
    addQueue(&q, 2);
    addQueue(&q, 3);
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));

    return 0;
}

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(queueType *q)
{
    q->front = q->rear = NULL;
}

int queueEmpty(queueType *q)
{
    return (q->front == NULL);
}

void addQueue(queueType *q, element item)
{
    queueNode *temp = (queueNode *)malloc(sizeof(queueNode));
    if (temp == NULL)
    {
        error("Memory allocation error");
    }
    else {
        temp->item = item;
        temp->link = NULL;
        if (queueEmpty(q))
        {
            q->front = temp;
            q->rear = temp;
        }
        else {
            q->rear->link = temp;
            q->rear = temp;
        }
    }
}

element deleteQueue(queueType *q)
{
    queueNode *temp = q->front;
    element item;
    if(queueEmpty(q))
        error("Queue is empty.");
    
    item = temp->item;
    q->front = q->front->link;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return item;
}

element peek(queueType *q)
{
    if (queueEmpty(q))
        error("Queue is empty.");
    return q->front->item;
}