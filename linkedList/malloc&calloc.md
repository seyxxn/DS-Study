## malloc()과 calloc()
동적 메모리 할당

### malloc()
- 메모리 블럭을 동적으로 할당하는 데 사용
- 지정된 크기의 메모리 공간을 예약
- 메모리 위치를 가리키는 널 포인터를 반환
- 할당된 공간이 쓰레기 값으로 채워짐
- 인자 1개

#### 사용방법
```
malloc(size_t size);
```
### calloc()
- 여러 메모리 블록을 할당하는 데 사용
- size만큼 0으로 초기화 개
- 인자 2개

#### 사용방법
```
calloc(size_t count, size_t size)  
```

- count : 할당할 byte의 수 (할당할 메모리의 단위 갯수)  
- size : 0으로 초기화 할 byte의 수 (size하나 당 크기)  
예) 4개 * 4바이트, 10개 * 1바이트