#include <stdio.h>
#include <stdlib.h>

// 定义链表结点结构
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// 定义顺序表结构
typedef struct {
    int *data;
    int length;
    int listsize;
} SqList;

// 初始化顺序表
SqList* initSqList(int initial_capacity) {
    SqList *list = (SqList*)malloc(sizeof(SqList));
    list->data = (int*)malloc(initial_capacity * sizeof(int));
    list->length = 0;
    list->listsize = initial_capacity;
    return list;
}

// 扩容顺序表
void expandSqList(SqList *list) {
    list->listsize *= 2;
    list->data = (int*)realloc(list->data, list->listsize * sizeof(int));
}

// 顺序表插入（保持递增有序）
void insertInOrder(SqList *list, int x) {
    if (list->length >= list->listsize) {
        expandSqList(list);
    }
    int i = list->length - 1;
    while (i >= 0 && list->data[i] > x) {
        list->data[i + 1] = list->data[i];
        i--;
    }
    list->data[i + 1] = x;
    list->length++;
}

// 顺序表就地逆置
void reverseSqList(SqList *list) {
    for (int i = 0; i < list->length / 2; i++) {
        int temp = list->data[i];
        list->data[i] = list->data[list->length - 1 - i];
        list->data[list->length - 1 - i] = temp;
    }
}

// 用户输入顺序表数据
void inputData(SqList *list) {
    int x,t;
    printf("请输入顺序表元素个数：");
    scanf("%d",&t);
    printf("请输入%d个元素：",t);
    for(int i=0;i<t;i++)
    {
        scanf("%d", &x);
        insertInOrder(list, x);
    }
}

// 创建带头结点的循环链表
ListNode* createCircularList(int n) {
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->next = head;
    ListNode *tail = head;
    printf("请输入链表中的 %d 个元素：\n", n);
    for (int i = 0; i < n; i++) {
        ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
        scanf("%d", &newNode->data);
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
    }
    return head;
}

// 合并两个循环链表
void connectCircularLists(ListNode **L1, ListNode *L2) {
    ListNode *temp = (*L1)->next;
    while (temp->next != *L1) temp = temp->next;
    temp->next = L2->next;
    ListNode *temp2 = L2->next;
    while (temp2->next != L2) temp2 = temp2->next;
    temp2->next = *L1;
}

// 删除循环链表中某节点的前驱节点
void deletePreNode(ListNode *s) {
    ListNode *temp = s;
    while (temp->next != s) temp = temp->next;
    ListNode *preNode = temp;
    temp = s;
    while (temp->next != preNode) temp = temp->next;
    temp->next = preNode->next;
    free(preNode);
}

// 求两个递增链表的交集
ListNode* getIntersection(ListNode *A, ListNode *B) {
    ListNode *p = A->next, *q = B->next, *r = A;
    while (p != A && q != B) {
        if (p->data == q->data) {
            ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
            newNode->data = p->data;
            r->next = newNode;
            r = newNode;
            p = p->next;
            q = q->next;
        } else if (p->data < q->data) {
            p = p->next;
        } else {
            q = q->next;
        }
    }
    r->next = A;
    return A;
}

// 打印循环链表
void printCircularList(ListNode *head) {
    ListNode *temp = head->next;
    while (temp != head) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 打印顺序表
void printSqList(SqList *list) {
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 主菜单
void menu() {
    int choice, n;
    ListNode *L1 = NULL, *L2 = NULL;
    SqList *list = initSqList(10);

    do {
        printf("******************实验1 线性表的应用************\n");
        printf("1. 求集合的交集\n");
        printf("2. 两个单向循环链表的合并\n");
        printf("3. 顺序表的插入\n");
        printf("4. 顺序表的就地逆置\n");
        printf("5. 在循环单链表中求某个结点的前驱\n");
        printf("0. 退出\n");
        printf("请选择 (0-5):\n");
        printf("**************************************************\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("输入链表A的元素个数: ");
                scanf("%d", &n);
                L1 = createCircularList(n);
                printf("输入链表B的元素个数: ");
                scanf("%d", &n);
                L2 = createCircularList(n);
                getIntersection(L1, L2);
                printf("交集链表A的内容: ");
                printCircularList(L1);
                break;
            case 2: 
                printf("输入链表L1的元素个数: ");
                scanf("%d", &n);
                L1 = createCircularList(n);
                printf("输入链表L2的元素个数: ");
                scanf("%d", &n);
                L2 = createCircularList(n);
                connectCircularLists(&L1, L2);
                printf("合并后的链表L1内容: ");
                printCircularList(L1);
                break;
            case 3: 
                inputData(list);
                printf("插入后的顺序表内容: ");
                printSqList(list);
                break;
            case 4: 
                if (list->length > 0) {
                    reverseSqList(list);
                    printf("顺序表逆置后的内容: ");
                    printSqList(list);
                } else {
                    printf("顺序表为空，请先插入数据再进行逆置操作。\n");
                }
                break;
            case 5: 
                printf("输入链表的元素个数: ");
                scanf("%d", &n);
                L1 = createCircularList(n);
                ListNode *node = L1->next->next;
                deletePreNode(node);
                printf("删除前驱节点后的链表内容: ");
                printCircularList(L1);
                break;
            case 0: printf("退出程序。\n"); break;
            default: printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);

    free(list->data);
    free(list);
}

int main() {
    menu();
    return 0;
}
