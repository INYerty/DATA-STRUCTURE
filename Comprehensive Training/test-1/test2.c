#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 100 // 定义队列的最大长度
#define MAX_WINDOWS 3 // 定义窗口的数量

// 顾客结构体
typedef struct {
    int id;           // 顾客ID
    int deposit;      // 存款金额
    int priority;     // 优先级
} Customer;

// 队列结构体
typedef struct {
    Customer customers[MAX_QUEUE]; // 顾客数组
    int front;                     // 队列头
    int rear;                      // 队列尾
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q->front = 0; // 初始化队列头
    q->rear = 0;  // 初始化队列尾
}

// 检查队列是否为空
int isEmpty(Queue *q) {
    return q->front == q->rear; // 如果队列头等于队列尾，队列为空
}

// 检查队列是否已满
int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE == q->front; // 如果队列尾的下一个位置是队列头，队列已满
}

// 入队
void enqueue(Queue *q, Customer c) {
    if (isFull(q)) { // 如果队列已满，打印提示信息
        printf("队列已满，无法加入更多顾客\n");
        return;
    }
    q->customers[q->rear] = c; // 将顾客加入队列尾
    q->rear = (q->rear + 1) % MAX_QUEUE; // 更新队列尾的位置
}

// 出队
Customer dequeue(Queue *q) {
    if (isEmpty(q)) { // 如果队列为空，打印提示信息并退出程序
        printf("队列为空，无法出队\n");
        exit(1);
    }
    Customer c = q->customers[q->front]; // 获取队列头的顾客
    q->front = (q->front + 1) % MAX_QUEUE; // 更新队列头的位置
    return c; // 返回出队的顾客
}

// 获取队列长度
int queueLength(Queue *q) {
    return (q->rear - q->front + MAX_QUEUE) % MAX_QUEUE; // 计算队列长度
}

// 根据存款金额设置优先级
int getPriority(int deposit) {
    if (deposit < 200000) {
        return 0; // 普通客户
    } else if (deposit <= 500000) {
        return 1; // VIP I级
    } else if (deposit <= 1000000) {
        return 2; // VIP II级
    } else {
        return 3; // VIP III级
    }
}

// 查找人数最少的队列
int findShortestQueue(Queue windows[]) {
    int minIndex = 0; // 初始化最短队列的索引
    int minLength = queueLength(&windows[0]); // 初始化最短队列的长度
    for (int i = 1; i < MAX_WINDOWS; i++) { // 遍历所有窗口
        int length = queueLength(&windows[i]); // 获取当前窗口的队列长度
        if (length < minLength) { // 如果当前窗口的队列长度小于最短队列的长度
            minIndex = i; // 更新最短队列的索引
            minLength = length; // 更新最短队列的长度
        }
    }
    return minIndex; // 返回最短队列的索引
}

// 叫号服务逻辑
void serveCustomer(Queue windows[]) {
    int highestPriority = -1; // 初始化最高优先级
    int windowIndex = -1; // 初始化最高优先级顾客所在的窗口索引

    // 找到优先级最高的顾客及其所在队列
    for (int i = 0; i < MAX_WINDOWS; i++) { // 遍历所有窗口
        if (!isEmpty(&windows[i])) { // 如果当前窗口的队列不为空
            Customer c = windows[i].customers[windows[i].front]; // 获取当前窗口队列头的顾客
            if (c.priority > highestPriority) { // 如果当前顾客的优先级高于最高优先级
                highestPriority = c.priority; // 更新最高优先级
                windowIndex = i; // 更新最高优先级顾客所在的窗口索引
            }
        }
    }

    // 如果找到优先级最高的顾客，进行服务
    if (windowIndex != -1) { // 如果找到最高优先级顾客
        Customer c = dequeue(&windows[windowIndex]); // 将顾客出队
        printf("窗口 %d 正在服务顾客 %d (存款: %d, 优先级: %d)\n", windowIndex + 1, c.id, c.deposit, c.priority); // 打印服务信息
    } else {
        printf("当前没有顾客等待服务\n"); // 如果没有顾客等待服务，打印提示信息
    }
}

int main() {
    Queue windows[MAX_WINDOWS]; // 定义窗口队列数组
    for (int i = 0; i < MAX_WINDOWS; i++) { // 初始化所有窗口队列
        initQueue(&windows[i]);
    }

    // 设置初始队列长度
    for (int i = 0; i < MAX_WINDOWS; i++) {
        int initialCount;
        printf("输入窗口 %d 的初始顾客人数: ", i + 1);
        scanf("%d", &initialCount);

        for (int j = 0; j < initialCount; j++) {
            Customer c;
            c.id = -1; // 初始顾客不需要具体ID
            c.deposit = 0; // 初始顾客存款默认为0
            c.priority = 0; // 初始顾客优先级默认为普通客户
            enqueue(&windows[i], c); // 将初始顾客加入队列
        }
    }

    int id = 1; // 新顾客ID递增
    char command[10]; // 存储用户输入的命令

    while (1) {
        printf("输入 'A' 添加顾客, 'S' 服务顾客, 'Q' 退出: "); // 打印提示信息
        scanf("%s", command); // 获取用户输入的命令

        if (strcmp(command, "A") == 0) { // 如果命令是 'A'
            Customer c;
            c.id = id++; // 设置顾客ID
            printf("输入存款金额: "); // 提示输入存款金额
            scanf("%d", &c.deposit); // 获取存款金额
            c.priority = getPriority(c.deposit); // 设置顾客优先级

            int windowIndex = findShortestQueue(windows); // 查找人数最少的队列
            enqueue(&windows[windowIndex], c); // 将顾客加入队列
            printf("顾客 %d (存款: %d, 优先级: %d) 已加入窗口 %d 队列\n", c.id, c.deposit, c.priority, windowIndex + 1); // 打印加入队列信息
        } else if (strcmp(command, "S") == 0) { // 如果命令是 'S'
            serveCustomer(windows); // 进行叫号服务
        } else if (strcmp(command, "Q") == 0) { // 如果命令是 'Q'
            printf("程序结束\n"); // 打印程序结束信息
            break; // 退出循环
        } else {
            printf("无效命令\n"); // 如果命令无效，打印提示信息
        }
    }

    return 0; // 返回0，程序结束
}
