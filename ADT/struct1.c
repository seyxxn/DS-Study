// 구조체를 정의하는 예시
#include <stdio.h>
#include <string.h>
struct humanBeing {
    char name[10];
    int age;
    float salary;
};

int main(){
    struct humanBeing person;
    strcpy(person.name, "홍길동");
    person.age = 10;
    person.salary = 35000;

    printf("%s\n", person.name);
    printf("%d\n", person.age);
    printf("%f\n", person.salary);
    return 0;
}