 # 과제 1 : Expression Evaluation
 연산자과 피연산자로 표현되는 수식은 전위식, 중위식, 후위식으로 나타낼 수 있다.  
 Linked List로 Stack 및 Queue를 직접 구현하고, 수식 분석기를 설계 및 구현한다.  

 - 구현내용
    1) 사용자로부터 3가지 표기법 중 하나를 입력 받음
    2) 입력된 수식을 분석하고 계산하여 결과를 출력

## 구현 단계
1. 프로그램 입력 방식에 따른 처리
    - 명령행 인자로 수식 입력하는 방법
    - 프로그램 실행 후 표준입력(키보드)로부터 수식을 입력하는 방법
2. 예외 처리 (입력시 예외)
    - 공백 입력 시 처리
    - 토큰 오입력 예외 처리
    - (명세x) 연산자 1개 입력 시 예외 처리
    - (명세x) 토큰 2개 입력 시 예외 처리
3. 사용자에게 입력을 받은 문자열을 공백 단위로 토큰을 쪼개서 스택에 저장우
4. 입력받은 문자열이 전위인지 후위인지 중위인지 구분하는 함수 구현
5. 중위->후위, 중위->전위, 전위->중위, 전위->후위 변환하는 함수 4개 구현
6. 후위표기식을 가지고 계산하는 함수 구현
7. 예외 처리 (후에 처리하는 예외)
    - 숫자 하나 입력 시 예외 처리
    - 0으로 나누는 수식 예외 처리


