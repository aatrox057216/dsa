/**
 * @file    BothStack.c
 * @brief   双栈共享存储空间接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "BothStack.h"
#include <stdio.h>
#include <string.h>

/* ==================== 内部辅助宏 ==================== */

/** @brief 参数有效性检查 */
#define CHECK_STACK(bs, ret)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((bs) == NULL)                                                                                              \
        {                                                                                                              \
            return (ret);                                                                                              \
        }                                                                                                              \
    } while (0)

/** @brief 栈号合法性检查 */
#define CHECK_STACK_NO(stackNo, ret)                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((stackNo) != STACK_1 && (stackNo) != STACK_2)                                                              \
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

BSStatus BS_Init(BothStack *bs)
{
    if (bs == NULL)
    {
        return BS_ERR_INVALID;
    }
    memset(bs->data, 0, sizeof(bs->data));
    bs->top1 = -1;
    bs->top2 = MAX_SIZE;
    return BS_OK;
}

BSStatus BS_Clear(BothStack *bs, int stackNo)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);

    if (stackNo == STACK_1)
    {
        bs->top1 = -1;
    }
    else
    {
        bs->top2 = MAX_SIZE;
    }
    return BS_OK;
}

BSStatus BS_ClearAll(BothStack *bs)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    bs->top1 = -1;
    bs->top2 = MAX_SIZE;
    return BS_OK;
}

BSStatus BS_Destroy(BothStack *bs)
{
    return BS_ClearAll(bs);
}

/* ==================== 容量与状态 ==================== */

int BS_Size(const BothStack *bs, int stackNo)
{
    if (bs == NULL || (stackNo != STACK_1 && stackNo != STACK_2))
    {
        return -1;
    }
    if (stackNo == STACK_1)
    {
        return bs->top1 + 1;
    }
    return MAX_SIZE - bs->top2;
}

int BS_Capacity(const BothStack *bs)
{
    if (bs == NULL)
    {
        return -1;
    }
    return MAX_SIZE;
}

int BS_Remaining(const BothStack *bs)
{
    if (bs == NULL)
    {
        return -1;
    }
    /* 剩余 = MAX_SIZE - size1 - size2 */
    return (bs->top2 - bs->top1 - 1);
}

bool BS_IsEmpty(const BothStack *bs, int stackNo)
{
    if (bs == NULL)
    {
        return false;
    }
    if (stackNo == STACK_1)
    {
        return bs->top1 == -1;
    }
    if (stackNo == STACK_2)
    {
        return bs->top2 == MAX_SIZE;
    }
    return false;
}

bool BS_IsFull(const BothStack *bs)
{
    if (bs == NULL)
    {
        return false;
    }
    /* 判满：两栈顶相邻 */
    return bs->top1 + 1 == bs->top2;
}

/* ==================== 核心操作 ==================== */

BSStatus BS_Push(BothStack *bs, int stackNo, ElemType elem)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);

    if (BS_IsFull(bs))
    {
        return BS_ERR_FULL;
    }
    if (stackNo == STACK_1)
    {
        /* 栈 1 向高位增长 */
        ++bs->top1;
        bs->data[bs->top1] = elem;
    }
    else
    {
        /* 栈 2 向低位下降 */
        --bs->top2;
        bs->data[bs->top2] = elem;
    }
    return BS_OK;
}

BSStatus BS_Pop(BothStack *bs, int stackNo, ElemType *out)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);

    if (BS_IsEmpty(bs, stackNo))
    {
        return BS_ERR_EMPTY;
    }
    if (stackNo == STACK_1)
    {
        if (out != NULL)
        {
            *out = bs->data[bs->top1];
        }
        --bs->top1;
    }
    else
    {
        if (out != NULL)
        {
            *out = bs->data[bs->top2];
        }
        ++bs->top2;
    }
    return BS_OK;
}

BSStatus BS_Top(const BothStack *bs, int stackNo, ElemType *out)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);
    if (out == NULL)
    {
        return BS_ERR_INVALID;
    }
    if (BS_IsEmpty(bs, stackNo))
    {
        return BS_ERR_EMPTY;
    }
    if (stackNo == STACK_1)
    {
        *out = bs->data[bs->top1];
    }
    else
    {
        *out = bs->data[bs->top2];
    }
    return BS_OK;
}

int BS_TopIndex(const BothStack *bs, int stackNo)
{
    if (bs == NULL)
    {
        return -2;
    }
    if (stackNo == STACK_1)
    {
        return bs->top1;
    }
    if (stackNo == STACK_2)
    {
        return bs->top2;
    }
    return -2;
}

/* ==================== 查找 ==================== */

BSStatus BS_GetElem(const BothStack *bs, int stackNo, int index, ElemType *out)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);
    if (out == NULL)
    {
        return BS_ERR_INVALID;
    }

    int size = BS_Size(bs, stackNo);
    CHECK_INDEX(index, size - 1, BS_ERR_INVALID);

    if (stackNo == STACK_1)
    {
        /* 栈 1 栈底在 data[0]，向下标增长方向排列 */
        *out = bs->data[index];
    }
    else
    {
        /* 栈 2 栈底在 data[MAX_SIZE-1]，向下标减小方向排列 */
        *out = bs->data[MAX_SIZE - 1 - index];
    }
    return BS_OK;
}

int BS_LocateFromTop(const BothStack *bs, int stackNo, ElemType elem)
{
    if (bs == NULL || (stackNo != STACK_1 && stackNo != STACK_2))
    {
        return -1;
    }
    int distance = 0;
    if (stackNo == STACK_1)
    {
        for (int i = bs->top1; i >= 0; --i, ++distance)
        {
            if (bs->data[i] == elem)
            {
                return distance;
            }
        }
    }
    else
    {
        for (int i = bs->top2; i < MAX_SIZE; ++i, ++distance)
        {
            if (bs->data[i] == elem)
            {
                return distance;
            }
        }
    }
    return -1;
}

/* ==================== 遍历与显示 ==================== */

BSStatus BS_TraverseBottomUp(const BothStack *bs, int stackNo, bool (*callback)(ElemType elem, int index, void *ctx),
                             void *ctx)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);
    if (callback == NULL)
    {
        return BS_ERR_INVALID;
    }

    int size = BS_Size(bs, stackNo);
    for (int i = 0; i < size; ++i)
    {
        ElemType val;
        BS_GetElem(bs, stackNo, i, &val);
        if (!callback(val, i, ctx))
        {
            break;
        }
    }
    return BS_OK;
}

BSStatus BS_TraverseTopDown(const BothStack *bs, int stackNo, bool (*callback)(ElemType elem, int index, void *ctx),
                            void *ctx)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    CHECK_STACK_NO(stackNo, BS_ERR_INVALID);
    if (callback == NULL)
    {
        return BS_ERR_INVALID;
    }

    int size = BS_Size(bs, stackNo);
    int idx = 0;
    for (int i = size - 1; i >= 0; --i, ++idx)
    {
        ElemType val;
        BS_GetElem(bs, stackNo, i, &val);
        if (!callback(val, idx, ctx))
        {
            break;
        }
    }
    return BS_OK;
}

BSStatus BS_Print(const BothStack *bs)
{
    CHECK_STACK(bs, BS_ERR_INVALID);

    printf("BothStack(len=%d, cap=%d, free=%d)\n", BS_Size(bs, STACK_1) + BS_Size(bs, STACK_2), MAX_SIZE,
           BS_Remaining(bs));

    /* 栈 1 从栈底到栈顶 */
    printf("  Stack1: bottom [");
    for (int i = 0; i <= bs->top1; ++i)
    {
        printf("%d", bs->data[i]);
        if (i != bs->top1)
        {
            printf(", ");
        }
    }
    printf("] top\n");

    /* 空闲区域 */
    printf("  Free  : %d slots\n", BS_Remaining(bs));

    /* 栈 2 从栈底到栈顶（栈底在 MAX_SIZE-1，栈顶在 top2） */
    printf("  Stack2: top [");
    for (int i = bs->top2; i < MAX_SIZE; ++i)
    {
        printf("%d", bs->data[i]);
        if (i != MAX_SIZE - 1)
        {
            printf(", ");
        }
    }
    printf("] bottom\n");
    return BS_OK;
}

/* ==================== 高级操作 ==================== */

BSStatus BS_ReverseStack1(BothStack *bs)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    int left = 0;
    int right = bs->top1;
    while (left < right)
    {
        ElemType tmp = bs->data[left];
        bs->data[left] = bs->data[right];
        bs->data[right] = tmp;
        ++left;
        --right;
    }
    return BS_OK;
}

BSStatus BS_ReverseStack2(BothStack *bs)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    /* 栈 2 有效区间为 [top2, MAX_SIZE-1] */
    int left = bs->top2;
    int right = MAX_SIZE - 1;
    while (left < right)
    {
        ElemType tmp = bs->data[left];
        bs->data[left] = bs->data[right];
        bs->data[right] = tmp;
        ++left;
        --right;
    }
    return BS_OK;
}

BSStatus BS_TransferOne(BothStack *bs, int dir)
{
    CHECK_STACK(bs, BS_ERR_INVALID);
    if (dir != STACK_1 && dir != STACK_2)
    {
        return BS_ERR_INVALID;
    }

    /* dir == 1：栈1 → 栈2；dir == 2：栈2 → 栈1 */
    int src = dir;
    int dst = (dir == STACK_1) ? STACK_2 : STACK_1;

    if (BS_IsEmpty(bs, src))
    {
        return BS_ERR_EMPTY;
    }
    if (BS_IsFull(bs))
    {
        return BS_ERR_FULL;
    }

    ElemType val;
    BS_Pop(bs, src, &val);
    BS_Push(bs, dst, val);
    return BS_OK;
}
