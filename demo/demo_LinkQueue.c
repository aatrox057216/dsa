/**
 * @file    demo.c
 * @brief   链队列功能演示：初始化、入队、出队、取队头、清空、销毁。
 * @author  aatroxfans
 * @date    2026-10-30
 */

#include "LinkQueue.h"
#include <stdio.h>

int main(void)
{
    LinkQueue Q;
    int e;

    if (!InitQueue(&Q))
    {
        fprintf(stderr, "初始化失败\n");
        return 1;
    }
    printf("初始化后，队列长度 = %d，是否为空 = %s\n", QueueLength(&Q), QueueEmpty(&Q) ? "是" : "否");

    /* 入队 1~5 */
    for (int i = 1; i <= 5; ++i)
    {
        EnQueue(&Q, i);
        printf("入队 %d\n", i);
    }
    printf("遍历队列：");
    QueueTraverse(&Q);
    printf("队列长度 = %d\n", QueueLength(&Q));

    /* 取队头 */
    GetHead(&Q, &e);
    printf("队头元素 = %d\n", e);

    /* 出队两个 */
    DeQueue(&Q, &e);
    printf("出队 %d\n", e);
    DeQueue(&Q, &e);
    printf("出队 %d\n", e);
    printf("遍历队列：");
    QueueTraverse(&Q);

    /* 清空 */
    ClearQueue(&Q);
    printf("清空后，队列长度 = %d，是否为空 = %s\n", QueueLength(&Q), QueueEmpty(&Q) ? "是" : "否");

    /* 空队出队测试 */
    if (!DeQueue(&Q, &e))
    {
        printf("空队出队被正确拒绝\n");
    }

    DestroyQueue(&Q);
    printf("销毁完成\n");
    return 0;
}
