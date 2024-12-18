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
    int isNew;        // 是否为新顾客（1: 新顾客, 0: 初始顾客）
} Customer;

// 队列结构体
typedef struct {
    Customer customers[MAX_QUEUE]; // 顾客数组
    int front;                     // 队列头
    int rear;                      // 队列尾
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

// 检查队列是否为空
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

// 检查队列是否已满
int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE == q->front;
}

// 入队
void enqueue(Queue *q, Customer c) {
    if (isFull(q)) {
        printf("队列已满，无法加入更多顾客\n");
        return;
    }
    q->customers[q->rear] = c;
    q->rear = (q->rear + 1) % MAX_QUEUE;
}

// 出队
Customer dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("队列为空，无法出队\n");
        exit(1);
    }
    Customer c = q->customers[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    return c;
}

// 获取队列长度
int queueLength(Queue *q) {
    return (q->rear - q->front + MAX_QUEUE) % MAX_QUEUE;
}

// 根据存款金额设置优先级
int getPriority(int deposit) {
    if (deposit < 200000) return 0;  // 普通客户
    if (deposit <= 500000) return 1; // VIP I级
    if (deposit <= 1000000) return 2; // VIP II级
    return 3; // VIP III级
}

// 查找人数最少的队列
int findShortestQueue(Queue windows[]) {
    int minIndex = 0;
    int minLength = queueLength(&windows[0]);
    for (int i = 1; i < MAX_WINDOWS; i++) {
        int length = queueLength(&windows[i]);
        if (length < minLength) {
            minIndex = i;
            minLength = length;
        }
    }
    return minIndex;
}

// 服务顾客逻辑
void serveCustomer(Queue windows[]) {
    int highestPriority = -1;
    int selectedWindow = -1;
    int selectedPosition = -1;

    // 遍历所有窗口，找到优先级最高的 **新顾客**
    for (int i = 0; i < MAX_WINDOWS; i++) {
        int length = queueLength(&windows[i]);
        int currentPos = windows[i].front;

        for (int j = 0; j < length; j++) {
            Customer c = windows[i].customers[currentPos];
            if (c.isNew && (c.priority > highestPriority || 
                (c.priority == highestPriority && selectedWindow == -1))) {
                highestPriority = c.priority;
                selectedWindow = i;
                selectedPosition = currentPos;
            }
            currentPos = (currentPos + 1) % MAX_QUEUE;
        }
    }

    // 服务选中的新顾客
    if (selectedWindow != -1 && selectedPosition != -1) {
        Customer c = windows[selectedWindow].customers[selectedPosition];
        
        // 调整队列，删除已服务的顾客
        for (int i = selectedPosition; i != windows[selectedWindow].rear; 
             i = (i + 1) % MAX_QUEUE) {
            int next = (i + 1) % MAX_QUEUE;
            windows[selectedWindow].customers[i] = windows[selectedWindow].customers[next];
        }
        windows[selectedWindow].rear = (windows[selectedWindow].rear - 1 + MAX_QUEUE) % MAX_QUEUE;

        printf("窗口 %d 正在服务顾客 %d (存款: %d, 优先级: %d)\n", 
               selectedWindow + 1, c.id, c.deposit, c.priority);
    } else {
        printf("当前没有新顾客等待服务\n");
    }
}

int main() {
    Queue windows[MAX_WINDOWS]; // 定义窗口队列数组
    for (int i = 0; i < MAX_WINDOWS; i++) {
        initQueue(&windows[i]);
    }

    // 输入初始顾客人数（初始顾客标记为非新顾客）
    for (int i = 0; i < MAX_WINDOWS; i++) {
        int initialCount;
        printf("输入窗口 %d 的初始顾客人数: ", i + 1);
        scanf("%d", &initialCount);

        for (int j = 0; j < initialCount; j++) {
            Customer c;
            c.id = -1; // 初始顾客不需要具体ID
            c.deposit = 0; // 初始顾客存款默认为0
            c.priority = 0; // 普通客户优先级最低
            c.isNew = 0; // 初始顾客
            enqueue(&windows[i], c);
        }
    }

    int id = 1; // 新顾客ID递增
    char command[10];

    while (1) {
        printf("输入 'A' 添加顾客, 'S' 服务顾客, 'Q' 退出: ");
        scanf("%s", command);

        if (strcmp(command, "A") == 0) { // 添加新顾客
            Customer c;
            c.id = id++;
            printf("输入存款金额: ");
            scanf("%d", &c.deposit);
            c.priority = getPriority(c.deposit);
            c.isNew = 1; // 新顾客

            int windowIndex = findShortestQueue(windows);
            enqueue(&windows[windowIndex], c);
            printf("顾客 %d (存款: %d, 优先级: %d) 已加入窗口 %d 队列\n", 
                   c.id, c.deposit, c.priority, windowIndex + 1);
        } else if (strcmp(command, "S") == 0) { // 服务顾客
            serveCustomer(windows);
        } else if (strcmp(command, "Q") == 0) { // 退出程序
            printf("程序结束\n");
            break;
        } else {
            printf("无效命令\n");
        }
    }

    return 0;
}
