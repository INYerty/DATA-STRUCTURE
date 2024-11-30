#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  // 定义最大顶点数量

// 定义邻接矩阵结构
typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];  // 矩阵表示边的存在
    int numVertices;  // 顶点数量
} AdjacencyMatrix;

// 定义邻接表节点结构
typedef struct AdjNode {
    int vertex;  // 相邻顶点
    struct AdjNode* next;  // 指向下一个相邻顶点的指针
} AdjNode;

// 定义邻接表结构
typedef struct {
    AdjNode* list[MAX_VERTICES];  // 顶点数组，每个顶点有一个链表表示其相邻顶点
    int numVertices;  // 顶点数量
} AdjacencyList;

// 创建邻接矩阵
AdjacencyMatrix* createMatrix(int numVertices) {
    AdjacencyMatrix* matrix = (AdjacencyMatrix*)malloc(sizeof(AdjacencyMatrix));  // 为邻接矩阵分配内存
    matrix->numVertices = numVertices;  // 设置顶点数量
    for (int i = 0; i < numVertices; i++) {  // 初始化矩阵所有元素为0
        for (int j = 0; j < numVertices; j++) {
            matrix->matrix[i][j] = 0;
        }
    }
    return matrix;  // 返回初始化后的矩阵
}

// 创建邻接表
AdjacencyList* createList(int numVertices) {
    AdjacencyList* list = (AdjacencyList*)malloc(sizeof(AdjacencyList));  // 为邻接表分配内存
    list->numVertices = numVertices;  // 设置顶点数量
    for (int i = 0; i < numVertices; i++) {  // 初始化每个顶点的邻接链表为NULL
        list->list[i] = NULL;
    }
    return list;  // 返回初始化后的邻接表
}

// 添加边到邻接矩阵
void addEdgeMatrix(AdjacencyMatrix* matrix, int u, int v) {
    matrix->matrix[u][v] = 1;  // 设置顶点u和v之间的边
    matrix->matrix[v][u] = 1;  // 无向图，设置顶点v和u之间的边
}

// 添加边到邻接表
void addEdgeList(AdjacencyList* list, int u, int v) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));  // 创建新节点
    newNode->vertex = v;  // 设置节点的顶点为v
    newNode->next = list->list[u];  // 将新节点插入链表头部
    list->list[u] = newNode;  // 将新节点设为顶点u的第一个相邻节点

    newNode = (AdjNode*)malloc(sizeof(AdjNode));  // 为无向图创建对称边
    newNode->vertex = u;  // 设置节点的顶点为u
    newNode->next = list->list[v];  // 将新节点插入链表头部
    list->list[v] = newNode;  // 将新节点设为顶点v的第一个相邻节点
}

// 邻接矩阵转换为邻接表
AdjacencyList* convertMatrixToList(AdjacencyMatrix* matrix) {
    AdjacencyList* list = createList(matrix->numVertices);  // 创建邻接表
    for (int i = 0; i < matrix->numVertices; i++) {  // 遍历每个顶点
        for (int j = matrix->numVertices - 1; j >= 0; j--) {  // 遍历每个相邻顶点
            if (matrix->matrix[i][j] != 0) {  // 如果顶点i和j之间有边
                AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));  // 创建新节点
                newNode->vertex = j;  // 设置节点的顶点为j
                newNode->next = list->list[i];  // 将新节点插入链表头部
                list->list[i] = newNode;  // 更新链表头部
            }
        }
    }
    return list;  // 返回创建的邻接表
}

// 邻接表转换为邻接矩阵
AdjacencyMatrix* convertListToMatrix(AdjacencyList* list) {
    AdjacencyMatrix* matrix = createMatrix(list->numVertices);  // 创建邻接矩阵
    for (int i = 0; i < list->numVertices; i++) {  // 遍历每个顶点
        AdjNode* node = list->list[i];  // 获取顶点i的邻接链表
        while (node != NULL) {  // 遍历链表中的每个节点
            matrix->matrix[i][node->vertex] = 1;  // 设置顶点i和相邻顶点之间的边
            node = node->next;  // 移动到下一个节点
        }
    }
    return matrix;  // 返回创建的邻接矩阵
}

// 广度优先搜索（BFS）
void BFS(AdjacencyList* list, int startVertex) {
    int visited[MAX_VERTICES] = {0};  // 创建访问数组并初始化为0
    int queue[MAX_VERTICES];  // 创建队列
    int front = 0, rear = 0;  // 初始化队列头尾指针

    visited[startVertex] = 1;  // 标记起始顶点已访问
    queue[rear++] = startVertex;  // 将起始顶点入队

    while (front != rear) {  // 当队列不为空时
        int currentVertex = queue[front++];  // 取出队列头部顶点
        printf("%d ", currentVertex);  // 打印当前顶点

        AdjNode* temp = list->list[currentVertex];  // 获取当前顶点的邻接链表
        while (temp) {  // 遍历邻接链表中的每个节点
            int adjVertex = temp->vertex;  // 获取相邻顶点
            if (!visited[adjVertex]) {  // 如果相邻顶点未访问
                visited[adjVertex] = 1;  // 标记相邻顶点已访问
                queue[rear++] = adjVertex;  // 将相邻顶点入队
            }
            temp = temp->next;  // 移动到下一个节点
        }
    }
}

// 深度优先搜索（DFS）
void DFSUtil(AdjacencyMatrix* matrix, int vertex, int visited[]) {
    visited[vertex] = 1;  // 标记当前顶点已访问
    printf("%d ", vertex);  // 打印当前顶点

    for (int i = 0; i < matrix->numVertices; i++) {  // 遍历所有顶点
        if (matrix->matrix[vertex][i] && !visited[i]) {  // 如果有边且顶点未访问
            DFSUtil(matrix, i, visited);  // 递归访问
        }
    }
}

void DFS(AdjacencyMatrix* matrix, int startVertex) {
    int visited[MAX_VERTICES] = {0};  // 创建访问数组并初始化为0
    DFSUtil(matrix, startVertex, visited);  // 从起始顶点开始DFS
}

// 主菜单
void menu() {
    printf("1. 邻接矩阵转换为邻接表\n");
    printf("2. 邻接表转换为邻接矩阵\n");
    printf("3. 广度优先搜索\n");
    printf("4. 深度优先搜索\n");
    printf("请选择一个操作: ");
}

int main() {
    AdjacencyMatrix* matrix;
    AdjacencyList* list;
    int choice, numVertices, u, v, startVertex;

    printf("请输入顶点数量: ");
    scanf("%d", &numVertices);

    matrix = createMatrix(numVertices);  // 创建邻接矩阵
    list = createList(numVertices);  // 创建邻接表

    printf("请输入边 (格式: u v, 输入-1 -1结束):\n");
    while (1) {
        scanf("%d %d", &u, &v);
        if (u == -1 && v == -1) break;  // 输入-1 -1结束
        addEdgeMatrix(matrix, u, v);  // 添加边到邻接矩阵
        addEdgeList(list, u, v);  // 添加边到邻接表
    }

    while (1) {
        menu();  // 显示菜单
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                list = convertMatrixToList(matrix);  // 邻接矩阵转换为邻接表
                printf("邻接矩阵转换为邻接表成功。\n");
                break;
            case 2:
                matrix = convertListToMatrix(list);  // 邻接表转换为邻接矩
                                printf("邻接表转换为邻接矩阵成功。\n");
                break;
            case 3:
                printf("请输入起始顶点: ");
                scanf("%d", &startVertex);
                printf("广度优先搜索结果: ");
                BFS(list, startVertex);  // 进行广度优先搜索
                printf("\n");
                break;
            case 4:
                printf("请输入起始顶点: ");
                scanf("%d", &startVertex);
                printf("深度优先搜索结果: ");
                DFS(matrix, startVertex);  // 进行深度优先搜索
                printf("\n");
                break;
            default:
                printf("无效选择。\n");  // 处理无效的选择
        }
    }

    return 0;  // 返回0表示程序成功执行
}//666
