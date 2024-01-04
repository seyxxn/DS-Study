#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int nfind(char *string, char *pat);

int main(){
    char pat[]= "aab";
    char string[] = "ababbaabaa";

    printf("%s\n%s\nArray[%d]\n", string, pat, nfind(string, pat));
}

// 문자열 패턴 매칭 함수
// string 문자열 내에 pat 문자열 패턴이 존재하는지 확인하는 함수
// 패턴이 매칭하면, 패턴의 시작점을 반환 (시작 인덱스 반환)
// 패턴이 없으면 -1 반환

int nfind(char *string, char *pat){
    int i,j, start = 0;

    int lasts = strlen(string)-1; // string 문자열의 마지막 위치
    int lastp = strlen(pat)-1; // pat 문자열의 마지막 위치
    int endmatch = lastp; // string 문자열의 현재 문자 인덱스로, pat 문자열의 마지막 문자와 일치해야 함

    // 외부 루프
    for(i=0; endmatch <= lasts; endmatch++, start++){
        // string 문자열에서 가리키고 있는 현재 문자 인덱스가 string 문자열의 길이를 넘지 않을 때 까지 반복함 
        // 한번의 반복이 끝날 때 마다, endmatch와 start가 한칸씩 이동함(커짐)
        // endmatch와 start는 string문자열 내에서 쌍으로 같이 이동함
        if(string[endmatch] == pat[lastp]){
            // string의 endmatch위치의 문자와 pat의 마지막 문자가 일치하다면, 내부 루프로 들어옴
            for(j=0, i=start; j < lastp && string[i] == pat[j]; i++, j++);
            // 내부루프에서는 pat의 모든 문자가 string의 현재 start위치부터 순서대로 일치하는 지 확인한다.
        }
        // j가 lastp에 도달했다면, pat의 모든 문자가 string의 start에서 시작하는 부분과 일치함을 의미함
        if(j==lastp){
            return start; // 패턴의 시작점을 반환함(패턴 매칭 성공)
        }
    }
    return -1; // 매칭되는 패턴이 없으면 -1을 반환 (패턴 매칭 실패)
}