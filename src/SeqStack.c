/**
 * @file    SeqStack.c
 * @brief   顺序栈接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "SeqStack.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== 内部辅助宏 ==================== */

/** @brief 参数有效性检查 */
#define CHECK_STACK(stack, ret)                                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((stack) == NULL)                                                                                           \
        {                                                                                                              \
            return (ret);                                                                                              \
        }                                                                                                              \
    } while (0)

/** @brief 下标范围检查 [0, upper] */
#define CHECK_INDEX(index, upper, ret)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((index) < 0 || (index) > (upper))                                                                          \
        {                                                                                                              \
            return (ret);                                                                                              \
        }                                                                                                              \
    } while (0)

/* ==================== 生命周期 ==================== */

SSStatus SS_Init(SeqStack *stack)
{
    if (stack == NULL)
    {
        return SS_ERR_INVALID;
    }
    memset(stack->data, 0, sizeof(stack->data));
    stack->top = -1;
    return SS_OK;
}

SSStatus SS_Clear(SeqStack *stack)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    stack->top = -1;
    return SS_OK;
}

SSStatus SS_Destroy(SeqStack *stack)
{
    /* 静态存储，无需释放，语义上等价于 Clear */
    return SS_Clear(stack);
}

/* ==================== 容量与状态 ==================== */

int SS_Size(const SeqStack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    return stack->top + 1;
}

int SS_Capacity(const SeqStack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    return MAX_SIZE;
}

bool SS_IsEmpty(const SeqStack *stack)
{
    if (stack == NULL)
    {
        return false;
    }
    return stack->top == -1;
}

bool SS_IsFull(const SeqStack *stack)
{
    if (stack == NULL)
    {
        return false;
    }
    return stack->top >= MAX_SIZE - 1;
}

/* ==================== 核心操作 ==================== */

SSStatus SS_Push(SeqStack *stack, ElemType elem)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    if (SS_IsFull(stack))
    {
        return SS_ERR_FULL;
    }
    ++stack->top;
    stack->data[stack->top] = elem;
    return SS_OK;
}

SSStatus SS_Pop(SeqStack *stack, ElemType *out)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    if (SS_IsEmpty(stack))
    {
        return SS_ERR_EMPTY;
    }
    if (out != NULL)
    {
        *out = stack->data[stack->top];
    }
    --stack->top;
    return SS_OK;
}

SSStatus SS_Top(const SeqStack *stack, ElemType *out)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    if (out == NULL)
    {
        return SS_ERR_INVALID;
    }
    if (SS_IsEmpty(stack))
    {
        return SS_ERR_EMPTY;
    }
    *out = stack->data[stack->top];
    return SS_OK;
}

int SS_TopIndex(const SeqStack *stack)
{
    if (stack == NULL)
    {
        return -2;
    }
    return stack->top;
}

/* ==================== 查找 ==================== */

SSStatus SS_GetElem(const SeqStack *stack, int index, ElemType *out)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    if (out == NULL)
    {
        return SS_ERR_INVALID;
    }
    CHECK_INDEX(index, stack->top, SS_ERR_FULL);
    *out = stack->data[index];
    return SS_OK;
}

int SS_LocateFromTop(const SeqStack *stack, ElemType elem)
{
    if (stack == NULL)
    {
        return -1;
    }
    int distance = 0;
    for (int i = stack->top; i >= 0; --i, ++distance)
    {
        if (stack->data[i] == elem)
        {
            return distance;
        }
    }
    return -1;
}

/* ==================== 遍历与显示 ==================== */

SSStatus SS_TraverseBottomUp(const SeqStack *stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    if (callback == NULL)
    {
        return SS_ERR_INVALID;
    }
    for (int i = 0; i <= stack->top; ++i)
    {
        if (!callback(stack->data[i], i, ctx))
        {
            break;
        }
    }
    return SS_OK;
}

SSStatus SS_TraverseTopDown(const SeqStack *stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_STACK(stack, SS_ERR_INVALID);
    if (callback == NULL)
    {
        return SS_ERR_INVALID;
    }
    int idx = 0;
    for (int i = stack->top; i >= 0; --i, ++idx)
    {
        if (!callback(stack->data[i], idx, ctx))
        {
            break;
        }
    }
    return SS_OK;
}

SSStatus SS_Print(const SeqStack *stack)
{
    CHECK_STACK(stack, SS_ERR_INVALID);

    printf("SeqStack(size=%d, cap=%d): bottom [", SS_Size(stack), MAX_SIZE);
    for (int i = 0; i <= stack->top; ++i)
    {
        printf("%d", stack->data[i]);
        if (i != stack->top)
        {
            printf(", ");
        }
    }
    printf("] top\n");
    return SS_OK;
}

/* ==================== 经典应用 ==================== */

bool SS_CheckBrackets(const char *expr)
{
    if (expr == NULL)
    {
        return false;
    }
    SeqStack stack;
    SS_Init(&stack);

    for (const char *p = expr; *p != '\0'; ++p)
    {
        char c = *p;
        if (c == '(' || c == '[' || c == '{')
        {
            if (SS_Push(&stack, (ElemType)c) != SS_OK)
            {
                return false; /* 栈满视为失败 */
            }
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            ElemType topChar;
            if (SS_Pop(&stack, &topChar) != SS_OK)
            {
                return false; /* 右括号多余 */
            }
            if ((c == ')' && topChar != '(') || (c == ']' && topChar != '[') || (c == '}' && topChar != '{'))
            {
                return false; /* 括号不配对 */
            }
        }
    }
    return SS_IsEmpty(&stack); /* 左括号是否全部匹配 */
}

SSStatus SS_DecimalToBase(int decimal, int base, char *out)
{
    if (decimal < 0 || base < 2 || base > 36 || out == NULL)
    {
        return SS_ERR_INVALID;
    }

    static const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    SeqStack stack;
    SS_Init(&stack);

    if (decimal == 0)
    {
        out[0] = '0';
        out[1] = '\0';
        return SS_OK;
    }

    /* 反复取余压栈 */
    int value = decimal;
    while (value > 0)
    {
        if (SS_Push(&stack, value % base) != SS_OK)
        {
            return SS_ERR_FULL;
        }
        value /= base;
    }

    /* 依次弹栈，得到高位到低位 */
    int i = 0;
    ElemType digit;
    while (SS_Pop(&stack, &digit) == SS_OK)
    {
        out[i++] = DIGITS[digit];
    }
    out[i] = '\0';
    return SS_OK;
}

// NOSONAR
SSStatus SS_EvalRPN(const char *expr, int *out)
{
    if (expr == NULL || out == NULL)
    {
        return SS_ERR_INVALID;
    }

    SeqStack stack;
    SS_Init(&stack);

    const char *p = expr;
    while (*p != '\0')
    {
        /* 跳过空白 */
        if (isspace((unsigned char)*p))
        {
            ++p;
            continue;
        }

        if (*p == '+' || *p == '-' || *p == '*' || *p == '/')
        {
            ElemType b, a;
            if (SS_Pop(&stack, &b) != SS_OK || SS_Pop(&stack, &a) != SS_OK)
            {
                return SS_ERR_INVALID; /* 操作数不足 */
            }
            ElemType r = 0;
            switch (*p)
            {
            case '+':
                r = a + b;
                break;
            case '-':
                r = a - b;
                break;
            case '*':
                r = a * b;
                break;
            case '/':
                if (b == 0)
                    return SS_ERR_INVALID;
                r = a / b;
                break;
            }
            if (SS_Push(&stack, r) != SS_OK)
            {
                return SS_ERR_FULL;
            }
            ++p;
        }
        else if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p + 1))))
        {
            /* 解析整数（含负号） */
            char *end = NULL;
            long v = strtol(p, &end, 10);
            if (SS_Push(&stack, (ElemType)v) != SS_OK)
            {
                return SS_ERR_FULL;
            }
            p = end;
        }
        else
        {
            return SS_ERR_INVALID;
        }
    }

    if (SS_Size(&stack) != 1)
    {
        return SS_ERR_INVALID; /* 结果不唯一 */
    }
    SS_Pop(&stack, out);
    return SS_OK;
}

SSStatus SS_TwoStacksQueue(const int *ops, const int *vals, int n, int *out, int *outLen)
{
    if (ops == NULL || vals == NULL || out == NULL || outLen == NULL || n < 0)
    {
        return SS_ERR_INVALID;
    }

    SeqStack in, outStack;
    SS_Init(&in);
    SS_Init(&outStack);

    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (ops[i] == 0)
        {
            /* 入队：压入 in 栈 */
            if (SS_Push(&in, vals[i]) != SS_OK)
            {
                return SS_ERR_FULL;
            }
        }
        else if (ops[i] == 1)
        {
            /* 出队：若 outStack 为空，将 in 全部倒入 */
            if (SS_IsEmpty(&outStack))
            {
                ElemType tmp;
                while (SS_Pop(&in, &tmp) == SS_OK)
                {
                    if (SS_Push(&outStack, tmp) != SS_OK)
                    {
                        return SS_ERR_FULL;
                    }
                }
            }
            ElemType v;
            if (SS_Pop(&outStack, &v) != SS_OK)
            {
                return SS_ERR_EMPTY; /* 队列为空 */
            }
            out[count++] = v;
        }
        else
        {
            return SS_ERR_INVALID;
        }
    }
    *outLen = count;
    return SS_OK;
}
