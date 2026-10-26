/**
 * @file    SqList.c
 * @brief   动态顺序表接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "SqList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== 内部辅助宏 ==================== */

/** @brief 参数有效性检查，失败返回指定状态码 */
#define CHECK_LIST(list, ret)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((list) == NULL || (list)->elem == NULL)                                                                    \
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

SqStatus Sq_Init(SqList *list)
{
    if (list == NULL)
    {
        return SQ_ERR_INVALID;
    }
    list->elem = (ElemType *)malloc(sizeof(ElemType) * SQ_LIST_INIT_SIZE);
    if (list->elem == NULL)
    {
        list->length = 0;
        list->listsize = 0;
        return SQ_ERR_NOMEM;
    }
    list->length = 0;
    list->listsize = SQ_LIST_INIT_SIZE;
    return SQ_OK;
}

SqStatus Sq_Clear(SqList *list)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    list->length = 0;
    return SQ_OK;
}

SqStatus Sq_Destroy(SqList *list)
{
    if (list == NULL)
    {
        return SQ_ERR_INVALID;
    }
    if (list->elem != NULL)
    {
        free(list->elem);
        list->elem = NULL;
    }
    list->length = 0;
    list->listsize = 0;
    return SQ_OK;
}

/* ==================== 容量与状态 ==================== */

int Sq_Length(const SqList *list)
{
    if (list == NULL || list->elem == NULL)
    {
        return -1;
    }
    return list->length;
}

int Sq_Capacity(const SqList *list)
{
    if (list == NULL || list->elem == NULL)
    {
        return -1;
    }
    return list->listsize;
}

bool Sq_IsEmpty(const SqList *list)
{
    if (list == NULL || list->elem == NULL)
    {
        return false;
    }
    return list->length == 0;
}

bool Sq_IsFull(const SqList *list)
{
    if (list == NULL || list->elem == NULL)
    {
        return false;
    }
    return list->length >= list->listsize;
}

SqStatus Sq_Reserve(SqList *list, int newSize)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (newSize < list->length)
    {
        return SQ_ERR_INVALID;
    }
    if (newSize == list->listsize)
    {
        return SQ_OK;
    }

    ElemType *newElem = (ElemType *)realloc(list->elem, sizeof(ElemType) * newSize);
    if (newElem == NULL)
    {
        return SQ_ERR_NOMEM;
    }
    list->elem = newElem;
    list->listsize = newSize;
    return SQ_OK;
}

SqStatus Sq_EnsureCapacity(SqList *list, int needSize)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (needSize <= list->listsize)
    {
        return SQ_OK;
    }

    /* 按增量扩容，直到容量足够 */
    int newSize = list->listsize;
    while (newSize < needSize)
    {
        newSize += SQ_LIST_INCREMENT;
    }
    return Sq_Reserve(list, newSize);
}

/* ==================== 查找 ==================== */

SqStatus Sq_GetElem(const SqList *list, int index, ElemType *out)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (out == NULL)
    {
        return SQ_ERR_INVALID;
    }
    CHECK_INDEX(index, list->length - 1, SQ_ERR_RANGE);
    *out = list->elem[index];
    return SQ_OK;
}

int Sq_LocateElem(const SqList *list, ElemType elem)
{
    if (list == NULL || list->elem == NULL)
    {
        return -1;
    }
    for (int i = 0; i < list->length; ++i)
    {
        if (list->elem[i] == elem)
        {
            return i;
        }
    }
    return -1;
}

/* ==================== 插入与删除 ==================== */

SqStatus Sq_Insert(SqList *list, int index, ElemType elem)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    /* 插入位置允许为 length，表示追加到表尾 */
    CHECK_INDEX(index, list->length, SQ_ERR_RANGE);

    /* 容量不足时自动扩容 */
    SqStatus st = Sq_EnsureCapacity(list, list->length + 1);
    if (st != SQ_OK)
    {
        return st;
    }

    /* 从后向前搬移，为 elem 腾出位置 */
    for (int i = list->length; i > index; --i)
    {
        list->elem[i] = list->elem[i - 1];
    }
    list->elem[index] = elem;
    ++list->length;
    return SQ_OK;
}

SqStatus Sq_PushBack(SqList *list, ElemType elem)
{
    return Sq_Insert(list, list != NULL ? list->length : 0, elem);
}

SqStatus Sq_DeleteAt(SqList *list, int index, ElemType *out)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (list->length == 0)
    {
        return SQ_ERR_EMPTY;
    }
    CHECK_INDEX(index, list->length - 1, SQ_ERR_RANGE);

    if (out != NULL)
    {
        *out = list->elem[index];
    }
    /* 从前向后搬移，覆盖被删元素 */
    for (int i = index; i < list->length - 1; ++i)
    {
        list->elem[i] = list->elem[i + 1];
    }
    --list->length;
    return SQ_OK;
}

SqStatus Sq_RemoveElem(SqList *list, ElemType elem)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (list->length == 0)
    {
        return SQ_ERR_EMPTY;
    }
    int pos = Sq_LocateElem(list, elem);
    if (pos < 0)
    {
        return SQ_ERR_RANGE;
    }
    return Sq_DeleteAt(list, pos, NULL);
}

SqStatus Sq_PopBack(SqList *list, ElemType *out)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (list->length == 0)
    {
        return SQ_ERR_EMPTY;
    }
    if (out != NULL)
    {
        *out = list->elem[list->length - 1];
    }
    --list->length;
    return SQ_OK;
}

/* ==================== 遍历与显示 ==================== */

SqStatus Sq_Traverse(const SqList *list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_LIST(list, SQ_ERR_INVALID);
    if (callback == NULL)
    {
        return SQ_ERR_INVALID;
    }
    for (int i = 0; i < list->length; ++i)
    {
        if (!callback(list->elem[i], i, ctx))
        {
            break;
        }
    }
    return SQ_OK;
}

SqStatus Sq_Print(const SqList *list)
{
    CHECK_LIST(list, SQ_ERR_INVALID);

    printf("SqList(len=%d, cap=%d): [", list->length, list->listsize);
    for (int i = 0; i < list->length; ++i)
    {
        printf("%d", list->elem[i]);
        if (i != list->length - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    return SQ_OK;
}

/* ==================== 高级操作 ==================== */

SqStatus Sq_Reverse(SqList *list)
{
    CHECK_LIST(list, SQ_ERR_INVALID);

    int left = 0;
    int right = list->length - 1;
    while (left < right)
    {
        ElemType tmp = list->elem[left];
        list->elem[left] = list->elem[right];
        list->elem[right] = tmp;
        ++left;
        --right;
    }
    return SQ_OK;
}

int Sq_RemoveAll(SqList *list, ElemType elem)
{
    if (list == NULL || list->elem == NULL)
    {
        return -1;
    }
    int write = 0;
    int removed = 0;
    for (int read = 0; read < list->length; ++read)
    {
        if (list->elem[read] != elem)
        {
            list->elem[write++] = list->elem[read];
        }
        else
        {
            ++removed;
        }
    }
    list->length = write;
    return removed;
}

int Sq_UniqueSorted(SqList *list)
{
    if (list == NULL || list->elem == NULL)
    {
        return -1;
    }
    if (list->length <= 1)
    {
        return 0;
    }

    int write = 1;
    for (int read = 1; read < list->length; ++read)
    {
        if (list->elem[read] != list->elem[write - 1])
        {
            list->elem[write++] = list->elem[read];
        }
    }
    int removed = list->length - write;
    list->length = write;
    return removed;
}

SqStatus Sq_MergeSorted(const SqList *a, const SqList *b, SqList *out)
{
    CHECK_LIST(a, SQ_ERR_INVALID);
    CHECK_LIST(b, SQ_ERR_INVALID);
    CHECK_LIST(out, SQ_ERR_INVALID);

    int needSize = a->length + b->length;
    SqStatus st = Sq_EnsureCapacity(out, needSize);
    if (st != SQ_OK)
    {
        return st;
    }

    int i = 0;
    int j = 0;
    int k = 0;
    while (i < a->length && j < b->length)
    {
        if (a->elem[i] <= b->elem[j])
        {
            out->elem[k++] = a->elem[i++];
        }
        else
        {
            out->elem[k++] = b->elem[j++];
        }
    }
    while (i < a->length)
    {
        out->elem[k++] = a->elem[i++];
    }
    while (j < b->length)
    {
        out->elem[k++] = b->elem[j++];
    }
    out->length = k;
    return SQ_OK;
}

SqStatus Sq_ShrinkToFit(SqList *list)
{
    CHECK_LIST(list, SQ_ERR_INVALID);

    if (list->length == list->listsize)
    {
        return SQ_OK;
    }
    /* 至少保留 1 个元素空间，避免 realloc(0) 行为不确定性 */
    int newSize = list->length > 0 ? list->length : 1;
    ElemType *newElem = (ElemType *)realloc(list->elem, sizeof(ElemType) * newSize);
    if (newElem == NULL)
    {
        return SQ_ERR_NOMEM;
    }
    list->elem = newElem;
    list->listsize = newSize;
    return SQ_OK;
}
