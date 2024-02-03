// 실행 코드 아님

// 환형 큐에서의 원소 삽입
void addQueue(element item)
{
    rear = (rear + 1) % capacity;
    if (front == rear)
        queueFull();
    queue[rear] = item;
}

// 환형 큐의 확장
void queueFull()
{
    element *newQueue;
    MALLOC(newQueue, 2 * capacity * sizeof(*queue));

    int start = (front + 1) % capacity;
    if (start < 2)
        copt\y(queue+start, queue+start+capacity-1, newQueue);
    else{
        copy(queue+start, queue+capacity, newQueue);
        copy(queue, queue+rear+1, newQueue+capacity-start);
    }

    front = 2 * capacity -1;
    rear = capacity - 2;
    capacity *= 2;
    free(queue);
    queue = newQueue;
}