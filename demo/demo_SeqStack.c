/**
 * @file    main.c
 * @brief   顺序栈使用示例
 */

#include "SeqStack.h"
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
    SeqStack stack;

    /* ---------- 初始化与压栈 ---------- */
    SS_Init(&stack);
    printf("初始化后：");
    SS_Print(&stack);

    for (int i = 1; i <= 5; ++i)
    {
        SS_Push(&stack, i * 10);
    }
    printf("压入 10/20/30/40/50 后：");
    SS_Print(&stack);

    /* ---------- 取栈顶 ---------- */
    ElemType topVal;
    SS_Top(&stack, &topVal);
    printf("栈顶元素：%d\n", topVal);

    /* ---------- 弹栈 ---------- */
    ElemType popped;
    SS_Pop(&stack, &popped);
    printf("弹出栈顶（值 %d）后：", popped);
    SS_Print(&stack);

    /* ---------- 查找 ---------- */
    printf("距栈顶最近的 30 距离：%d\n", SS_LocateFromTop(&stack, 30));
    ElemType val;
    SS_GetElem(&stack, 0, &val);
    printf("栈底元素：%d\n", val);

    /* ---------- 双向遍历 ---------- */
    printf("从栈底到栈顶遍历：\n");
    SS_TraverseBottomUp(&stack, print_cb, NULL);
    printf("从栈顶到栈底遍历：\n");
    SS_TraverseTopDown(&stack, print_cb, NULL);

    /* ---------- 括号匹配 ---------- */
    const char *tests[] = { "{[()]}", "([]{})", "((()))", "([)]", "((", "))" };
    printf("\n括号匹配测试：\n");
    for (int i = 0; i < 6; ++i)
    {
        printf("  \"%s\" -> %s\n", tests[i], SS_CheckBrackets(tests[i]) ? "匹配" : "不匹配");
    }

    /* ---------- 进制转换 ---------- */
    char buf[64];
    printf("\n进制转换：\n");
    SS_DecimalToBase(255, 2, buf);
    printf("  255 -> 二进制 %s\n", buf);
    SS_DecimalToBase(255, 16, buf);
    printf("  255 -> 十六进制 %s\n", buf);
    SS_DecimalToBase(1000, 36, buf);
    printf("  1000 -> 36 进制 %s\n", buf);

    /* ---------- 后缀表达式求值 ---------- */
    int result = 0;
    printf("\n后缀表达式求值：\n");
    SS_EvalRPN("3 4 + 2 * 7 -", &result);
    printf("  \"3 4 + 2 * 7 -\" = %d\n", result);
    SS_EvalRPN("5 1 2 + 4 * + 3 -", &result);
    printf("  \"5 1 2 + 4 * + 3 -\" = %d\n", result);

    /* ---------- 两个栈实现队列 ---------- */
    int ops[] = { 0, 0, 0, 1, 0, 1, 1 };
    int vals[] = { 1, 2, 3, 0, 4, 0, 0 };
    int outs[16] = { 0 };
    int outLen = 0;
    SS_TwoStacksQueue(ops, vals, 7, outs, &outLen);
    printf("\n两个栈实现队列，出队序列：");
    for (int i = 0; i < outLen; ++i)
    {
        printf("%d ", outs[i]);
    }
    printf("\n");

    /* ---------- 清空 ---------- */
    SS_Clear(&stack);
    printf("\n清空后：");
    SS_Print(&stack);

    return 0;
}
