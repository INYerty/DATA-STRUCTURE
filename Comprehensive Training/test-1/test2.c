#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100 // 定义最大客户数量为10，可以根据需求调整
#define MAX_WINDOWS 3     // 定义窗口数量为3

// 定义结构体，包含客户信息
typedef struct
{
    char name[50];         // 客户姓名
    char card_number[5];   // 4位银行卡号 + 1位结束符
    double deposit_amount; // 存款金额
    int priority;          // 客户优先级（0: 普通客户, 1: I级, 2: II级, 3: III级）
    int service_time;      // 服务时间（单位分钟）
    int served;            // 客户是否已被服务的标记（0: 未服务, 1: 已服务）
    int window_index;      // 客户被分配的窗口索引
} Customer;

// 声明客户数组、统计变量及窗口服务人数
Customer customers[MAX_CUSTOMERS]; // 存储客户信息的数组
int customer_count = 0;            // 当前客户数
int served_customers = 0;          // 已服务客户数
int vip_customers = 0;             // VIP客户数
int total_waiting_time = 0;        // 总逗留时间

// 窗口服务人数，窗口A、B、C的客户数量
int window_count[MAX_WINDOWS] = {0, 0, 0}; // 初始化每个窗口的客户数为0

// 函数声明
void add_customer();             // 添加客户
void serve_customers();          // 服务客户
void print_summary();            // 打印服务统计信息
int get_priority(double amount); // 获取客户优先级
int find_min_window();           // 查找服务人数最少的窗口
void sort_customers();           // 对客户按存款金额进行排序

// 主函数
int main()
{
    int choice;

    // 初始化窗口服务人数
    printf("请输入每个窗口初始服务人数 (A B C): ");
    scanf("%d %d %d", &window_count[0], &window_count[1], &window_count[2]); // 从键盘输入各窗口的初始客户人数

    // 主菜单循环，提供给用户选择不同功能
    while (1)
    {
        printf("\n多窗口银行业务模拟系统\n");
        printf("1. 添加客户\n");
        printf("2. 服务客户\n");
        printf("3. 打印统计信息\n");
        printf("4. 退出系统\n");
        printf("请选择功能: ");
        scanf("%d", &choice); // 获取用户输入的选择

        // 根据用户选择调用对应的功能
        switch (choice)
        {
        case 1:
            add_customer(); // 添加客户
            break;
        case 2:
            serve_customers(); // 服务客户
            break;
        case 3:
            print_summary(); // 打印统计信息
            break;
        case 4:
            exit(0); // 退出系统
        default:
            printf("无效选择，请重试。\n"); // 用户输入无效选择时提示
        }
    }

    return 0;
}

// 添加客户函数
void add_customer()
{
    // 如果当前客户数已达到最大值，则无法添加新客户
    if (customer_count >= MAX_CUSTOMERS)
    {
        printf("客户数量已达到上限！\n");
        return;
    }

    // 获取当前要添加的客户位置
    Customer *c = &customers[customer_count];

    // 输入客户信息
    printf("输入客户姓名: ");
    scanf("%s", c->name);
    printf("输入银行卡号 (4位): ");
    scanf("%s", c->card_number);
    printf("输入存款金额: ");
    scanf("%lf", &c->deposit_amount);

    // 根据存款金额计算客户优先级
    c->priority = get_priority(c->deposit_amount);
    c->served = 0; // 初始化为未服务状态

    // 为客户分配服务窗口
    c->window_index = find_min_window();
    window_count[c->window_index]++; // 增加该窗口的客户数

    customer_count++; // 客户总数加1

    // 添加客户后进行排序
    sort_customers();
}

// 根据客户存款金额获取其优先级
int get_priority(double amount)
{
    if (amount < 200000)
        return 0; // 存款小于20万为普通客户
    if (amount <= 500000)
        return 1; // 存款在20万到50万之间为I级客户
    if (amount <= 1000000)
        return 2; // 存款在50万到100万之间为II级客户
    if (amount > 1000000)
        return 3; // 存款大于100万为III级客户
}

// 查找服务人数最少的窗口
int find_min_window()
{
    int min_index = 0; // 假设窗口0的服务人数最少
    for (int i = 1; i < MAX_WINDOWS; i++)
    {
        if (window_count[i] < window_count[min_index])
        {
            min_index = i; // 更新窗口索引为当前服务人数最少的窗口
        }
    }
    return min_index; // 返回服务人数最少的窗口索引
}

// 对客户按存款金额进行排序（使用冒泡排序）
void sort_customers()
{
    for (int i = 0; i < customer_count - 1; i++)
    {
        for (int j = 0; j < customer_count - i - 1; j++)
        {
            if (customers[j].deposit_amount < customers[j + 1].deposit_amount)
            {
                // 交换存款金额较小的客户与存款金额较大的客户
                Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
} // 结束冒泡排序

// 服务客户函数
void serve_customers()
{
    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].served == 0)
        { // 仅服务未被服务过的客户
            // 随机生成服务时间（1到15分钟之间）
            customers[i].service_time = rand() % 15 + 1;
            total_waiting_time += customers[i].service_time; // 累加总等待时间
            customers[i].served = 1;                         // 标记该客户已服务

            // 统计服务过的客户数量
            served_customers++;

            // 输出服务信息，根据优先级输出不同的信息
            if (customers[i].priority > 0)
            {
                vip_customers++; // 如果是VIP客户，VIP客户数加1
                printf("服务VIP客户: 姓名: %s, 银行卡号: %s, 存款: %.2f, 服务时间: %d分钟, 窗口: %d, VIP等级: %d\n",
                       customers[i].name, customers[i].card_number, customers[i].deposit_amount, customers[i].service_time, customers[i].window_index + 1, customers[i].priority);
            }
            else
            {
                // 普通客户服务信息
                printf("服务普通客户: 姓名: %s, 银行卡号: %s, 存款: %.2f, 服务时间: %d分钟, 窗口: %d\n",
                       customers[i].name, customers[i].card_number, customers[i].deposit_amount, customers[i].service_time, customers[i].window_index + 1);
            }

            // 服务完成后，减少该窗口的客户数量
            window_count[customers[i].window_index]--;
        }
    }
}

// 打印统计信息
void print_summary()
{
    printf("\n服务统计:\n");
    printf("总客户数: %d\n", served_customers);
    printf("VIP客户数: %d\n", vip_customers);
    if (served_customers > 0)
    {
        printf("平均逗留时间: %.2f分钟\n", (double)total_waiting_time / served_customers); // 输出平均逗留时间
    }
    else
    {
        printf("没有客户接受服务。\n"); // 如果没有客户接受服务，则输出提示
    }
}
