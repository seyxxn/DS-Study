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

// 이진 탐색 트리에서의 삽입
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 이진탐색트리에 노드 삽입 함수
TreeNode *insert(TreeNode *root, int data){
    // 빈 트리인 경우 새 노드를 생성하여 반환
    if (root == NULL) {
        return createNode(data);
    }

    // 데이터가 현재 노드의 데이터와 같다면, 아무 작업도 하지 않음
    if (data == root->data){
        return root;
    }

    // 데이터가 현재 노드의 데이터보다 작으면 왼쪽 서브 트리에 삽입
    if (data < root->data){
        root->left = insert(root->left, data);
    }

    // 데이터가 현재 노드의 데이터보다 크면 오른쪽 서브 트리에 삽입
    else {
        root->right = insert(root->right, data);
    }
    return root;
}