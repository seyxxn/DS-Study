// 이진 탐색 트리에서의 탐색 
// 인수로 4가지를 받는다.
// 정렬된 배열 또는 리스트 list
// 현재 탐색 범위의 가장 작은 인덱스 low 
// 현재 탐색 범위의 가장 큰 인덱스 high
// 찾으려는 값 target

// target을 찾으면 해당 값의 인덱스를 반환하고, 찾지 못한 경우 -1을 반환
int search_binary(int list[], int low, int high, int target){
    if (low > high){
        // 원소를 찾지 못한 경우
        return -1;
    }

    int mid = (low + high) / 2; // 이진탐색이므로 가운데 값을 기준으로 
    if (list[mid] == target){
        // 원소를 찾은 경우
        return mid;
    } else if (list[mid] > target){
        // 찾는 값이 중간값보다 작은 경우, 왼쪽으로 탐색
        return search_binary(list, low, mid - 1, target);
    }else {
        // 찾는 값이 중간값보다 큰 경우, 오른쪽 탐색
        return search_binary(list, mid + 1, high, target);
    }
}