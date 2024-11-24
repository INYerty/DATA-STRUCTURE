#include <stdio.h>   // 包含输入输出函数头文件
#include <stdlib.h>  // 包含动态内存分配函数头文件
#include <stdbool.h> // 包含布尔类型支持头文件

#define MAX 100 // 定义图的最大顶点数

// 邻接矩阵结构定义
typedef struct {
    int vertices[MAX];   // 顶点集合（可以进一步扩展为存储顶点名称）
    int edges[MAX][MAX]; // 邻接矩阵，用于存储边的信息
    int vertex_count;    // 顶点数
    int edge_count;      // 边数
} AdjMatrix;

// 邻接表节点结构定义
typedef struct AdjListNode {
    int vertex;                  // 该节点代表的顶点
    struct AdjListNode* next;    // 指向下一个邻接节点
} AdjListNode;

// 邻接表头定义
typedef struct {
    AdjListNode* head; // 每个顶点的邻接链表的头指针
} AdjList;

// 邻接表结构定义
typedef struct {
    AdjList array[MAX]; // 邻接表数组，大小为MAX
    int vertex_count;   // 顶点数
    int edge_count;     // 边数
} GraphAdjList;

// 全局访问标记数组，用于DFS
int visited[MAX];

// 打印菜单函数
void menu() {
    // 提供用户选择的功能菜单
    printf("\n--- 图的实验主菜单 ---\n");
    printf("1. 创建图\n");
    printf("2. 邻接矩阵转邻接表\n");
    printf("3. 邻接表转邻接矩阵\n");
    printf("4. 广度优先搜索（BFS）\n");
    printf("5. 深度优先搜索（DFS）\n");
    printf("6. 退出\n");
    printf("请输入你的选择（1-6）：");
}

// 创建邻接矩阵函数
void createAdjMatrix(AdjMatrix* graph) {
    printf("请输入图的顶点数和边数（空格分隔）：");
    scanf("%d %d", &graph->vertex_count, &graph->edge_count);

    // 初始化邻接矩阵，所有值为0
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = 0; j < graph->vertex_count; j++) {
            graph->edges[i][j] = 0;
        }
    }

    // 输入每条边的起点和终点，并更新邻接矩阵
    printf("请输入每条边（格式：起点 终点）：\n");
    for (int i = 0; i < graph->edge_count; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph->edges[u][v] = 1; // 无向图，所以两个方向都要设置
        graph->edges[v][u] = 1;
    }
    printf("邻接矩阵创建完成！\n");
}

// 邻接矩阵转邻接表函数
void adjMatrixToAdjList(AdjMatrix* matrix, GraphAdjList* list) {
    list->vertex_count = matrix->vertex_count;
    list->edge_count = matrix->edge_count;

    // 初始化邻接表
    for (int i = 0; i < matrix->vertex_count; i++) {
        list->array[i].head = NULL; // 初始化头指针为空
        for (int j = 0; j < matrix->vertex_count; j++) {
            if (matrix->edges[i][j] == 1) {
                // 如果邻接矩阵中存在边，则创建邻接表节点
                AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
                newNode->vertex = j;       // 设置邻接节点的顶点编号
                newNode->next = list->array[i].head; // 插入到链表头部
                list->array[i].head = newNode;
            }
        }
    }
    printf("邻接表创建完成！\n");
}

// 深度优先搜索（DFS）函数，基于邻接矩阵
void DFS(AdjMatrix* graph, int v) {
    visited[v] = 1; // 标记当前顶点已访问
    printf("%d ", v); // 输出访问的顶点

    // 遍历邻接矩阵中的邻接顶点
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->edges[v][i] == 1 && !visited[i]) {
            // 如果存在未访问的邻接顶点，递归调用DFS
            DFS(graph, i);
        }
    }
}

// 广度优先搜索（BFS）函数，基于邻接表
void BFS(GraphAdjList* list, int start) {
    bool visited[MAX] = { false }; // 初始化访问标记数组
    int queue[MAX], front = 0, rear = 0; // 初始化队列

    // 标记起始顶点为已访问并加入队列
    printf("%d ", start);
    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++]; // 取出队首顶点
        AdjListNode* temp = list->array[current].head;
        while (temp) {
            int adjVertex = temp->vertex; // 获取邻接顶点
            if (!visited[adjVertex]) {
                // 如果邻接顶点未被访问
                printf("%d ", adjVertex);
                visited[adjVertex] = true;
                queue[rear++] = adjVertex; // 入队
            }
            temp = temp->next; // 访问下一个邻接节点
        }
    }
}

// 主函数
int main() {
    AdjMatrix matrix;         // 定义邻接矩阵结构变量
    GraphAdjList list;        // 定义邻接表结构变量
    int choice;               // 用户菜单选择变量

    while (1) {
        menu();               // 显示菜单
        scanf("%d", &choice); // 用户输入选择
        switch (choice) {
            case 1:
                createAdjMatrix(&matrix); // 创建邻接矩阵
                break;
            case 2:
                adjMatrixToAdjList(&matrix, &list); // 矩阵转表
                break;
            case 3:
                printf("功能未实现\n"); // 选做功能
                break;
            case 4:
                printf("请输入起始顶点：");
                int startBFS;
                scanf("%d", &startBFS);
                BFS(&list, startBFS); // 执行广度优先搜索
                break;
            case 5:
                printf("请输入起始顶点：");
                int startDFS;
                scanf("%d", &startDFS);
                for (int i = 0; i < matrix.vertex_count; i++) visited[i] = 0; // 重置访问数组
                DFS(&matrix, startDFS); // 执行深度优先搜索
                break;
            case 6:
                printf("退出程序。\n"); // 退出程序
                exit(0);
            default:
                printf("无效选择，请重新输入！\n"); // 无效选择提示
        }
    }
    return 0;
}
