#include <stdio.h>

struct Student {
    char num[9];
    int deAchievement;
    int caiAchievement;
    int totalAchievement;
};

void sortArray(int index, struct Student studentArray[]);

void printResult(int index, struct Student studentArray[]);

int main() {
    //总的学生
    int totalNumber;
    //低分 高分
    int low, high;
    scanf("%d%d%d", &totalNumber, &low, &high);
    if (totalNumber > 100000 || low < 60 || low > high || high > 100) {
        return 0;
    }
    struct Student studentArray[totalNumber];
    struct Student studentArrayFirst[totalNumber];
    struct Student studentArraySecond[totalNumber];
    struct Student studentArrayThird[totalNumber];
    struct Student studentArrayFourth[totalNumber];
    int indexFirst = 0;
    int indexSecond = 0;
    int indexThird = 0;
    int indexFourth = 0;
    for (int i = 0; i < totalNumber; i++) {
        scanf("%s %d %d", &studentArray[i].num, &studentArray[i].deAchievement,
              &studentArray[i].caiAchievement);
        studentArray[i].totalAchievement =
                studentArray[i].deAchievement + studentArray[i].caiAchievement;
        if (studentArray[i].deAchievement >= high && studentArray[i].caiAchievement >= high) {
            studentArrayFirst[indexFirst++] = studentArray[i];
        } else if (studentArray[i].deAchievement >= high && studentArray[i].caiAchievement >= low) {
            studentArraySecond[indexSecond++] = studentArray[i];
        } else if (studentArray[i].deAchievement < high && studentArray[i].caiAchievement < high
                   && studentArray[i].deAchievement >= low && studentArray[i].caiAchievement >= low
                   && studentArray[i].deAchievement >= studentArray[i].caiAchievement) {
            studentArrayThird[indexThird++] = studentArray[i];
        } else if (studentArray[i].deAchievement >= low && studentArray[i].caiAchievement >= low) {
            studentArrayFourth[indexFourth++] = studentArray[i];
        }
    }
    printf("%d\n", indexFirst + indexSecond + indexThird + indexFourth);
    //一个简单的冒泡排序
    if (indexFirst > 0) {
        sortArray(indexFirst, studentArrayFirst);
    }
    if (indexSecond > 0) {
        sortArray(indexSecond, studentArraySecond);
    }
    if (indexThird > 0) {
        sortArray(indexThird, studentArrayThird);
    }
    if (indexFourth > 0) {
        sortArray(indexFourth, studentArrayFourth);
    }
    return 0;
}

void sortArray(int index, struct Student studentArray[]) {
    int len = index - 1;
    for (int i = 0; i < index; i++) {
        //设置一个标志位
        int flag = 1;
        int tempPostion = 0;  // 记录最后一次交换的位置
        //先给数组排序从大到小
        //然后如果不是1的 则为关键字
        //这时候需要输出
        for (int j = 0; j < len; j++) {
            if (studentArray[j].totalAchievement < studentArray[j + 1].totalAchievement) {
                struct Student temp = studentArray[j];
                studentArray[j] = studentArray[j + 1];
                studentArray[j + 1] = temp;
                //发生交换，标志位置0
                flag = 0;
                tempPostion = j;  //记录交换的位置
            } else if (studentArray[j].totalAchievement ==
                       studentArray[j + 1].totalAchievement) {
                //    当某类考生中有多人总分相同时，按其德分降序排列；若德分也并列，则按准考证号的升序输出。
                if (studentArray[j].deAchievement < studentArray[j + 1].deAchievement) {
                    struct Student temp = studentArray[j];
                    studentArray[j] = studentArray[j + 1];
                    studentArray[j + 1] = temp;
                    //发生交换，标志位置0
                    flag = 0;
                    tempPostion = j;  //记录交换的位置
                } else if (studentArray[j].deAchievement ==
                           studentArray[j + 1].deAchievement) {
                    //这里对学号做比较
                    for (int k = 0; k < 8; ++k) {
                        if (studentArray[j].num[k] < studentArray[j + 1].num[k]) {
                            struct Student temp = studentArray[j];
                            studentArray[j] = studentArray[j + 1];
                            studentArray[j + 1] = temp;
                            //发生交换，标志位置0
                            flag = 0;
                            tempPostion = j;  //记录交换的位置
                        }
                    }
                }
            }
        }
        len = tempPostion;
        if (flag) {
            //如果没有交换过元素，则已经有序
            break;
        }
    }
    printResult(index, studentArray);
}

void printResult(int index, struct Student studentArray[]) {
    for (int j = 0; j < index; j++) {
        printf("%s %d %d\n", studentArray[j].num, studentArray[j].deAchievement,
               studentArray[j].caiAchievement);
    }
}

