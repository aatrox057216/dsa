/**
 * @file    demo.c
 * @brief   链式双端队列功能演示：两端插入、两端删除、双向遍历、单元素边界。
 * @author  aatroxfans
 * @date    2026-10-30
 */

#include "Deque.h"
#include <stdio.h>

int main(void)
{
    Deque D;
    int e;

    DequeInit(&D);
    printf("初始化后，size = %d，是否为空 = %s\n", DequeSize(&D), DequeIsEmpty(&D) ? "是" : "否");

    /* 两端交替插入：头插 1 3 5，尾插 2 4 6 */
    DequePushBack(&D, 2);
    DequePushFront(&D, 1);
    DequePushBack(&D, 4);
    DequePushFront(&D, 3);
    DequePushBack(&D, 6);
    DequePushFront(&D, 5);
    printf("两端插入后正向遍历：");
    DequeTraverseForward(&D);
    printf("反向遍历：");
    DequeTraverseBackward(&D);
    printf("size = %d\n", DequeSize(&D));

    /* 取两端元素 */
    DequeGetFront(&D, &e);
    printf("队头 = %d\n", e);
    DequeGetBack(&D, &e);
    printf("队尾 = %d\n", e);

    /* 两端删除 */
    DequePopFront(&D, &e);
    printf("头删 %d\n", e);
    DequePopBack(&D, &e);
    printf("尾删 %d\n", e);
    printf("删除后正向遍历：");
    DequeTraverseForward(&D);

    /* 边界：删到只剩一个元素，再删空，验证 front/rear 同步置空 */
    DequeClear(&D);
    DequePushFront(&D, 42);
    printf("单元素队列：");
    DequeTraverseForward(&D);
    DequePopBack(&D, &e);
    printf("尾删唯一元素 %d，是否为空 = %s\n", e, DequeIsEmpty(&D) ? "是" : "否");

    /* 空队删除测试 */
    if (!DequePopFront(&D, &e))
    {
        printf("空队头删被正确拒绝\n");
    }
    if (!DequePopBack(&D, &e))
    {
        printf("空队尾删被正确拒绝\n");
    }

    DequeDestroy(&D);
    printf("销毁完成\n");
    return 0;
}
