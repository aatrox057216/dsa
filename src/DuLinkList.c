/**
 * @file    DuLinkList.c
 * @brief   带头结点的双向链表接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "DuLinkList.h"
#include <stdio.h>
#include <stdlib.h>

/* ==================== 内部辅助 ==================== */

/** @brief 参数有效性检查 */
#define CHECK_LIST(list, ret)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((list) == NULL)                                                                                            \
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

/**
 * @brief 内部函数：创建新结点
 * @param  elem 结点数据
 * @return 新结点指针；失败返回 NULL
 * @note   prior 与 next 均初始化为 NULL
 */
static DuLNode *DL_NewNode(ElemType elem)
{
    DuLNode *node = (DuLNode *)malloc(sizeof(DuLNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = elem;
    node->prior = NULL;
    node->next = NULL;
    return node;
}

/**
 * @brief 内部函数：定位尾结点
 * @param  list 链表头指针
 * @return 尾结点指针；空表返回头结点
 */
static DuLNode *DL_TailNode(DuLinkList list)
{
    DuLNode *cur = list;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    return cur;
}

/* ==================== 生命周期 ==================== */

DLStatus DL_Init(DuLinkList *list)
{
    if (list == NULL)
    {
        return DL_ERR_INVALID;
    }
    DuLNode *head = (DuLNode *)malloc(sizeof(DuLNode));
    if (head == NULL)
    {
        *list = NULL;
        return DL_ERR_NOMEM;
    }
    head->data = 0;
    head->prior = NULL;
    head->next = NULL;
    *list = head;
    return DL_OK;
}

DLStatus DL_Clear(DuLinkList list)
{
    CHECK_LIST(list, DL_ERR_INVALID);

    DuLNode *cur = list->next;
    while (cur != NULL)
    {
        DuLNode *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    list->next = NULL;
    return DL_OK;
}

DLStatus DL_Destroy(DuLinkList *list)
{
    if (list == NULL || *list == NULL)
    {
        return DL_ERR_INVALID;
    }
    DL_Clear(*list);
    free(*list);
    *list = NULL;
    return DL_OK;
}

/* ==================== 容量与状态 ==================== */

int DL_Length(DuLinkList list)
{
    if (list == NULL)
    {
        return -1;
    }
    int len = 0;
    DuLNode *cur = list->next;
    while (cur != NULL)
    {
        ++len;
        cur = cur->next;
    }
    return len;
}

bool DL_IsEmpty(DuLinkList list)
{
    if (list == NULL)
    {
        return false;
    }
    return list->next == NULL;
}

/* ==================== 查找 ==================== */

DuLNode *DL_GetNode(DuLinkList list, int index)
{
    if (list == NULL || index < 0)
    {
        return NULL;
    }
    int len = DL_Length(list);
    if (index >= len)
    {
        return NULL;
    }

    /* 优化：前半段从头走，后半段从尾走 */
    if (index < len / 2)
    {
        DuLNode *cur = list->next;
        for (int i = 0; i < index; ++i)
        {
            cur = cur->next;
        }
        return cur;
    }
    DuLNode *cur = DL_TailNode(list);
    for (int i = len - 1; i > index; --i)
    {
        cur = cur->prior;
    }
    return cur;
}

DLStatus DL_GetElem(DuLinkList list, int index, ElemType *out)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (out == NULL)
    {
        return DL_ERR_INVALID;
    }
    DuLNode *node = DL_GetNode(list, index);
    if (node == NULL)
    {
        return DL_ERR_RANGE;
    }
    *out = node->data;
    return DL_OK;
}

DuLNode *DL_LocateNode(DuLinkList list, ElemType elem)
{
    if (list == NULL)
    {
        return NULL;
    }
    DuLNode *cur = list->next;
    while (cur != NULL)
    {
        if (cur->data == elem)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int DL_LocateElem(DuLinkList list, ElemType elem)
{
    if (list == NULL)
    {
        return -1;
    }
    DuLNode *cur = list->next;
    int i = 0;
    while (cur != NULL)
    {
        if (cur->data == elem)
        {
            return i;
        }
        cur = cur->next;
        ++i;
    }
    return -1;
}

/* ==================== 插入 ==================== */

DLStatus DL_InsertHead(DuLinkList list, ElemType elem)
{
    CHECK_LIST(list, DL_ERR_INVALID);

    DuLNode *node = DL_NewNode(elem);
    if (node == NULL)
    {
        return DL_ERR_NOMEM;
    }
    /* 头插：node 插入到头结点之后 */
    node->prior = list;
    node->next = list->next;
    if (list->next != NULL)
    {
        list->next->prior = node;
    }
    list->next = node;
    return DL_OK;
}

DLStatus DL_PushBack(DuLinkList list, ElemType elem)
{
    CHECK_LIST(list, DL_ERR_INVALID);

    DuLNode *node = DL_NewNode(elem);
    if (node == NULL)
    {
        return DL_ERR_NOMEM;
    }
    /* 定位尾结点，尾结点 next 为 NULL */
    DuLNode *tail = DL_TailNode(list);
    tail->next = node;
    node->prior = tail;
    node->next = NULL;
    return DL_OK;
}

DLStatus DL_InsertAt(DuLinkList list, int index, ElemType elem)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    CHECK_INDEX(index, DL_Length(list), DL_ERR_RANGE);

    DuLNode *node = DL_NewNode(elem);
    if (node == NULL)
    {
        return DL_ERR_NOMEM;
    }
    /* 定位到 index 的前驱 */
    DuLNode *prev = list;
    for (int i = 0; i < index; ++i)
    {
        prev = prev->next;
    }
    /* 在 prev 之后插入 node */
    node->prior = prev;
    node->next = prev->next;
    if (prev->next != NULL)
    {
        prev->next->prior = node;
    }
    prev->next = node;
    return DL_OK;
}

DLStatus DL_InsertAfter(DuLNode *node, ElemType elem)
{
    if (node == NULL)
    {
        return DL_ERR_INVALID;
    }
    DuLNode *newNode = DL_NewNode(elem);
    if (newNode == NULL)
    {
        return DL_ERR_NOMEM;
    }
    /* 在 node 之后插入 newNode */
    newNode->prior = node;
    newNode->next = node->next;
    if (node->next != NULL)
    {
        node->next->prior = newNode;
    }
    node->next = newNode;
    return DL_OK;
}

DLStatus DL_InsertBefore(DuLNode *node, ElemType elem)
{
    if (node == NULL)
    {
        return DL_ERR_INVALID;
    }
    DuLNode *newNode = DL_NewNode(elem);
    if (newNode == NULL)
    {
        return DL_ERR_NOMEM;
    }
    /* 在 node 之前插入 newNode：借助 node->prior 实现 O(1) */
    newNode->next = node;
    newNode->prior = node->prior;
    if (node->prior != NULL)
    {
        node->prior->next = newNode;
    }
    node->prior = newNode;
    return DL_OK;
}

/* ==================== 删除 ==================== */

DLStatus DL_DeleteAt(DuLinkList list, int index, ElemType *out)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (list->next == NULL)
    {
        return DL_ERR_EMPTY;
    }

    int len = DL_Length(list);
    CHECK_INDEX(index, len - 1, DL_ERR_RANGE);

    /* 定位到 index 的前驱 */
    DuLNode *prev = list;
    for (int i = 0; i < index; ++i)
    {
        prev = prev->next;
    }
    DuLNode *target = prev->next;
    if (out != NULL)
    {
        *out = target->data;
    }
    /* 摘除 target */
    prev->next = target->next;
    if (target->next != NULL)
    {
        target->next->prior = prev;
    }
    free(target);
    return DL_OK;
}

DLStatus DL_DeleteNode(DuLNode *node, ElemType *out)
{
    if (node == NULL || node->prior == NULL)
    {
        /* node->prior == NULL 说明是头结点或非法结点 */
        return DL_ERR_INVALID;
    }
    if (out != NULL)
    {
        *out = node->data;
    }
    /* O(1) 摘除：借助 prior 与 next 双向连接 */
    node->prior->next = node->next;
    if (node->next != NULL)
    {
        node->next->prior = node->prior;
    }
    free(node);
    return DL_OK;
}

DLStatus DL_RemoveElem(DuLinkList list, ElemType elem)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (list->next == NULL)
    {
        return DL_ERR_EMPTY;
    }
    DuLNode *cur = list->next;
    while (cur != NULL)
    {
        if (cur->data == elem)
        {
            return DL_DeleteNode(cur, NULL);
        }
        cur = cur->next;
    }
    return DL_ERR_RANGE;
}

DLStatus DL_PopFront(DuLinkList list, ElemType *out)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (list->next == NULL)
    {
        return DL_ERR_EMPTY;
    }
    return DL_DeleteNode(list->next, out);
}

DLStatus DL_PopBack(DuLinkList list, ElemType *out)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (list->next == NULL)
    {
        return DL_ERR_EMPTY;
    }
    DuLNode *tail = DL_TailNode(list);
    return DL_DeleteNode(tail, out);
}

/* ==================== 建表 ==================== */

DLStatus DL_CreateHead(DuLinkList *list, const ElemType *arr, int n)
{
    if (list == NULL)
    {
        return DL_ERR_INVALID;
    }
    if (arr == NULL && n > 0)
    {
        return DL_ERR_INVALID;
    }

    DLStatus st = DL_Init(list);
    if (st != DL_OK)
    {
        return st;
    }
    /* 头插法：结果与数组顺序相反 */
    for (int i = 0; i < n; ++i)
    {
        st = DL_InsertHead(*list, arr[i]);
        if (st != DL_OK)
        {
            DL_Destroy(list);
            return st;
        }
    }
    return DL_OK;
}

DLStatus DL_CreateTail(DuLinkList *list, const ElemType *arr, int n)
{
    if (list == NULL)
    {
        return DL_ERR_INVALID;
    }
    if (arr == NULL && n > 0)
    {
        return DL_ERR_INVALID;
    }

    DLStatus st = DL_Init(list);
    if (st != DL_OK)
    {
        return st;
    }
    /* 尾插法：维护尾指针，O(n) 建表 */
    DuLNode *tail = *list;
    for (int i = 0; i < n; ++i)
    {
        DuLNode *node = DL_NewNode(arr[i]);
        if (node == NULL)
        {
            DL_Destroy(list);
            return DL_ERR_NOMEM;
        }
        tail->next = node;
        node->prior = tail;
        tail = node;
    }
    return DL_OK;
}

/* ==================== 遍历与显示 ==================== */

DLStatus DL_TraverseForward(DuLinkList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (callback == NULL)
    {
        return DL_ERR_INVALID;
    }
    DuLNode *cur = list->next;
    int i = 0;
    while (cur != NULL)
    {
        if (!callback(cur->data, i, ctx))
        {
            break;
        }
        cur = cur->next;
        ++i;
    }
    return DL_OK;
}

DLStatus DL_TraverseBackward(DuLinkList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_LIST(list, DL_ERR_INVALID);
    if (callback == NULL)
    {
        return DL_ERR_INVALID;
    }
    if (list->next == NULL)
    {
        return DL_OK;
    }
    DuLNode *cur = DL_TailNode(list);
    int i = 0;
    while (cur != list)
    {
        if (!callback(cur->data, i, ctx))
        {
            break;
        }
        cur = cur->prior;
        ++i;
    }
    return DL_OK;
}

DLStatus DL_Print(DuLinkList list)
{
    CHECK_LIST(list, DL_ERR_INVALID);

    printf("DuLinkList(len=%d): NULL <- [head] <-> ", DL_Length(list));
    DuLNode *cur = list->next;
    while (cur != NULL)
    {
        printf("%d", cur->data);
        if (cur->next != NULL)
        {
            printf(" <-> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
    return DL_OK;
}

DLStatus DL_PrintReverse(DuLinkList list)
{
    CHECK_LIST(list, DL_ERR_INVALID);

    printf("DuLinkList(反向, len=%d): NULL <- ", DL_Length(list));
    if (list->next == NULL)
    {
        printf("[head] -> NULL\n");
        return DL_OK;
    }
    DuLNode *cur = DL_TailNode(list);
    while (cur != list)
    {
        printf("%d", cur->data);
        if (cur->prior != list)
        {
            printf(" <-> ");
        }
        cur = cur->prior;
    }
    printf(" <-> [head] -> NULL\n");
    return DL_OK;
}

/* ==================== 高级操作 ==================== */

DLStatus DL_Reverse(DuLinkList list)
{
    CHECK_LIST(list, DL_ERR_INVALID);

    if (list->next == NULL || list->next->next == NULL)
    {
        /* 空表或单元素，无需反转 */
        return DL_OK;
    }

    /* 交换每个数据结点的 prior 与 next */
    DuLNode *cur = list->next;
    DuLNode *newHead = NULL;
    while (cur != NULL)
    {
        DuLNode *nxt = cur->next;
        /* 交换 prior 与 next */
        cur->prior = nxt;
        cur->next = newHead == NULL ? NULL : newHead;
        /* 修正 next 的 prior */
        if (cur->next != NULL)
        {
            cur->next->prior = cur;
        }
        newHead = cur;
        cur = nxt;
    }
    /* newHead 为原尾结点，成为新首结点 */
    list->next = newHead;
    if (newHead != NULL)
    {
        newHead->prior = list;
    }
    return DL_OK;
}

int DL_RemoveAll(DuLinkList list, ElemType elem)
{
    if (list == NULL)
    {
        return -1;
    }
    int removed = 0;
    DuLNode *cur = list->next;
    while (cur != NULL)
    {
        DuLNode *nxt = cur->next;
        if (cur->data == elem)
        {
            /* 就地摘除，复用 DeleteNode 逻辑 */
            cur->prior->next = cur->next;
            if (cur->next != NULL)
            {
                cur->next->prior = cur->prior;
            }
            free(cur);
            ++removed;
        }
        cur = nxt;
    }
    return removed;
}

int DL_UniqueSorted(DuLinkList list)
{
    if (list == NULL)
    {
        return -1;
    }
    if (list->next == NULL || list->next->next == NULL)
    {
        return 0;
    }
    int removed = 0;
    DuLNode *cur = list->next;
    while (cur != NULL && cur->next != NULL)
    {
        if (cur->data == cur->next->data)
        {
            DuLNode *dup = cur->next;
            cur->next = dup->next;
            if (dup->next != NULL)
            {
                dup->next->prior = cur;
            }
            free(dup);
            ++removed;
        }
        else
        {
            cur = cur->next;
        }
    }
    return removed;
}

DLStatus DL_MergeSorted(DuLinkList a, DuLinkList b, DuLinkList *out)
{
    CHECK_LIST(a, DL_ERR_INVALID);
    CHECK_LIST(b, DL_ERR_INVALID);
    if (out == NULL)
    {
        return DL_ERR_INVALID;
    }

    DLStatus st = DL_Init(out);
    if (st != DL_OK)
    {
        return st;
    }

    DuLNode *pa = a->next;
    DuLNode *pb = b->next;
    DuLNode *tail = *out;

    while (pa != NULL && pb != NULL)
    {
        ElemType val;
        if (pa->data <= pb->data)
        {
            val = pa->data;
            pa = pa->next;
        }
        else
        {
            val = pb->data;
            pb = pb->next;
        }
        DuLNode *node = DL_NewNode(val);
        if (node == NULL)
        {
            DL_Destroy(out);
            return DL_ERR_NOMEM;
        }
        tail->next = node;
        node->prior = tail;
        tail = node;
    }
    while (pa != NULL)
    {
        DuLNode *node = DL_NewNode(pa->data);
        if (node == NULL)
        {
            DL_Destroy(out);
            return DL_ERR_NOMEM;
        }
        tail->next = node;
        node->prior = tail;
        tail = node;
        pa = pa->next;
    }
    while (pb != NULL)
    {
        DuLNode *node = DL_NewNode(pb->data);
        if (node == NULL)
        {
            DL_Destroy(out);
            return DL_ERR_NOMEM;
        }
        tail->next = node;
        node->prior = tail;
        tail = node;
        pb = pb->next;
    }
    return DL_OK;
}
