// 이진탐색트리에서의 탐색
int search_binary(int list[], int high, int target){
    if (low > high){
        return -1;
    }
    int min = (low+high) / 2;
    if (list[mid] == target){
        return mid;
    } else if (list[mid] > target){
        return search_binary(list, low, mid - 1, target);
    } else {
        return search_binary(list, mid+1, high, target);
    }
}