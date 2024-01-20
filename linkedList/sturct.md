## 구조체 : struct와 typedef struct

- 구조체는 직접 변수의 형태를 만들 수 있는 문법을 말함
- 2가지 종류가 존재, struct와 typedef struct

### struct

```
struct student_info{
    int number;
    char name[20];
    int age;
}

int main(){
    struct student_info s = {1, "Hong gill, dong", 12};
    s.number = 10;
}
```

- struct는 main함수에서 변수를 선언할 때, struct를 명시해야 한다.
- 구조체 멤버에 접근하고 싶다면, '.'을 사용하여 접근한다.

### typedef struct

- typedef라는 키워드를 이용하면, 매번 struct 키워드를 붙이지 않아도 된다. 구조체의 별칭을 만들어서 키워드를 없앨 수 있다.

```
typedef struct student_info{
    int number;
    char name[20];
    int age;
}student;

int main(){
    student s = {1, "Hong gill dong", 10};
}
```

#### Question

```
typedef struct listNode *listPointer;
typedef struct {
    int data;
    listNode link;
} listNode;
```

- typedef 다음에 나오는 struct 정의에서 변수이름을 생략할 수 있는가?
  - 생략할 수 있음. 일반적으로 typedef를 사용하 때는 구조체의 이름을 새로운 타입의 이름으로 정의하는 것이 주요 목적이다. 따라서 변수 이름을 따로 정의하지 않아도 된다. 이렇게하면 해당 구조체를 사용할 때마다 변수 이름을 지정하지 않아도 된다.
