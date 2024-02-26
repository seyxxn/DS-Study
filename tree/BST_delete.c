// 이진 탐색 트리에서 노드 삭제 함수
TreeNode *deleteNode(TreeNode *root, int key){
    // 트리가 비어있는 경우
    if (root == NULL){
        return root;
    }

    // 삭제할 노드를 찾아야함
    if (key < root->data){
        // 삭제할 값 < 현재 루트 노드 값 -> 왼쪽으로 가야함
        root->left = deleteNode(root->left, key);
    } else if (key > root->data){
        // 삭제할 값 > 현재 루트 노드 값 -> 오른쪽으로 가야함
        root->right = deleteNode(root->right, key);
    } else {
        // 삭제할 노드를 찾은 경우
        // CASE 1 : 리프 노드인 경우 (자식이 없는 경우)
        if (root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        // CASE 2 : 하나의 자식 노드를 가지는 경우
        else if (root->left == NULL){
            // 오른쪽 자식 노드만 가지는 경우
            TreeNode *temp = root;
            root = root->right; // 오른쪽과 연결
            free(temp);
        }
        else if (root->right == NULL){
            //  왼쪽 자식 노드만 가지는 경우
            TreeNode *temp = root;
            root = root->left; // 왼쪽과 연결
            free(temp);
        }
        // CASE 3 : 두 개의 자식노드를 가지는 경우
        else {
            // 오른쪽 서브 트리에서 가장 작은 값을 가진 노드를 찾음
            TreeNode *temp = findMin(root->right);
            // 찾은 노드의 값을 삭제할 노드로 복사
            root->data = temp->data;
            // 오른쪽 서브 트리에서 복사한 값을 가진 노드를 삭제
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}