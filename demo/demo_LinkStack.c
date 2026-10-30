/**
 * @file    main.c
 * @brief   链栈使用示例
 */

#include "LinkStack.h"
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
    LinkStack stack;

    /* ---------- 初始化与压栈 ---------- */
    LS_Init(&stack);
    printf("初始化后：");
    LS_Print(stack);

    for (int i = 1; i <= 5; ++i)
    {
        LS_Push(&stack, i * 10);
    }
    printf("压入 10/20/30/40/50 后：");
    LS_Print(stack);

    /* ---------- 取栈顶 ---------- */
    ElemType topVal;
    LS_Top(stack, &topVal);
    printf("栈顶元素：%d\n", topVal);

    /* ---------- 弹栈 ---------- */
    ElemType popped;
    LS_Pop(&stack, &popped);
    printf("弹出栈顶（值 %d）后：", popped);
    LS_Print(stack);

    /* ---------- 查找 ---------- */
    printf("距栈顶最近的 30 距离：%d\n", LS_LocateFromTop(stack, 30));
    ElemType val;
    LS_GetElem(stack, 0, &val);
    printf("栈底元素：%d\n", val);

    /* ---------- 双向遍历 ---------- */
    printf("从栈顶到栈底遍历：\n");
    LS_TraverseTopDown(stack, print_cb, NULL);
    printf("从栈底到栈顶遍历：\n");
    LS_TraverseBottomUp(stack, print_cb, NULL);

    /* ---------- 括号匹配 ---------- */
    const char *tests[] = { "{[()]}", "([]{})", "((()))", "([)]", "((", "))" };
    printf("\n括号匹配测试：\n");
    for (int i = 0; i < 6; ++i)
    {
        printf("  \"%s\" -> %s\n", tests[i], LS_CheckBrackets(tests[i]) ? "匹配" : "不匹配");
    }

    /* ---------- 进制转换 ---------- */
    char buf[64];
    printf("\n进制转换：\n");
    LS_DecimalToBase(255, 2, buf);
    printf("  255 -> 二进制 %s\n", buf);
    LS_DecimalToBase(255, 16, buf);
    printf("  255 -> 十六进制 %s\n", buf);
    LS_DecimalToBase(1000, 36, buf);
    printf("  1000 -> 36 进制 %s\n", buf);

    /* ---------- 后缀表达式求值 ---------- */
    int result = 0;
    printf("\n后缀表达式求值：\n");
    LS_EvalRPN("3 4 + 2 * 7 -", &result);
    printf("  \"3 4 + 2 * 7 -\" = %d\n", result);
    LS_EvalRPN("5 1 2 + 4 * + 3 -", &result);
    printf("  \"5 1 2 + 4 * + 3 -\" = %d\n", result);

    /* ---------- 中缀表达式求值 ---------- */
    printf("\n中缀表达式求值：\n");
    LS_EvalInfix("3 + 4 * 2 - 7", &result);
    printf("  \"3 + 4 * 2 - 7\" = %d\n", result);
    LS_EvalInfix("(1 + 2) * (3 + 4)", &result);
    printf("  \"(1 + 2) * (3 + 4)\" = %d\n", result);

    /* ---------- 出栈序列合法性 ---------- */
    int pushSeq[] = { 1, 2, 3, 4, 5 };
    int pop1[] = { 4, 5, 3, 2, 1 }; /* 合法 */
    int pop2[] = { 4, 3, 5, 1, 2 }; /* 非法 */
    printf("\n出栈序列合法性：\n");
    printf("  {4,5,3,2,1} -> %s\n", LS_IsPopOrderValid(pushSeq, pop1, 5) ? "合法" : "非法");
    printf("  {4,3,5,1,2} -> %s\n", LS_IsPopOrderValid(pushSeq, pop2, 5) ? "合法" : "非法");

    /* ---------- 清空 ---------- */
    LS_Clear(&stack);
    printf("\n清空后：");
    LS_Print(stack);

    return 0;
}
