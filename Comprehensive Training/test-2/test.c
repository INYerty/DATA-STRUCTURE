#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTUDENTS 100
#define MAXSUBJECTS 10

typedef struct
{
    int id;                    // 学号
    char name[50];             // 姓名
    int semester;              // 学期
    float scores[MAXSUBJECTS]; // 各科成绩
    float totalScore;          // 总成绩
} Student;

Student student[MAXSTUDENTS];
int n, m; // 学生数量和科目数量
float fail = 60.0;

// 计算每个学生的总成绩
void calculateTotal()
{
    for (int i = 0; i < n; i++)
    {
        student[i].totalScore = 0;
        for (int j = 0; j < m; j++)
        {
            student[i].totalScore += student[i].scores[j]; // 将第 j 门科目的成绩加到总成绩中
        }
    }
}

// 打印每学期排名
void printRank()
{
    printf("学期排名\n");
    for (int sem = 1; sem <= 4; sem++)
    { // 假设学期为4
        printf("\n%d 学期:\n", sem);
        Student temp[MAXSTUDENTS];
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (student[i].semester == sem)
            {
                temp[count++] = student[i];
            }
        }

        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (temp[i].totalScore < temp[j].totalScore)
                {
                    Student t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }
        }

        for (int i = 0; i < count; i++)
        {
            printf("%d. 学号: %d, 姓名: %s, 总分: %.2f\n",
                   i + 1, temp[i].id, temp[i].name, temp[i].totalScore);
        }
    }
}

// 打印每学期不及格人数
void printFail()
{
    printf("\n学期不及格人数\n");
    for (int sem = 1; sem <= 4; sem++)
    {
        printf("\n学期 %d:\n", sem);
        int failcount[MAXSUBJECTS] = {0};

        for (int i = 0; i < n; i++)
        {
            if (student[i].semester == sem)
            {
                for (int j = 0; j < m; j++)
                {
                    if (student[i].scores[j] < fail)
                    {
                        failcount[j]++;
                    }
                }
            }
        }

        for (int i = 0; i < m; i++)
        {
            printf("科目 %d 不及格人数: %d\n", i + 1, failcount[i]);
        }
    }
}

// 打印每个学生的不及格情况
void printFailStudents()
{
    printf("\n学生不及格情况\n");
    for (int i = 0; i < n; i++)
    {
        int failcount = 0;
        printf("\n学号: %d, 姓名: %s\n", student[i].id, student[i].name);

        for (int j = 0; j < m; j++)
        {
            if (student[i].scores[j] < fail)
            {
                failcount++;
                printf("  科目 %d 成绩: %.2f (不及格)\n", j + 1, student[i].scores[j]);
            }
        }

        if (failcount == 0)
        {
            printf("  无不及格成绩\n");
        }
    }
}

// 打印达到预警标准的学生名单
void warning(int warningScore)
{
    printf("\n达到预警标准的学生\n");
    for (int i = 0; i < n; i++)
    {
        int failcount = 0;

        for (int j = 0; j < m; j++)
        {
            if (student[i].scores[j] < fail)
            {
                failcount++;
            }
        }

        if (failcount >= warningScore)
        {
            printf("学号: %d, 姓名: %s, 不及格科目数: %d\n",student[i].id, student[i].name, failcount);
        }
    }
}

// 打印每个学生的总成绩
void printTotalScores()
{
    printf("\n学生总成绩\n");
    for (int i = 0; i < n; i++)
    {
        printf("学号: %d, 姓名: %s, 学期: %d, 总分: %.2f\n",
               student[i].id, student[i].name, student[i].semester, student[i].totalScore);
    }
}

// 菜单显示和处理用户选择
void menu()
{
    int choice, warningScore;

    while (1)
    {
        printf("\n--- 学生成绩管理菜单 ---\n");
        printf("1. 每学期排名\n");
        printf("2. 每学期不及格人数\n");
        printf("3. 学生不及格情况统计\n");
        printf("4. 设置预警标准并打印名单\n");
        printf("5. 打印总成绩\n");
        printf("0. 退出\n");
        printf("请输入选择: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printRank();
            break;
        case 2:
            printFail();
            break;
        case 3:
            printFailStudents();
            break;
        case 4:
            printf("请输入不及格课程数预警值: ");
            scanf("%d", &warningScore);
            warning(warningScore);
            break;
        case 5:
            printTotalScores();
            break;
        case 0:
            return;
        default:
            printf("无效选择！请重新输入。\n");
        }
    }
}

int main()
{
    printf("请输入学生人数和科目数量: ");
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        printf("\n输入第 %d 个学生的信息 (学号 姓名 学期号 各科成绩):\n", i + 1);
        scanf("%d %s %d", &student[i].id, student[i].name, &student[i].semester);

        for (int j = 0; j < m; j++)
        {
            scanf("%f", &student[i].scores[j]);
        }
    }

    calculateTotal();
    menu();
    return 0;
}