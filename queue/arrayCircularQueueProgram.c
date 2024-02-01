// 환형 큐 예제 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define ERROR_CODE -1

typedef struct
{
    int id;
    char description[100];
} Task;

Task queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void queueFull()
{
    fprintf(stderr, "Queue is full, cannot add task\n");
    exit(EXIT_FAILURE);
}

Task queueEmpty()
{
    Task emptyTask;
    emptyTask.id = ERROR_CODE;
    fprintf(stderr, "Queue is empty, no task to process\n");
    return emptyTask;
}

void addQueue(Task task)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear)
        queueFull();
    queue[rear] = task;
}

Task deleteQueue()
{
    if (front == rear)
        return queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

void printQueue()
{
    int i;

    fprintf(stdout, "Front : %d, Rear : %d\n", front, rear);
    fprintf(stdout, "Queue : \n");

    if (front == rear)
    {
        printf("Empty\n");
        return;
    }

    i = (front + 1) % MAX_QUEUE_SIZE;
    while (1)
    {
        printf("Task ID : %d\n", queue[i].id);
        printf("Description : %s\n", queue[i].description);

        if (i == rear)
            break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("1. Add Task\n2. Precess Task\n3. Exit\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if ((rear + 1) % MAX_QUEUE_SIZE == front)
            {
                printf("Queue is full. Cannot add a new Task.\n");
            }
            else
            {
                Task newTask;
                newTask.id = rear + 2;
                printf("Enter task description : ");
                scanf(" %[^\n]", newTask.description);
                addQueue(newTask);
                printf("Task added successfully.\n");
            }
            break;
        case 2:
            if (front == rear)
            {
                printf("Queue is empty. No task to precess.\n");
            }
            else
            {
                Task task = deleteQueue();
                printf("Processing Task...\n");
                printf("Description : %s\n", task.description);
                printf("Task precessed succecfully.\n");
            }
            break;
        case 3:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        printQueue();
    }
    return 0;
}