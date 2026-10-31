/**
 * @file    demo.c
 * @brief   循环队列功能演示：入队、判满、出队、循环复用、清空、销毁。
 * @author  aatroxfans
 * @date    2026-10-30
 */

#include "SqQueue.h"
#include <stdio.h>

int main(void)
{
    SqQueue Q;
    QElemType e;

    if (!Sq_InitQueue(&Q))
    {
        fprintf(stderr, "初始化失败\n");
        return 1;
    }
    printf("初始化后，长度 = %d，是否为空 = %s\n", Sq_QueueLength(&Q), Sq_QueueEmpty(&Q) ? "是" : "否");

    /* 入队 1~5 */
    for (int i = 1; i <= 5; ++i)
    {
        Sq_EnQueue(&Q, i);
    }
    printf("入队 1~5 后遍历：");
    Sq_QueueTraverse(&Q);
    printf("长度 = %d\n", Sq_QueueLength(&Q));

    /* 取队头、出队两个 */
    Sq_GetHead(&Q, &e);
    printf("队头元素 = %d\n", e);
    Sq_DeQueue(&Q, &e);
    printf("出队 %d\n", e);
    Sq_DeQueue(&Q, &e);
    printf("出队 %d\n", e);
    printf("出队两个后遍历：");
    Sq_QueueTraverse(&Q);

    /* 演示循环复用：再入队若干，front 已后移 */
    for (int i = 6; i <= 9; ++i)
    {
        Sq_EnQueue(&Q, i);
    }
    printf("再入队 6~9 后遍历：");
    Sq_QueueTraverse(&Q);
    printf("长度 = %d\n", Sq_QueueLength(&Q));

    /* 填满测试：最多存 MAXQSIZE-1 个 */
    while (!Sq_QueueFull(&Q))
    {
        Sq_EnQueue(&Q, 0);
    }
    printf("队列已满，长度 = %d（最大可存 %d）\n", Sq_QueueLength(&Q), MAXQSIZE - 1);
    if (!Sq_EnQueue(&Q, 999))
    {
        printf("满队入队被正确拒绝\n");
    }

    /* 清空 */
    Sq_ClearQueue(&Q);
    printf("清空后，长度 = %d，是否为空 = %s\n", Sq_QueueLength(&Q), Sq_QueueEmpty(&Q) ? "是" : "否");

    Sq_DestroyQueue(&Q);
    printf("销毁完成\n");
    return 0;
}
