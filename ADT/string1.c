#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 문자열 : 배열의 원소가 문자인 데이터 타입
// C언어에서는 문자열을 널 문자 \0 로 끝나는 문자 배열을 의미함

int main()
{
    // 문자열 변수 선언과 초기화
    char s1[100] = {"dog"};
    char t1[] = {"house"};

    // 문자열 관련 함수 -> string.h에 모두 정의된다.

    // 1. strcat(a,b) : a스트링과 b스트링을 연결시켜 a스트링으로 결과를 반환함
    printf("%s\n", strcat(s1, t1));
    printf("%s\n", s1); // 변경됨
    printf("%s\n", t1); // 그대로

    printf("============\n");

    char s2[100] = {"dog"};
    char t2[] = {"house"};

    // 2. strncat(a,b,n) : b스트링의 n개의 문자와 a스트링을 연결하여 a스트링으로 결과를 반환함
    printf("%s\n", strncat(s2, t2, 3));

    char s3[100] = {"dog"};
    char t3[] = {"house"};

    printf("============\n");

    // 3. strcmp(a,b) : 두 스트링을 비교함.

    // 4. strncmp(a,b,n) : 두 스트링을 n개의 문자까지만 비교함.

    // 5. strcpy(a,b) : b스트링을 a스트링에 복사하여 a스트링으로 결과를 반환홤.

    // 6. strncpy(a,b,n) : n개의 b스트링을 a스트링에 복사하여 a스트링으로 결과를 반환홤.

    // 7. strlen(s) : 스트링의 길이를 반환홤
    printf("%lu\n", strlen(s3));

    printf("==========\n");

    // 8. strchr(a,b) : a스트링에서 b스트링의 내용이 처음 나오는 곳의 포인터를 반환, 없으면 NULL 반환.

    // 9. strrchr(a,b) : a스트링에서 b스트링의 내용이 마지막으로 나오는 곳의 포인터를 반환, 없으면 NULL 반환.

    // 10. strtok(s, deter) : s스트링을 deter로 구분하여 토큰을 반환함
    char str[] = "손흥민,봉준호,제이팍";
    char *ptr = strtok(str, ",");
    while (ptr != NULL)
    {
        printf("%s\n", ptr);
        ptr = strtok(NULL, ",");
    }

    printf("===========\n");

    // 11. strstr(a, b) : a스트링에서 b스트링과 일치하는 문자열이 있는지 확인하는 함수. 있다면 그 시작 포인터를 반환하고 없으면 NULL 반환
    char str1[] = "James. He is a smart man";
    char str2[] = "smart";
    char *ptr1 = strstr(str1, str2);
    if (ptr1 != NULL)
    {
        strncpy(ptr1, "idiot", 5); // 이렇게하면 5글자만 복사됨
        printf("strstr example : %s\n", str1);
    }

    printf("===========\n");

    char str3[] = "James. He is a smart man";
    char str4[] = "smart";
    char *ptr2 = strstr(str3, str4);
    if (ptr2 != NULL)
    {
        strcpy(ptr2, "idiot"); // 이렇게하면 포인터 뒤의 모든 글자가 복사됨
        printf("strstr example : %s\n", str3);
    }

    return 0;
}