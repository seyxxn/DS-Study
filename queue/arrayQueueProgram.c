// 큐를 활용한 간단한 작업 관리 시스템 프로그램 예

#include <stdio.h>
#define MAX_QUEUE_SIZE 100

typedef struct
{
    int id;                // 작업 ID
    char description[100]; // 작업 설명
} Task;

Task queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

int isQueueEmpty()
{
    return (rear == front);
}

int isQueueFull()
{
    return (rear == MAX_QUEUE_SIZE - 1);
}

void enQueue(Task task)
{
    if (isQueueFull())
    {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue[++rear] = task;
}

Task deQueue()
{
    if (isQueueEmpty())
    {
        printf("Queue is empty. Cannot dequeue.\n");
        Task emptyTask;
        emptyTask.id = -1;
        return emptyTask;
    }
    return queue[++front];
}

void printTask(Task task)
{
    printf("Task ID : %d\n", task.id);
    printf("Description : %s\n", task.description);
}

int main()
{
    int choice;
    while (1)
    {
        printf("1. Add Task \n2. Process Task \n3. Exit \nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (!isQueueFull())
            {
                Task newTask;
                newTask.id = rear + 2;
                printf("Enter task description : ");
                scanf(" %[^\n]", newTask.description);
                enQueue(newTask);
                printf("Task added succesfully.\n");
            }
            else
            {
                printf("Queue is full. Cannot add a new task.\n");
            }
            break;
        case 2:
            if (!isQueueEmpty())
            {
                Task task = deQueue();
                printf("Processing Task...\n");
                printTask(task);
                printf("Task processed successfully.\n");
            }
            else
            {
                printf("Queue is empty. No task to process.\n");
            }
            break;
        case 3:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    return 0;
}