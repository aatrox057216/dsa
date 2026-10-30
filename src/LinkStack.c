/**
 * @file    LinkStack.c
 * @brief   链栈接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "LinkStack.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== 内部辅助 ==================== */

/**
 * @brief 内部函数：创建新结点
 * @param  elem 结点数据
 * @return 新结点指针；失败返回 NULL
 */
static StackNode *LS_NewNode(ElemType elem)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = elem;
    node->next = NULL;
    return node;
}

/* ==================== 生命周期 ==================== */

LSStatus LS_Init(LinkStack *stack)
{
    if (stack == NULL)
    {
        return LS_ERR_INVALID;
    }
    *stack = NULL;
    return LS_OK;
}

LSStatus LS_Clear(LinkStack *stack)
{
    if (stack == NULL)
    {
        return LS_ERR_INVALID;
    }
    StackNode *cur = *stack;
    while (cur != NULL)
    {
        StackNode *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    *stack = NULL;
    return LS_OK;
}

LSStatus LS_Destroy(LinkStack *stack)
{
    /* 链栈无独立头结点，Destroy 与 Clear 等价 */
    return LS_Clear(stack);
}

/* ==================== 容量与状态 ==================== */

int LS_Size(LinkStack stack)
{
    int len = 0;
    StackNode *cur = stack;
    while (cur != NULL)
    {
        ++len;
        cur = cur->next;
    }
    return len;
}

bool LS_IsEmpty(LinkStack stack)
{
    return stack == NULL;
}

/* ==================== 核心操作 ==================== */

LSStatus LS_Push(LinkStack *stack, ElemType elem)
{
    if (stack == NULL)
    {
        return LS_ERR_INVALID;
    }
    StackNode *node = LS_NewNode(elem);
    if (node == NULL)
    {
        return LS_ERR_NOMEM;
    }
    /* 头插：新结点成为新栈顶 */
    node->next = *stack;
    *stack = node;
    return LS_OK;
}

LSStatus LS_Pop(LinkStack *stack, ElemType *out)
{
    if (stack == NULL)
    {
        return LS_ERR_INVALID;
    }
    if (*stack == NULL)
    {
        return LS_ERR_EMPTY;
    }
    StackNode *top = *stack;
    if (out != NULL)
    {
        *out = top->data;
    }
    *stack = top->next;
    free(top);
    return LS_OK;
}

LSStatus LS_Top(LinkStack stack, ElemType *out)
{
    if (stack == NULL)
    {
        return LS_ERR_EMPTY;
    }
    if (out == NULL)
    {
        return LS_ERR_INVALID;
    }
    *out = stack->data;
    return LS_OK;
}

/* ==================== 查找 ==================== */

LSStatus LS_GetElem(LinkStack stack, int index, ElemType *out)
{
    if (out == NULL)
    {
        return LS_ERR_INVALID;
    }
    if (index < 0)
    {
        return LS_ERR_INVALID;
    }
    int len = LS_Size(stack);
    if (index >= len)
    {
        return LS_ERR_INVALID;
    }
    /* 栈顶为 index = len-1，栈底为 index = 0 */
    StackNode *cur = stack;
    for (int i = len - 1; i > index; --i)
    {
        cur = cur->next;
    }
    *out = cur->data;
    return LS_OK;
}

int LS_LocateFromTop(LinkStack stack, ElemType elem)
{
    int distance = 0;
    StackNode *cur = stack;
    while (cur != NULL)
    {
        if (cur->data == elem)
        {
            return distance;
        }
        cur = cur->next;
        ++distance;
    }
    return -1;
}

/* ==================== 遍历与显示 ==================== */

LSStatus LS_TraverseTopDown(LinkStack stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    if (callback == NULL)
    {
        return LS_ERR_INVALID;
    }
    int idx = 0;
    StackNode *cur = stack;
    while (cur != NULL)
    {
        if (!callback(cur->data, idx, ctx))
        {
            break;
        }
        cur = cur->next;
        ++idx;
    }
    return LS_OK;
}

LSStatus LS_TraverseBottomUp(LinkStack stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    if (callback == NULL)
    {
        return LS_ERR_INVALID;
    }
    int len = LS_Size(stack);
    for (int i = 0; i < len; ++i)
    {
        ElemType val;
        LS_GetElem(stack, i, &val);
        if (!callback(val, i, ctx))
        {
            break;
        }
    }
    return LS_OK;
}

LSStatus LS_Print(LinkStack stack)
{
    printf("LinkStack(size=%d): bottom [", LS_Size(stack));

    /* 先收集到临时数组，逆序打印，避免递归 */
    int len = LS_Size(stack);
    if (len > 0)
    {
        ElemType *buf = (ElemType *)malloc(sizeof(ElemType) * len);
        if (buf != NULL)
        {
            StackNode *cur = stack;
            for (int i = len - 1; i >= 0; --i)
            {
                buf[i] = cur->data;
                cur = cur->next;
            }
            for (int i = 0; i < len; ++i)
            {
                printf("%d", buf[i]);
                if (i != len - 1)
                {
                    printf(", ");
                }
            }
            free(buf);
        }
    }
    printf("] top\n");
    return LS_OK;
}

/* ==================== 经典应用 ==================== */

bool LS_CheckBrackets(const char *expr)
{
    if (expr == NULL)
    {
        return false;
    }
    LinkStack stack;
    LS_Init(&stack);

    for (const char *p = expr; *p != '\0'; ++p)
    {
        char c = *p;
        if (c == '(' || c == '[' || c == '{')
        {
            if (LS_Push(&stack, (ElemType)c) != LS_OK)
            {
                LS_Destroy(&stack);
                return false;
            }
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            ElemType topChar;
            if (LS_Pop(&stack, &topChar) != LS_OK)
            {
                LS_Destroy(&stack);
                return false;
            }
            if ((c == ')' && topChar != '(') || (c == ']' && topChar != '[') || (c == '}' && topChar != '{'))
            {
                LS_Destroy(&stack);
                return false;
            }
        }
    }
    bool ok = LS_IsEmpty(stack);
    LS_Destroy(&stack);
    return ok;
}

LSStatus LS_DecimalToBase(int decimal, int base, char *out)
{
    if (decimal < 0 || base < 2 || base > 36 || out == NULL)
    {
        return LS_ERR_INVALID;
    }
    static const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (decimal == 0)
    {
        out[0] = '0';
        out[1] = '\0';
        return LS_OK;
    }

    LinkStack stack;
    LS_Init(&stack);

    int value = decimal;
    while (value > 0)
    {
        if (LS_Push(&stack, value % base) != LS_OK)
        {
            LS_Destroy(&stack);
            return LS_ERR_NOMEM;
        }
        value /= base;
    }

    int i = 0;
    ElemType digit;
    while (LS_Pop(&stack, &digit) == LS_OK)
    {
        out[i++] = DIGITS[digit];
    }
    out[i] = '\0';
    return LS_OK;
}

LSStatus LS_EvalRPN(const char *expr, int *out)
{
    if (expr == NULL || out == NULL)
    {
        return LS_ERR_INVALID;
    }
    LinkStack stack;
    LS_Init(&stack);

    const char *p = expr;
    while (*p != '\0')
    {
        if (isspace((unsigned char)*p))
        {
            ++p;
            continue;
        }

        if (*p == '+' || *p == '-' || *p == '*' || *p == '/')
        {
            ElemType b, a;
            if (LS_Pop(&stack, &b) != LS_OK || LS_Pop(&stack, &a) != LS_OK)
            {
                LS_Destroy(&stack);
                return LS_ERR_INVALID;
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
                {
                    LS_Destroy(&stack);
                    return LS_ERR_INVALID;
                }
                r = a / b;
                break;
            }
            if (LS_Push(&stack, r) != LS_OK)
            {
                LS_Destroy(&stack);
                return LS_ERR_NOMEM;
            }
            ++p;
        }
        else if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p + 1))))
        {
            char *end = NULL;
            long v = strtol(p, &end, 10);
            if (LS_Push(&stack, (ElemType)v) != LS_OK)
            {
                LS_Destroy(&stack);
                return LS_ERR_NOMEM;
            }
            p = end;
        }
        else
        {
            LS_Destroy(&stack);
            return LS_ERR_INVALID;
        }
    }

    if (LS_Size(stack) != 1)
    {
        LS_Destroy(&stack);
        return LS_ERR_INVALID;
    }
    LS_Pop(&stack, out);
    return LS_OK;
}

/* ==================== 中缀表达式求值（双链栈） ==================== */

/**
 * @brief 内部函数：获取运算符优先级
 * @return 数值越大优先级越高；非法运算符返回 -1
 */
static int infix_priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}

/**
 * @brief 内部函数：从操作数栈弹出两个数并计算
 */
static bool infix_apply(LinkStack *numStack, char op)
{
    ElemType b, a;
    if (LS_Pop(numStack, &b) != LS_OK)
        return false;
    if (LS_Pop(numStack, &a) != LS_OK)
        return false;
    ElemType r = 0;
    switch (op)
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
            return false;
        r = a / b;
        break;
    default:
        return false;
    }
    return LS_Push(numStack, r) == LS_OK;
}

LSStatus LS_EvalInfix(const char *expr, int *out)
{
    if (expr == NULL || out == NULL)
    {
        return LS_ERR_INVALID;
    }

    LinkStack numStack; /* 操作数栈 */
    LinkStack opStack;  /* 运算符栈 */
    LS_Init(&numStack);
    LS_Init(&opStack);

    const char *p = expr;
    while (*p != '\0')
    {
        if (isspace((unsigned char)*p))
        {
            ++p;
            continue;
        }

        if (isdigit((unsigned char)*p)
            || (*p == '-' && isdigit((unsigned char)*(p + 1)) && (p == expr || !isdigit((unsigned char)*(p - 1)))))
        {
            /* 解析整数（含负号） */
            char *end = NULL;
            long v = strtol(p, &end, 10);
            if (LS_Push(&numStack, (ElemType)v) != LS_OK)
            {
                LS_Destroy(&numStack);
                LS_Destroy(&opStack);
                return LS_ERR_NOMEM;
            }
            p = end;
        }
        else if (*p == '(')
        {
            if (LS_Push(&opStack, (ElemType)*p) != LS_OK)
            {
                LS_Destroy(&numStack);
                LS_Destroy(&opStack);
                return LS_ERR_NOMEM;
            }
            ++p;
        }
        else if (*p == ')')
        {
            /* 弹出运算符直到遇到 '(' */
            bool matched = false;
            while (!LS_IsEmpty(opStack))
            {
                ElemType op;
                LS_Pop(&opStack, &op);
                if ((char)op == '(')
                {
                    matched = true;
                    break;
                }
                if (!infix_apply(&numStack, (char)op))
                {
                    LS_Destroy(&numStack);
                    LS_Destroy(&opStack);
                    return LS_ERR_INVALID;
                }
            }
            if (!matched)
            {
                LS_Destroy(&numStack);
                LS_Destroy(&opStack);
                return LS_ERR_INVALID;
            }
            ++p;
        }
        else if (infix_priority(*p) > 0)
        {
            while (!LS_IsEmpty(opStack))
            {
                ElemType topOp;
                LS_Top(opStack, &topOp);
                if ((char)topOp == '(')
                    break;
                if (infix_priority((char)topOp) < infix_priority(*p))
                    break;
                LS_Pop(&opStack, &topOp);
                if (!infix_apply(&numStack, (char)topOp))
                {
                    LS_Destroy(&numStack);
                    LS_Destroy(&opStack);
                    return LS_ERR_INVALID;
                }
            }
            if (LS_Push(&opStack, (ElemType)*p) != LS_OK)
            {
                LS_Destroy(&numStack);
                LS_Destroy(&opStack);
                return LS_ERR_NOMEM;
            }
            ++p;
        }
        else
        {
            LS_Destroy(&numStack);
            LS_Destroy(&opStack);
            return LS_ERR_INVALID;
        }
    }

    /* 处理剩余运算符 */
    while (!LS_IsEmpty(opStack))
    {
        ElemType op;
        LS_Pop(&opStack, &op);
        if ((char)op == '(')
        {
            LS_Destroy(&numStack);
            LS_Destroy(&opStack);
            return LS_ERR_INVALID;
        }
        if (!infix_apply(&numStack, (char)op))
        {
            LS_Destroy(&numStack);
            LS_Destroy(&opStack);
            return LS_ERR_INVALID;
        }
    }

    if (LS_Size(numStack) != 1)
    {
        LS_Destroy(&numStack);
        LS_Destroy(&opStack);
        return LS_ERR_INVALID;
    }
    LS_Pop(&numStack, out);
    return LS_OK;
}

/* ==================== 出栈序列合法性 ==================== */

bool LS_IsPopOrderValid(const int *pushSeq, const int *popSeq, int n)
{
    if ((pushSeq == NULL || popSeq == NULL) && n > 0)
    {
        return false;
    }
    if (n <= 0)
    {
        return true;
    }

    LinkStack stack;
    LS_Init(&stack);

    int j = 0; /* popSeq 指针 */
    for (int i = 0; i < n; ++i)
    {
        /* 压入 pushSeq[i] */
        if (LS_Push(&stack, pushSeq[i]) != LS_OK)
        {
            LS_Destroy(&stack);
            return false;
        }
        /* 尽可能弹出与 popSeq 匹配的栈顶 */
        while (!LS_IsEmpty(stack))
        {
            ElemType top;
            LS_Top(stack, &top);
            if (top == popSeq[j])
            {
                LS_Pop(&stack, NULL);
                ++j;
            }
            else
            {
                break;
            }
        }
    }

    bool ok = (j == n) && LS_IsEmpty(stack);
    LS_Destroy(&stack);
    return ok;
}
