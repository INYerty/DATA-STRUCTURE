#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // 定义线性表的最大容量

// 定义线性表结构体
typedef struct {
    int data[MAX_SIZE]; // 存储数据的数组
    int length;         // 线性表当前的长度
} LinearList;

// 初始化线性表
void initList(LinearList *list) {
    list->length = 0; // 初始化长度为0
}

// 插入元素
int insert(LinearList *list, int index, int value) {
    if (index < 0 || index > list->length || list->length >= MAX_SIZE) {
        return -1; // 插入位置不合法或线性表已满
    }
    
    // 将插入位置之后的元素后移
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    
    // 插入新元素
    list->data[index] = value;
    list->length++; // 更新线性表长度
    return 0; // 插入成功
}

// 删除元素
int delete(LinearList *list, int index) {
    if (index < 0 || index >= list->length) {
        return -1; // 删除位置不合法
    }

    // 将删除位置之后的元素前移
    for (int i = index; i < list->length - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->length--; // 更新线性表长度
    return 0; // 删除成功
}

// 显示线性表
void displayList(LinearList *list) {
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main() {
    LinearList list; // 声明线性表
    initList(&list); // 初始化线性表

    // 测试插入
    insert(&list, 0, 10);
    insert(&list, 1, 20);
    insert(&list, 1, 15); // 在索引1处插入15
    printf("当前线性表: ");
    displayList(&list); // 显示线性表

    // 测试删除
    delete(&list, 0); // 删除索引1的元素
    printf("删除索引0后的线性表: ");
    displayList(&list); // 显示线性表

    return 0;
}
