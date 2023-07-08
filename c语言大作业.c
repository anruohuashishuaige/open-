#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 100 // 最大学生人数
#define M 7 // 课程数量

// 定义学生结构体
typedef struct {
    int id; // 学号
    char name[20]; // 姓名
    char gender[10]; // 性别
    char address[100]; // 家庭住址
    char phone[20]; // 联系电话
    double scores[M]; // 七门课程单科成绩
    double exam_avg; // 考试平均成绩
    double test; // 平时测试
    double teacher_score; // 任课教师评分
    double total_score; // 综合测评总分
    int rank; // 综合测评名次
} Student;

// 定义班级结构体
typedef struct {
    Student students[N]; // 学生数组
    int size; // 学生数量
} Class;

// 函数声明
void input_scores(Class *class); // 录入学生成绩
void find_student(Class *class); // 查找学生信息
void add_student(Class *class); // 增加学生信息
void delete_student(Class *class); // 删除学生信息
void update_student(Class *class); // 修改学生信息
void analyze_scores(Class *class); // 统计分析成绩
void output_students(Class *class); // 输出所有学生信息

int main() {
    Class class = { .size = 0 }; // 初始化班级

    int op;
    while (1) {
        printf("学生成绩管理系统\n");
        printf("1. 录入学生成绩\n");
        printf("2. 查找学生信息\n");
        printf("3. 增加学生信息\n");
        printf("4. 删除学生信息\n");
        printf("5. 修改学生信息\n");
        printf("6. 统计分析成绩\n");
        printf("7. 输出所有学生信息\n");
        printf("0. 退出系统\n");
        printf("请选择操作：");
        scanf("%d", &op);

        switch (op) {
            case 1:
                input_scores(&class);
                break;
            case 2:
                find_student(&class);
                break;
            case 3:
                add_student(&class);
                break;
            case 4:
                delete_student(&class);
                break;
            case 5:
                update_student(&class);
                break;
            case 6:
                analyze_scores(&class);
                break;
            case 7:
                output_students(&class);
                break;
            case 0:
                exit(0);
            default:
                printf("无效操作！\n");
        }
    }

    return 0;
}

// 录入学生成绩函数定义
void input_scores(Class *class) {
    int id, i, j;
    double sum;

    printf("请输入学号：");
    scanf("%d", &id);

    for (i = 0; i < class->size; i++) {
        if (class->students[i].id == id) {
            sum = 0;
            for (j = 0; j < M; j++) {
                printf("请输入第 %d 门课程成绩：", j + 1);
                scanf("%lf", &class->students[i].scores[j]);
                sum += class->students[i].scores[j];
            }
            class->students[i].exam_avg = sum / M;
            return;
        }
    }

    printf("未找到该学生！\n");
}

// 查找学生信息函数定义
void find_student(Class *class) {
    int id, i;

    printf("请输入学号：");
    scanf("%d", &id);

    for (i = 0; i < class->size; i++) {
        if (class->students[i].id == id) {
            printf("学号：%d\n", class->students[i].id);
            printf("姓名：%s\n", class->students[i].name);
            printf("性别：%s\n", class->students[i].gender);
            printf("家庭住址：%s\n", class->students[i].address);
            printf("联系电话：%s\n", class->students[i].phone);
            printf("考试平均成绩：%.2lf\n", class->students[i].exam_avg);
            printf("平时测试：%.2lf\n", class->students[i].test);
            printf("任课教师评分：%.2lf\n", class->students[i].teacher_score);
            printf("综合测评总分：%.2lf\n", class->students[i].total_score);
            printf("综合测评名次：%d\n", class->students[i].rank);
            return;
        }
    }

    printf("未找到该学生！\n");
}

// 增加学生信息函数定义
void add_student(Class *class) {
    Student student;
    int i, j;

    if (class->size == N) {
        printf("班级人数已满，无法添加！\n");
        return;
    }

    printf("请输入学号：");
    scanf("%d", &student.id);

    for (i = 0; i < class->size; i++) {
        if (class->students[i].id == student.id) {
            printf("该学生已存在！\n");
            return;
        }
    }

    printf("请输入姓名：");
    scanf("%s", student.name);
    printf("请输入性别：");
    scanf("%s", student.gender);
    printf("请输入家庭住址：");
    scanf("%s", student.address);
    printf("请输入联系电话：");
    scanf("%s", student.phone);

    for (i = 0; i < M; i++) {
        student.scores[i] = 0;
    }
    student.exam_avg = 0;
    student.test = 0;
    student.teacher_score = 0;
    student.total_score = 0;
    student.rank = 0;

    for (i = 0; i < class->size; i++) {
        if (student.id < class->students[i].id) {
            for (j = class->size - 1; j >= i; j--) {
                class->students[j + 1] = class->students[j];
            }
            class->students[i] = student;
            class->size++;
            return;
        }
    }

    class->students[class->size++] = student;
}

// 删除学生信息函数定义
void delete_student(Class *class) {
    int id, i, j;

    printf("请输入学号：");
    scanf("%d", &id);

    for (i = 0; i < class->size; i++) {
        if (class->students[i].id == id) {
            for (j = i; j < class->size - 1; j++) {
                class->students[j] = class->students[j + 1];
            }
            class->size--;
            printf("删除成功！\n");
            return;
        }
    }

    printf("未找到该学生！\n");
}

// 修改学生信息函数定义
void update_student(Class *class) {
    int id, i;

    printf("请输入学号：");
    scanf("%d", &id);

    for (i = 0; i < class->size; i++) {
        if (class->students[i].id == id) {
            printf("请输入新的姓名：");
            scanf("%s", class->students[i].name);
            printf("请输入新的性别：");
            scanf("%s", class->students[i].gender);
            printf("请输入新的家庭住址：");
            scanf("%s", class->students[i].address);
            printf("请输入新的联系电话：");
            scanf("%s", class->students[i].phone);
            return;
        }
    }

    printf("未找到该学生！\n");
}

void analyze_scores(Class *class) {
    int count[6] = {0}; // 各分数段人数
    double sum, avg, variance, std_dev; // 总和、平均值、方差、标准差
    double gpa; // 平均绩点
    int i, j;

    // 统计各分数段人数
    for (i = 0; i < class->size; i++) {
        if (class->students[i].exam_avg < 60) {
            count[0]++;
        } else if (class->students[i].exam_avg < 70) {
            count[1]++;
        } else if (class->students[i].exam_avg < 80) {
            count[2]++;
        } else if (class->students[i].exam_avg < 90) {
            count[3]++;
        } else if (class->students[i].exam_avg < 100) {
            count[4]++;
        } else {
            count[5]++;
        }
    }

    printf("各分数段人数统计：\n");
    printf("0~59分：%d\n", count[0]);
    printf("60~69分：%d\n", count[1]);
    printf("70~79分：%d\n", count[2]);
    printf("80~89分：%d\n", count[3]);
    printf("90~99分：%d\n", count[4]);
    printf("100分：%d\n", count[5]);

    // 计算学生考试的平均成绩
    sum = 0;
    for (i = 0; i < class->size; i++) {
        sum += class->students[i].exam_avg;
    }
    avg = sum / class->size;

    printf("学生考试平均成绩：%.2lf\n", avg);

    // 按照考试平均成绩从小到大排序
    for (i = 0; i < class->size - 1; i++) {
        for (j = i + 1; j < class->size; j++) {
            if (class->students[i].exam_avg > class->students[j].exam_avg) {
                Student temp = class->students[i];
                class->students[i] = class->students[j];
                class->students[j] = temp;
            }
        }
    }

    // 计算学生成绩的标准差
    sum = 0;
    for (i = 0; i < class->size; i++) {
        sum += pow(class->students[i].exam_avg - avg, 2);
    }
    variance = sum / class->size;
    std_dev = sqrt(variance);

    printf("学生成绩标准差：%.2lf\n", std_dev);

    // 计算学生的平均绩点
    sum = 0;
    for (i = 0; i < class->size; i++) {
        if (class->students[i].exam_avg >= 90) {
            gpa = 4.0;
        } else if (class->students[i].exam_avg >= 80) {
            gpa = 3.0;
        } else if (class->students[i].exam_avg >= 70) {
            gpa = 2.0;
        } else if (class->students[i].exam_avg >= 60) {
            gpa = 1.0;
        } else {
            gpa = 0.0;
        }
        sum += gpa;
    }
    avg = sum / class->size;

    printf("学生平均绩点：%.2lf\n", avg);

    // 计算综合测评总分及名次
    for (i = 0; i < class->size; i++) {
        class->students[i].total_score = class->students[i].exam_avg * 0.6 + class->students[i].test * 0.2 + class->students[i].teacher_score * 0.2;
    }

    for (i = 0; i < class->size; i++) {
        class->students[i].rank = 1;
        for (j = 0; j < class->size; j++) {
            if (class->students[j].total_score > class->students[i].total_score) {
                class->students[i].rank++;
            }
        }
    }
}

// 输出所有学生信息函数定义
void output_students(Class *class) {
    int i, j;

    printf("学号\t姓名\t性别\t家庭住址\t联系电话\t考试平均成绩\t平时测试\t任课教师评分\t综合测评总分\t综合测评名次\n");
    for (i = 0; i < class->size; i++) {
        printf("%d\t%s\t%s\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%d\n",
            class->students[i].id,
            class->students[i].name,
            class->students[i].gender,
            class->students[i].address,
            class->students[i].phone,
            class->students[i].exam_avg,
            class->students[i].test,
            class->students[i].teacher_score,
            class->students[i].total_score,
            class->students[i].rank
        );
    }
}