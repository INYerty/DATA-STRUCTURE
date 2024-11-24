#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE 100

typedef struct TreeNode {  // 建立二叉树结点的结构体
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

// 创建二叉树
TreeNode* createTree() {
    char data;
    scanf(" %c", &data);  // 注意使用 %c 并加上空格忽略前导空白
    if (data == '#') {
        return NULL;  // '#' 表示空结点
    }
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));  // 为新的结点分配内存空间
    newNode->data = data;
    newNode->lchild = createTree();  // 函数的递归，创建左右子树
    newNode->rchild = createTree();
    return newNode;
}

// 先序遍历
void preOrder(TreeNode* x) {
    if (x == NULL) {
        return;
    }
    printf("%c ", x->data);
    preOrder(x->lchild);
    preOrder(x->rchild);
}

// 中序遍历
void inOrder(TreeNode* x) {
    if (x == NULL) {
        return;
    }
    inOrder(x->lchild);
    printf("%c ", x->data);
    inOrder(x->rchild);
}

// 后序遍历
void postOrder(TreeNode* x) {
    if (x == NULL) {
        return;
    }
    postOrder(x->lchild);
    postOrder(x->rchild);
    printf("%c ", x->data);
}

// 层次遍历
typedef struct {
    TreeNode* data[MAXQUEUE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

int isFull(Queue* q) {
    return (q->rear + 1) % MAXQUEUE == q->front;
}

void enterQueue(Queue* q, TreeNode* node) {
    if (!isFull(q)) {
        q->data[q->rear] = node;
        q->rear = (q->rear + 1) % MAXQUEUE;
    }
}

TreeNode* outQueue(Queue* q) {
    if (!isEmpty(q)) {
        TreeNode* node = q->data[q->front];
        q->front = (q->front + 1) % MAXQUEUE;
        return node;
    }
    return NULL;
}

void levelOrder(TreeNode* x) {
    if (x == NULL) {
        return;
    }
    Queue q;
    initializeQueue(&q);
    enterQueue(&q, x);

    while (!isEmpty(&q)) {  // 队列不为空时循环
        TreeNode* node = outQueue(&q);  // 出队一个结点
        printf("%c ", node->data);  // 输出结点数据

        if (node->lchild != NULL) {  // 如果左子结点不为空，将左子结点入队
            enterQueue(&q, node->lchild);
        }

        if (node->rchild != NULL) {  // 如果右子结点不为空，将右子结点入队
            enterQueue(&q, node->rchild);
        }
    }
}

// 二叉树深度
int treeDepth(TreeNode* x) {
    if (x == NULL) {
        return 0;
    }
    int leftDepth = treeDepth(x->lchild);  // 左子树深度
    int rightDepth = treeDepth(x->rchild);  // 右子树深度
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;  // 返回较大的深度加1
}

// 叶子结点的个数
int countLeafNodes(TreeNode* x) {
    if (x == NULL) {
        return 0;
    }
    if (x->lchild == NULL && x->rchild == NULL) {
        return 1;  // 当前结点是叶子结点，返回1
    }
    return countLeafNodes(x->lchild) + countLeafNodes(x->rchild);  // 递归求左右子树的叶子结点数
}

int main() {
    printf("请按先序输入二叉树（用#表示空节点）: ");
    TreeNode* x = createTree();
    int choice;
    while (1) {
        printf("\n请选择操作：\n");
        printf("1. 先序遍历\n");
        printf("2. 中序遍历\n");
        printf("3. 后序遍历\n");
        printf("4. 层次遍历\n");
        printf("5. 树的深度\n");
        printf("6. 叶子结点个数\n");
        printf("7. 退出\n");
        printf("选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("先序遍历：");
                preOrder(x);  // 执行先序遍历
                printf("\n");
                break;
            case 2:
                printf("中序遍历：");
                inOrder(x);  // 执行中序遍历
                printf("\n");
                break;
            case 3:
                printf("后序遍历：");
                postOrder(x);  // 执行后序遍历
                printf("\n");
                break;
            case 4:
                printf("层次遍历：");
                levelOrder(x);  // 执行层次遍历
                printf("\n");
                break;
            case 5:
                printf("树的深度：%d\n", treeDepth(x));  // 输出树的深度
                break;
            case 6:
                printf("叶子结点个数：%d\n", countLeafNodes(x));  // 输出叶子结点个数
                break;
            case 7:
                printf("退出程序。\n");  // 退出程序
                return 0;
            default:
                printf("无效选择，请重新输入。\n");  // 处理无效选择
        }
    }
}
