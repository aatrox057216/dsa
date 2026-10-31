/**
 * @file    demo.c
 * @brief   定长数组循环队列功能演示：入队、判满、出队、循环复用、清空。
 * @author  aatroxfans
 * @date    2026-10-30
 */

#include "CircularQueue.h"
#include <stdio.h>

int main(void)
{
    CircularQueue Q;
    int e;

    Ci_InitQueue(&Q);
    printf("初始化后，长度 = %d，是否为空 = %s\n", Ci_QueueLength(&Q), Ci_QueueEmpty(&Q) ? "是" : "否");

    /* 入队 1~5 */
    for (int i = 1; i <= 5; ++i)
    {
        Ci_EnQueue(&Q, i);
    }
    printf("入队 1~5 后遍历：");
    Ci_QueueTraverse(&Q);
    printf("长度 = %d\n", Ci_QueueLength(&Q));

    /* 取队头、出队两个 */
    Ci_GetHead(&Q, &e);
    printf("队头元素 = %d\n", e);
    Ci_DeQueue(&Q, &e);
    printf("出队 %d\n", e);
    Ci_DeQueue(&Q, &e);
    printf("出队 %d\n", e);
    printf("出队两个后遍历：");
    Ci_QueueTraverse(&Q);

    /* 演示循环复用：front 已后移，再入队使 rear 绕回 */
    for (int i = 6; i <= 9; ++i)
    {
        Ci_EnQueue(&Q, i);
    }
    printf("再入队 6~9 后遍历：");
    Ci_QueueTraverse(&Q);
    printf("长度 = %d，front = %d，rear = %d\n", Ci_QueueLength(&Q), Q.front, Q.rear);

    /* 填满测试：最多存 MAXSIZE-1 个 */
    while (!Ci_QueueFull(&Q))
    {
        Ci_EnQueue(&Q, 0);
    }
    printf("队列已满，长度 = %d（最大可存 %d）\n", Ci_QueueLength(&Q), MAXSIZE - 1);
    if (!Ci_EnQueue(&Q, 999))
    {
        printf("满队入队被正确拒绝\n");
    }

    /* 清空 */
    Ci_ClearQueue(&Q);
    printf("清空后，长度 = %d，是否为空 = %s\n", Ci_QueueLength(&Q), Ci_QueueEmpty(&Q) ? "是" : "否");

    return 0;
}
