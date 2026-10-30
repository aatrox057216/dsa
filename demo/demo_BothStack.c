/**
 * @file    main.c
 * @brief   双栈共享存储空间使用示例
 */

#include "BothStack.h"
#include <stdio.h>

/** @brief 遍历回调：打印元素 */
static bool print_cb(ElemType elem, int index, void *ctx)
{
    (void)ctx;
    printf("  [%d] = %d\n", index, elem);
    return true;
}

int main(void)
{
    BothStack bs;

    /* ---------- 初始化 ---------- */
    BS_Init(&bs);
    printf("初始化后：\n");
    BS_Print(&bs);

    /* ---------- 向两个栈压入元素 ---------- */
    for (int i = 1; i <= 5; ++i)
    {
        BS_Push(&bs, STACK_1, i * 10); /* 栈1: 10 20 30 40 50 */
    }
    for (int i = 1; i <= 3; ++i)
    {
        BS_Push(&bs, STACK_2, i * 100); /* 栈2: 100 200 300 */
    }
    printf("\n压入栈1(10..50) 与栈2(100..300) 后：\n");
    BS_Print(&bs);
    printf("剩余槽位：%d\n", BS_Remaining(&bs));

    /* ---------- 取栈顶 ---------- */
    ElemType topVal;
    BS_Top(&bs, STACK_1, &topVal);
    printf("\n栈1栈顶：%d\n", topVal);
    BS_Top(&bs, STACK_2, &topVal);
    printf("栈2栈顶：%d\n", topVal);

    /* ---------- 弹栈 ---------- */
    ElemType popped;
    BS_Pop(&bs, STACK_1, &popped);
    printf("\n弹出栈1栈顶（值 %d）后：\n", popped);
    BS_Print(&bs);

    /* ---------- 查找 ---------- */
    printf("\n栈1中 30 距栈顶距离：%d\n", BS_LocateFromTop(&bs, STACK_1, 30));

    ElemType val;
    BS_GetElem(&bs, STACK_1, 0, &val);
    printf("栈1栈底元素：%d\n", val);
    BS_GetElem(&bs, STACK_2, 0, &val);
    printf("栈2栈底元素：%d\n", val);

    /* ---------- 遍历 ---------- */
    printf("\n栈1从栈底到栈顶遍历：\n");
    BS_TraverseBottomUp(&bs, STACK_1, print_cb, NULL);
    printf("栈2从栈顶到栈底遍历：\n");
    BS_TraverseTopDown(&bs, STACK_2, print_cb, NULL);

    /* ---------- 逆序 ---------- */
    BS_ReverseStack1(&bs);
    printf("\n栈1逆序后：\n");
    BS_Print(&bs);

    /* ---------- 转移元素 ---------- */
    BS_TransferOne(&bs, STACK_1); /* 栈1 → 栈2 */
    printf("\n将栈1栈顶转移到栈2后：\n");
    BS_Print(&bs);

    /* ---------- 判满演示：填满共享空间 ---------- */
    printf("\n填满共享空间...\n");
    while (!BS_IsFull(&bs))
    {
        /* 交替压入两栈 */
        if (BS_Size(&bs, STACK_1) <= BS_Size(&bs, STACK_2))
        {
            if (BS_Push(&bs, STACK_1, 999) != BS_OK)
                break;
        }
        else
        {
            if (BS_Push(&bs, STACK_2, 888) != BS_OK)
                break;
        }
    }
    printf("是否已满：%s\n", BS_IsFull(&bs) ? "true" : "false");
    printf("栈1大小=%d，栈2大小=%d，剩余=%d\n", BS_Size(&bs, STACK_1), BS_Size(&bs, STACK_2), BS_Remaining(&bs));

    /* ---------- 清空 ---------- */
    BS_Clear(&bs, STACK_1);
    printf("\n仅清空栈1后：\n");
    BS_Print(&bs);

    BS_ClearAll(&bs);
    printf("\n清空全部后：\n");
    BS_Print(&bs);

    return 0;
}
