/**
 * @file    StaticList.c
 * @brief   静态顺序表接口实现
 * @author  aatroxfans
 * @date    2026-10-13
 */

#include "StaticList.h"

#include <stdio.h>
#include <string.h>

/* ==================== 内部辅助宏 ==================== */

/** @brief 参数有效性检查，失败返回指定状态码 */

#define CHECK_LIST(list, ret)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((list) == NULL)                                                                                            \
        {                                                                                                              \
            return (ret);                                                                                              \
        }                                                                                                              \
    } while (0)
/** @brief 下标范围检查 [0, upper]，失败返回指定状态码 */
#define CHECK_INDEX(index, upper, ret)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((index) < 0 || (index) > (upper))                                                                          \
        {                                                                                                              \
            return (ret);                                                                                              \
        }                                                                                                              \
    } while (0)

/* ==================== 生命周期 ==================== */

SLStatus SL_Init(StaticList *list)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    memset(list->data, 0, sizeof(list->data));
    list->length = 0;
    return SL_OK;
}

SLStatus SL_Clear(StaticList *list)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    list->length = 0;
    return SL_OK;
}

SLStatus SL_Destroy(StaticList *list)
{
    /* 静态存储，无需释放，语义上等价于 Clear */
    return SL_Clear(list);
}

/* ==================== 容量与状态 ==================== */

int SL_Length(const StaticList *list)
{
    CHECK_LIST(list, -1);
    return list->length;
}

int SL_Capacity(const StaticList *list)
{
    CHECK_LIST(list, -1);
    return MAX_SIZE;
}

bool SL_IsEmpty(const StaticList *list)
{
    if (list == NULL)
    {
        return false;
    }
    return list->length == 0;
}

bool SL_IsFull(const StaticList *list)
{
    if (list == NULL)
    {
        return false;
    }
    return list->length >= MAX_SIZE;
}

/* ==================== 查找 ==================== */

SLStatus SL_GetElem(const StaticList *list, int index, ElemType *out)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (out == NULL)
    {
        return SL_ERR_INVALID;
    }
    CHECK_INDEX(index, list->length - 1, SL_ERR_RANGE);
    *out = list->data[index];
    return SL_OK;
}

int SL_LocateElem(const StaticList *list, ElemType elem)
{
    CHECK_LIST(list, -1);
    for (int i = 0; i < list->length; ++i)
    {
        if (list->data[i] == elem)
        {
            return i;
        }
    }
    return -1;
}

/* ==================== 插入与删除 ==================== */

SLStatus SL_Insert(StaticList *list, int index, ElemType elem)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (SL_IsFull(list))
    {
        return SL_ERR_FULL;
    }
    /* 插入位置允许为 length，表示追加到表尾 */
    CHECK_INDEX(index, list->length, SL_ERR_RANGE);

    /* 从后向前搬移，为 elem 腾出位置 */
    for (int i = list->length; i > index; --i)
    {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = elem;
    ++list->length;
    return SL_OK;
}

SLStatus SL_PushBack(StaticList *list, ElemType elem)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (SL_IsFull(list))
    {
        return SL_ERR_FULL;
    }
    list->data[list->length] = elem;
    ++list->length;
    return SL_OK;
}

SLStatus SL_DeleteAt(StaticList *list, int index, ElemType *out)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (SL_IsEmpty(list))
    {
        return SL_ERR_EMPTY;
    }
    CHECK_INDEX(index, list->length - 1, SL_ERR_RANGE);

    if (out != NULL)
    {
        *out = list->data[index];
    }
    /* 从前向后搬移，覆盖被删元素 */
    for (int i = index; i < list->length - 1; ++i)
    {
        list->data[i] = list->data[i + 1];
    }
    --list->length;
    return SL_OK;
}

SLStatus SL_RemoveElem(StaticList *list, ElemType elem)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (SL_IsEmpty(list))
    {
        return SL_ERR_EMPTY;
    }
    int pos = SL_LocateElem(list, elem);
    if (pos < 0)
    {
        return SL_ERR_RANGE;
    }
    return SL_DeleteAt(list, pos, NULL);
}

SLStatus SL_PopBack(StaticList *list, ElemType *out)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (SL_IsEmpty(list))
    {
        return SL_ERR_EMPTY;
    }
    if (out != NULL)
    {
        *out = list->data[list->length - 1];
    }
    --list->length;
    return SL_OK;
}

/* ==================== 遍历与显示 ==================== */

SLStatus SL_Traverse(const StaticList *list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_LIST(list, SL_ERR_INVALID);
    if (callback == NULL)
    {
        return SL_ERR_INVALID;
    }
    for (int i = 0; i < list->length; ++i)
    {
        if (!callback(list->data[i], i, ctx))
        {
            break;
        }
    }
    return SL_OK;
}

SLStatus SL_Print(const StaticList *list)
{
    CHECK_LIST(list, SL_ERR_INVALID);

    printf("StaticList(len=%d, cap=%d): [", list->length, MAX_SIZE);
    for (int i = 0; i < list->length; ++i)
    {
        printf("%d", list->data[i]);
        if (i != list->length - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    return SL_OK;
}

/* ==================== 高级操作 ==================== */

SLStatus SL_Reverse(StaticList *list)
{
    CHECK_LIST(list, SL_ERR_INVALID);

    int left = 0;
    int right = list->length - 1;
    while (left < right)
    {
        ElemType tmp = list->data[left];
        list->data[left] = list->data[right];
        list->data[right] = tmp;
        ++left;
        --right;
    }
    return SL_OK;
}

int SL_RemoveAll(StaticList *list, ElemType elem)
{
    CHECK_LIST(list, -1);

    int write = 0;
    int removed = 0;
    for (int read = 0; read < list->length; ++read)
    {
        if (list->data[read] != elem)
        {
            list->data[write++] = list->data[read];
        }
        else
        {
            ++removed;
        }
    }
    list->length = write;
    return removed;
}

int SL_UniqueSorted(StaticList *list)
{
    CHECK_LIST(list, -1);

    if (list->length <= 1)
    {
        return 0;
    }

    int write = 1;
    for (int read = 1; read < list->length; ++read)
    {
        if (list->data[read] != list->data[write - 1])
        {
            list->data[write++] = list->data[read];
        }
    }
    int removed = list->length - write;
    list->length = write;
    return removed;
}

SLStatus SL_MergeSorted(const StaticList *a, const StaticList *b, StaticList *out)
{
    CHECK_LIST(a, SL_ERR_INVALID);
    CHECK_LIST(b, SL_ERR_INVALID);
    CHECK_LIST(out, SL_ERR_INVALID);

    if (a->length + b->length > MAX_SIZE)
    {
        return SL_ERR_FULL;
    }

    int i = 0;
    int j = 0;
    int k = 0;
    while (i < a->length && j < b->length)
    {
        if (a->data[i] <= b->data[j])
        {
            out->data[k++] = a->data[i++];
        }
        else
        {
            out->data[k++] = b->data[j++];
        }
    }
    while (i < a->length)
    {
        out->data[k++] = a->data[i++];
    }
    while (j < b->length)
    {
        out->data[k++] = b->data[j++];
    }
    out->length = k;
    return SL_OK;
}
