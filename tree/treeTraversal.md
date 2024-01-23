## 트리 순회 (Tree Traversal)

- 트리의 모든 노드들을 방문하는 과정을 트리 순회라고 함
- 트리 순회에는 전위 순회, 중위 순회, 후위 순회가 존재함
- 순회는 보통 재귀로 쉽게 구현이 가능함

### 전위 순회 (Preorder Traversal)

- Root - Left - Right 순서로 방문함
- 전위 순회는 깊이 우선 순회 (DFS)라고 하기도 함
- 트리를 복사하거나, 전위 표기법을 구하는데 주로 사용
- 트리를 복사할 때 전위 순회를 사용하는 이유는 트리를 생성할 때 자식 노드보다 부노 노드가 먼저 생성되어야 하기 때문이다.

```
void preorder(treePointer root)
{
    if (root)
    {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
```

### 후위 순회 (Postorder Traversal)

- Left - Right - Root 순서로 방문함
- 후위 순회는 트리를 삭제하는 데 주로 사용한다.
- 그 이유는, 부모 노드를 삭제하기 전에 자식 노드를 삭제하는 순으로 삭제를 해야하기 때문이다.

```
void postorder(treePointer root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}
```

### 중위 순회 (Inorder Traversal)

- Left - Root - Right 순서로 방문함
- 중위 순회는 왼쪽 오른쪽 대칭 순서로 순회를 하기 때문에 대칭 순회라고도 한다.
- 중위 순회는 이진탐색트리에서 오름차순 또는 내림차순으로 값을 가져올 때 사용
- 보통 왼쪽이 루트보다 작은 값, 오른쪽은 루트보다 큰 값을 가지므로, 내림차순으로 값을 가져오기 위해서는 역순(Right - Root - Left)으로 중위 순회를 하면 된다.

```
void inorder(treePointer root)
{
    if (root)
    {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}
```
