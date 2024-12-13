#include <stdio.h>

// 顺序查找
int sequential_search(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i; // 找到返回索引
        }
    }
    return -1; // 未找到
}

// 折半查找
int binary_search(int arr[], int size, int key) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) {
            return mid; // 找到返回索引
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // 未找到
}

int main() {
    int table1[] = {8, 15, 19, 26, 33, 41, 47, 52, 64, 90};
    int table2[] = {12, 76, 29, 15, 62, 35, 33, 89, 48, 20};
    int size1 = sizeof(table1) / sizeof(table1[0]);
    int size2 = sizeof(table2) / sizeof(table2[0]);
    int key1 = 41, key2 = 35;

    printf("顺序查找结果：\n");
    printf("表1中查找%d的结果：%d\n", key1, sequential_search(table1, size1, key1));
    printf("表2中查找%d的结果：%d\n", key2, sequential_search(table2, size2, key2));

    printf("折半查找结果：\n");
    printf("表1中查找%d的结果：%d\n", key1, binary_search(table1, size1, key1));

    return 0;
}
