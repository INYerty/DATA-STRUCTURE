#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define STACKSIZE 100

// 循环链表结构体
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 循环队列结构体
typedef struct {
    Node *tail; // 队尾指针
} CirclularQueue;

// 初始化循环队列
void initializeQueue(CirclularQueue* queue) {
    Node* head = (Node*)malloc(sizeof(Node)); // 创建一个头节点
    head->next = head; // 头节点指向头结点，表示空队列
    queue->tail = head; // 尾结点指向头结点，表示队列是循环队列
}

// 入队
void enterqueue(int data, CirclularQueue* queue) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 创建一个新的结点用于存储入队元素的值
    newNode->data = data; // 入队的值
    newNode->next = queue->tail->next; // "queue->tail->next"相当于之前的"q.next"
    queue->tail->next = newNode;
    queue->tail = newNode; // queue->tail的指向由初始化时的head变为新插入的队尾元素newNode;
}

// 出队
int outqueue(CirclularQueue* queue) {
    if (queue->tail->next == queue->tail) { // 队尾指针
        printf("队列为空\n");
        return -1;
    }
    Node* head = queue->tail->next; // 获取头结点
    Node* front = head->next; // 第一个元素，即head->next;
    int x = front->data; // 用x来存储第一个元素的值
    head->next = front->next; // 之后把front free掉
    free(front);
    return x; // 将x出队列，输出
}

// 基于数组的循环队列
typedef struct {
    int data[MAXSIZE];
    int rear; // 尾指针
    int length;
} Arrayqueue;

// 初始化数组型的循环队列
void initializeArrayqueue(Arrayqueue* queue) {
    queue->rear = -1; // 赋值尾指针，表示队列为空
    queue->length = 0;
}

// 判断队列是否已满
int isFull(Arrayqueue* queue) {
    return queue->length == MAXSIZE;
}

// 入队
void enterArrayqueue(Arrayqueue* queue, int data) {
    if (isFull(queue)) {
        printf("队列已满\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAXSIZE;
    queue->data[queue->rear] = data;  // 将新元素插入队列
    queue->length++; // 队长度加一
}

// 出队
int outArrayqueue(Arrayqueue* queue) {
    if (queue->length == 0) {
        printf("队列为空\n");
        return -1;
    }
    int frontIndex = (queue->rear + 1 - queue->length + MAXSIZE) % MAXSIZE;  // 计算队列头元素的索引
    int x = queue->data[frontIndex];
    queue->length--;
    return x;
}

// 栈操作
typedef struct {
    int data[STACKSIZE];
    int top;
} Stack;

// 初始化栈
void initializeStack(Stack* stack) {
    stack->top = -1; // 栈顶指针为-1，表示栈空
}

// 判断栈是否为空
int isStackEmpty(Stack* stack) {
    return stack->top == -1; // 栈顶指针为-1，表示栈空
}

// 入栈
void enterStack(Stack* stack, int x) {
    if (stack->top == STACKSIZE - 1) {
        printf("栈已满\n");
        return;
    }
    stack->data[++stack->top] = x; // 将元素压入栈中
}

// 出栈
int outStack(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("栈为空\n");
        return -1;  // 返回-1表示栈为空
    }
    return stack->data[stack->top--];  // 返回栈顶元素并将栈顶指针下移
}

// 逆置单链表
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// 创建链表
ListNode* createList(int size) {
    ListNode* head = NULL;
    ListNode* tail = NULL; // 初始化头尾指针
    int data;

    for (int i = 0; i < size; i++) {
        printf("请输入第 %d 个节点的值: ", i + 1);
        scanf("%d", &data);

        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;  // 否则将尾节点的next指向新节点
            tail = newNode;  // 更新尾指针
        }
    }
    return head;
}

// 逆置链表
void reverseList(ListNode* head) {
    Stack stack;
    initializeStack(&stack);  // 初始化栈
    ListNode* temp = head;

    // 将链表节点的值压入栈中
    while (temp != NULL) {
        enterStack(&stack, temp->data);  // 入栈
        temp = temp->next;
    }

    // 从栈中弹出节点的值并更新链表
    temp = head;
    while (temp != NULL) {
        temp->data = outStack(&stack);  // 出栈并更新链表节点的值
        temp = temp->next;
    }
}

// 打印链表
void printList(ListNode* head) {
    ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);  // 打印节点的值
        temp = temp->next;
    }
    printf("NULL\n");  // 打印链表结束标识
}

int main() {
    CirclularQueue circularQueue;  // 创建循环链表队列变量
    Arrayqueue arrayQueue;         // 创建数组循环队列变量
    Stack stack;                   // 创建栈变量

    int choice, x, data, listSize;  // 选择、值和链表大小

    // 初始化队列和栈
    initializeQueue(&circularQueue);
    initializeArrayqueue(&arrayQueue);
    initializeStack(&stack);

    while (1) {
        printf("\n请选择操作：\n1. 循环链表队列的入队/出队\n");
        printf("2. 数组循环队列的入队/出队\n");
        printf("3. 栈操作\n4. 逆置单链表\n0. 退出\n");
        scanf("%d", &choice);  // 输入选择

        switch (choice) {
            case 1:
                printf("输入1入队，2出队：");
                int op;
                scanf("%d", &op);  // 输入入队或出队操作
                if (op == 1) {
                    printf("输入入队值：");
                    scanf("%d", &x);  // 输入入队的值
                    enterqueue(x, &circularQueue);  // 执行入队操作
                } else if (op == 2) {
                    printf("出队值：%d\n", outqueue(&circularQueue));  // 执行出队操作并打印出队值
                }
                break;

            case 2:
                printf("输入1入队，2出队：");
                scanf("%d", &op);  // 输入入队或出队操作
                if (op == 1) {
                    printf("输入入队值：");
                    scanf("%d", &data);  // 输入入队的值
                    enterArrayqueue(&arrayQueue, data);  // 执行入队操作
                } else if (op == 2) {
                    printf("出队值：%d\n", outArrayqueue(&arrayQueue));  // 执行出队操作并打印出队值
                }
                break;

            case 3:
                printf("输入整数入栈，输入-1出栈：");
                scanf("%d", &data);  // 输入栈操作
                if (data == -1) {
                    printf("出栈值：%d\n", outStack(&stack));  // 执行出栈操作并打印出栈值
                } else {
                    enterStack(&stack, data);  // 执行入栈操作
                }
                break;

            case 4:
                // 选择逆置链表时询问链表的大小并创建链表
                printf("请输入链表的大小: ");
                scanf("%d", &listSize);  // 输入链表的大小
                ListNode* list = createList(listSize);  // 创建链表
                printf("原链表：\n");
                printList(list);  // 打印原链表
                reverseList(list);  // 逆置链表
                printf("逆置后的链表：\n");
                printList(list);  // 打印逆置后的链表
                break;

            case 0:
                printf("退出程序\n");
                exit(0);  // 退出程序

            default:
                printf("无效选择\n");
        }
    }

    return 0;
}
