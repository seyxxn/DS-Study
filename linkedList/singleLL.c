#include <stdio.h>
#include <stdlib.h>

// 단일 연결 리스트
// https://codejin.tistory.com/136 참고

// 연결 리스트 구현 시, 일단 노드가 필요
// 노드에는 다음 노드를 가리킬 포인터와 데이터로 구성됨

typedef struct Node
{
    int data;          // 데이터
    struct Node *next; // 다음 노드를 가리킬 포인터
} node;

// head 노드를 동적할당으로 생성
// head 노드에는 데이터가 들어가있지는 않고, 단지 다음 노드를 가르키는 연결리스트의 중심과 같은 노드

int main()
{
    node *head = (node *)malloc(sizeof(node));
    head->data = 0;
    head->next = NULL;
    // 우선 널로 초기화 함
}

/* < 삽입 과정 >
1. 삽입하고자 하는 위치의 앞까지 간다. 이때의 노드가 NULL이 아니라면, 이 노드를 임시로 저장한다. 이때의 노드를 a라고 하자.
2. 새로운 노드를 동적할당하여 생성한다. 이때의 노드를 b라고 하자.
3. b에 새로운 데이터를 담고, 이 노드의 next를 a의 next로 저장한다.
4. a의 next를 b로 바꾼다. */

// head : 연결리스트의 시작을 나타내는 노드 포인터
// index : 삽입하고자 하는 위치의 인덱스
// data : 삽입할 노드의 데이터 값
void insert_node(node *head, const int index, const int data)
{
    int k = index;         // 삽입하고자 하는 인덱스 값을 k에 저장
    node *pre_node = head; // index-1번째 노드를 가리킬 임시 변수 (1번 과정에서 필요한 임시 변수)
    // 임시 노드 포인터를 생성하고, 이를 연결 리스트의 시작인 head로 초기화

    node *insert = (node *)malloc(sizeof(node)); // 추가할 노드를 동적할당으로 생성
    insert->data = data;                         // 데이터를 담는다.

    // index-1 번쨰로 이동(삽입하고자 하는 위치의 앞까지 간다.)
    // 만약 index가 연결리스트 범위를 초과한다면(null) 반복을 멈춤
    // 반복문을 사용하여 index-1 번째 노드로 이동.
    while (k-- && pre_node != NULL)
    {
        pre_node = pre_node->next;
    }

    // 만약 null이라면
    // pre_node가 NULL이라면, 삽입할 위치가 연결리스트의 범위를 벗어났으므로,
    // 메모리 누수를 방지하기 위해 새로 할당한 노드를 해제하고 함수를 종료
    if (pre_node == NULL)
    {
        free(insert); // 동적할당을 해제하고
        return;       // 돌아간다.
    }

    insert->next = pre_node->next; // 새로 생성한 노드는 index-1번째 노드가 가르키던 노드를 가르키고
    pre_node->next = insert;       // index-1번째 노드는 insert를 가르키게 한다.
}

/* <삭제 과정>
1. 삭제하고자 하는 노드 바로 앞까지 이동한다. 이때 이 다음노드가 NULL이 아니라면, 이 노드를 임시로 저장한다. 이떄 이 노드를 a라고 한다.
2. 삭제할 노드는 저장한 노드의 다음 노드이다. 그 노드를 임시로 저장한다. 이때의 노드를 b라고 하자.
3. b의 next를 a의 next에 저장한다.
4. b를 삭제한다. */

/* **?
삭제과정에서는 삽입과정과 달리 null체크를 본인 노드가 아닌 다음 노드도 체크함.
삽입의 경우, 다음 노드가 null이더라도 본인이 null이 아니라면 추가가 가능하기 때문에 본인이 null인지 체크해야 함.
하지만 삭제의 경우, 본인이 null이면 while문 중간에서 조건이 false가 되어 반복을 멈추고, 본인이 null이면 next도 null 이기 때문이다.
또한 본인이 null이 아닌 경우, 다음 null 노드는 지울 수가 없기 때문에 다음 노드가 null인지 체크하는 것이다.
*/

void delete_node(node *head, const int index)
{
    int k = index;         // 인덱스 저장
    node *pre_node = head; // index-1 번째 노드를 가리킬 임시 변수
    node *garbage = NULL;  // 삭제할 노드를 저장할 임시 변수

    while (k-- && pre_node != NULL)
    {
        pre_node = pre_node->next; // index-1번째 노드로 이동
    }

    // 본인 또는 다음 노드가 NULL이라면 그냥 돌아간다. (삭제가 안된다.)
    if (pre_node == NULL || pre_node->next == NULL)
        return;

    garbage = pre_node->next;       // 삭제할 노드를 저장
    pre_node->next = garbage->next; // 사제할 노드의 다음 노드와 연결
    free(garbage);                  // 노드를 삭제
}

// <탐색 과정>
// 찾고자하는 값이 몇번째 인덱스에 존재하는지 인덱스를 반환하는 함수
int search(node *head, const int val)
{
    // 이 경우 연결리스트가 비어있는 경우를 나타냄 (즉, 검색할 값이 없다는 것)
    if (head->next == NULL)
        return -1; // 다음노드가 NULL이면 -1 return

    int index = 0; // 찾으려는 값의 인덱스
    // 임시 포인터 생성하고, 연결리스트의 첫번째 실제 노드를 가리키게 함
    // (head는 단지 연결리스트의 시작점을 나타내기 때문에, 실제 데이터가 있는 첫번째 노드부터 검색을 시작하려면 head->next를 사용)
    node *temp = head->next;
    // head는 기준일 뿐, index를 세는데에는 들어가면 안됨

    // 값을 찾을 때까지 반복함
    while (temp->data != val)
    {
        ++index;           // 반복이 한번 일어날 때 마다 인덱스를 증가시킴
        temp = temp->next; // 다음노드로 이동

        if (temp == NULL)
            return -1; // 찾으려하는 값이 없는 경우 -1 반환
    }

    return index;
}

// 인덱스에 해당하는 값을 가져오는 함수
int get_data(node *head, const int index)
{
    // 연결리스트가 비어있는 경우를 나타냄
    if (head->next == NULL)
        return -1;

    int k = index;
    node *temp = head->next;

    while (k--)
        temp = temp->next; // index로 이동한다.
    return temp->data;
}

// 연결리스트의 길이를 반환하는 함수
int size(node *head)
{
    node *temp = head->next;
    int len = 0;
    while (temp != NULL)
    {
        ++len;
        temp = temp->next;
    }
    return len;
}

// 연결리스트를 순회하며 출력하는 함수
void print_ll(node *head)
{
    // 연결리스트가 비어있는 경우
    if (head->next == NULL)
        return;

    node *temp = head->next;
    while (temp != NULL)
    {                              // temp가 null이 아닐 때 까지
        printf("%d ", temp->data); // 공백으로 구분하여 출력함
        temp = temp->data;         // 다음노드로 이동
    }
    printf("\n");
}