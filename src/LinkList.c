/**
 * @file    LinkList.c
 * @brief   带头结点的单链表接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>

/* ==================== 内部辅助宏 ==================== */

/** @brief 参数有效性检查（头指针非空且头结点存在） */
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

/**
 * @brief 内部函数：创建新结点
 * @param  elem 结点数据
 * @return 新结点指针；失败返回 NULL
 */
static LNode *LL_NewNode(ElemType elem)
{
    LNode *node = (LNode *)malloc(sizeof(LNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = elem;
    node->next = NULL;
    return node;
}

/* ==================== 生命周期 ==================== */

LLStatus LL_Init(LinkList *list)
{
    if (list == NULL)
    {
        return LL_ERR_INVALID;
    }
    /* 头结点不存数据 */
    LNode *head = (LNode *)malloc(sizeof(LNode));
    if (head == NULL)
    {
        *list = NULL;
        return LL_ERR_NOMEM;
    }
    head->data = 0;
    head->next = NULL;
    *list = head;
    return LL_OK;
}

LLStatus LL_Clear(LinkList list)
{
    CHECK_LIST(list, LL_ERR_INVALID);

    LNode *cur = list->next;
    while (cur != NULL)
    {
        LNode *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    list->next = NULL;
    return LL_OK;
}

LLStatus LL_Destroy(LinkList *list)
{
    if (list == NULL || *list == NULL)
    {
        return LL_ERR_INVALID;
    }
    LL_Clear(*list);
    free(*list);
    *list = NULL;
    return LL_OK;
}

/* ==================== 容量与状态 ==================== */

int LL_Length(LinkList list)
{
    if (list == NULL)
    {
        return -1;
    }
    int len = 0;
    LNode *cur = list->next;
    while (cur != NULL)
    {
        ++len;
        cur = cur->next;
    }
    return len;
}

bool LL_IsEmpty(LinkList list)
{
    if (list == NULL)
    {
        return false;
    }
    return list->next == NULL;
}

/* ==================== 查找 ==================== */

LNode *LL_GetNode(LinkList list, int index)
{
    if (list == NULL || index < 0)
    {
        return NULL;
    }
    LNode *cur = list->next;
    int i = 0;
    while (cur != NULL && i < index)
    {
        cur = cur->next;
        ++i;
    }
    return cur;
}

LLStatus LL_GetElem(LinkList list, int index, ElemType *out)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    if (out == NULL)
    {
        return LL_ERR_INVALID;
    }
    LNode *node = LL_GetNode(list, index);
    if (node == NULL)
    {
        return LL_ERR_RANGE;
    }
    *out = node->data;
    return LL_OK;
}

LNode *LL_LocateNode(LinkList list, ElemType elem)
{
    if (list == NULL)
    {
        return NULL;
    }
    LNode *cur = list->next;
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

int LL_LocateElem(LinkList list, ElemType elem)
{
    if (list == NULL)
    {
        return -1;
    }
    LNode *cur = list->next;
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

LLStatus LL_InsertHead(LinkList list, ElemType elem)
{
    CHECK_LIST(list, LL_ERR_INVALID);

    LNode *node = LL_NewNode(elem);
    if (node == NULL)
    {
        return LL_ERR_NOMEM;
    }
    /* 头插：node 插入到头结点之后 */
    node->next = list->next;
    list->next = node;
    return LL_OK;
}

LLStatus LL_PushBack(LinkList list, ElemType elem)
{
    CHECK_LIST(list, LL_ERR_INVALID);

    LNode *node = LL_NewNode(elem);
    if (node == NULL)
    {
        return LL_ERR_NOMEM;
    }
    /* 尾插：遍历找到尾结点 */
    LNode *cur = list;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = node;
    return LL_OK;
}

LLStatus LL_InsertAt(LinkList list, int index, ElemType elem)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    /* 允许 index == length，表示尾插 */
    CHECK_INDEX(index, LL_Length(list), LL_ERR_RANGE);

    LNode *node = LL_NewNode(elem);
    if (node == NULL)
    {
        return LL_ERR_NOMEM;
    }
    /* 定位到 index 的前驱 */
    LNode *prev = list;
    for (int i = 0; i < index; ++i)
    {
        prev = prev->next;
    }
    node->next = prev->next;
    prev->next = node;
    return LL_OK;
}

LLStatus LL_InsertAfter(LNode *node, ElemType elem)
{
    if (node == NULL)
    {
        return LL_ERR_INVALID;
    }
    LNode *newNode = LL_NewNode(elem);
    if (newNode == NULL)
    {
        return LL_ERR_NOMEM;
    }
    newNode->next = node->next;
    node->next = newNode;
    return LL_OK;
}

LLStatus LL_InsertBefore(LinkList list, LNode *node, ElemType elem)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    if (node == NULL)
    {
        return LL_ERR_INVALID;
    }
    /* 定位 node 的前驱 */
    LNode *prev = list;
    while (prev != NULL && prev->next != node)
    {
        prev = prev->next;
    }
    if (prev == NULL)
    {
        return LL_ERR_RANGE; /* node 不在链表中 */
    }
    LNode *newNode = LL_NewNode(elem);
    if (newNode == NULL)
    {
        return LL_ERR_NOMEM;
    }
    newNode->next = node;
    prev->next = newNode;
    return LL_OK;
}

/* ==================== 删除 ==================== */

LLStatus LL_DeleteAt(LinkList list, int index, ElemType *out)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    if (list->next == NULL)
    {
        return LL_ERR_EMPTY;
    }

    int len = LL_Length(list);
    CHECK_INDEX(index, len - 1, LL_ERR_RANGE);

    /* 定位到 index 的前驱 */
    LNode *prev = list;
    for (int i = 0; i < index; ++i)
    {
        prev = prev->next;
    }
    LNode *target = prev->next;
    if (out != NULL)
    {
        *out = target->data;
    }
    prev->next = target->next;
    free(target);
    return LL_OK;
}

LLStatus LL_RemoveElem(LinkList list, ElemType elem)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    if (list->next == NULL)
    {
        return LL_ERR_EMPTY;
    }
    /* prev 为删除结点的前驱 */
    LNode *prev = list;
    while (prev->next != NULL)
    {
        if (prev->next->data == elem)
        {
            LNode *target = prev->next;
            prev->next = target->next;
            free(target);
            return LL_OK;
        }
        prev = prev->next;
    }
    return LL_ERR_RANGE;
}

LLStatus LL_PopFront(LinkList list, ElemType *out)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    return LL_DeleteAt(list, 0, out);
}

LLStatus LL_PopBack(LinkList list, ElemType *out)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    if (list->next == NULL)
    {
        return LL_ERR_EMPTY;
    }
    /* 定位尾结点的前驱 */
    LNode *prev = list;
    while (prev->next != NULL && prev->next->next != NULL)
    {
        prev = prev->next;
    }
    LNode *target = prev->next;
    if (out != NULL)
    {
        *out = target->data;
    }
    prev->next = NULL;
    free(target);
    return LL_OK;
}

/* ==================== 建表 ==================== */

LLStatus LL_CreateHead(LinkList *list, const ElemType *arr, int n)
{
    if (list == NULL)
    {
        return LL_ERR_INVALID;
    }
    if (arr == NULL && n > 0)
    {
        return LL_ERR_INVALID;
    }

    LLStatus st = LL_Init(list);
    if (st != LL_OK)
    {
        return st;
    }
    /* 头插法：依次插入到头部，结果与数组顺序相反 */
    for (int i = 0; i < n; ++i)
    {
        st = LL_InsertHead(*list, arr[i]);
        if (st != LL_OK)
        {
            LL_Destroy(list);
            return st;
        }
    }
    return LL_OK;
}

LLStatus LL_CreateTail(LinkList *list, const ElemType *arr, int n)
{
    if (list == NULL)
    {
        return LL_ERR_INVALID;
    }
    if (arr == NULL && n > 0)
    {
        return LL_ERR_INVALID;
    }

    LLStatus st = LL_Init(list);
    if (st != LL_OK)
    {
        return st;
    }
    /* 尾插法：维护尾指针，O(1) 追加，结果与数组顺序一致 */
    LNode *tail = *list;
    for (int i = 0; i < n; ++i)
    {
        LNode *node = LL_NewNode(arr[i]);
        if (node == NULL)
        {
            LL_Destroy(list);
            return LL_ERR_NOMEM;
        }
        tail->next = node;
        tail = node;
    }
    return LL_OK;
}

/* ==================== 遍历与显示 ==================== */

LLStatus LL_Traverse(LinkList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_LIST(list, LL_ERR_INVALID);
    if (callback == NULL)
    {
        return LL_ERR_INVALID;
    }
    LNode *cur = list->next;
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
    return LL_OK;
}

LLStatus LL_Print(LinkList list)
{
    CHECK_LIST(list, LL_ERR_INVALID);

    printf("LinkList(len=%d): [", LL_Length(list));
    LNode *cur = list->next;
    while (cur != NULL)
    {
        printf("%d", cur->data);
        if (cur->next != NULL)
        {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("]\n");
    return LL_OK;
}

/* ==================== 高级操作 ==================== */

LLStatus LL_Reverse(LinkList list)
{
    CHECK_LIST(list, LL_ERR_INVALID);

    LNode *prev = NULL;
    LNode *cur = list->next;
    while (cur != NULL)
    {
        LNode *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    list->next = prev;
    return LL_OK;
}

int LL_RemoveAll(LinkList list, ElemType elem)
{
    if (list == NULL)
    {
        return -1;
    }
    int removed = 0;
    LNode *prev = list;
    while (prev->next != NULL)
    {
        if (prev->next->data == elem)
        {
            LNode *target = prev->next;
            prev->next = target->next;
            free(target);
            ++removed;
        }
        else
        {
            prev = prev->next;
        }
    }
    return removed;
}

int LL_UniqueSorted(LinkList list)
{
    if (list == NULL)
    {
        return -1;
    }
    int removed = 0;
    LNode *cur = list->next;
    while (cur != NULL && cur->next != NULL)
    {
        if (cur->data == cur->next->data)
        {
            LNode *dup = cur->next;
            cur->next = dup->next;
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

LLStatus LL_MergeSorted(LinkList a, LinkList b, LinkList *out)
{
    CHECK_LIST(a, LL_ERR_INVALID);
    CHECK_LIST(b, LL_ERR_INVALID);
    if (out == NULL)
    {
        return LL_ERR_INVALID;
    }

    LLStatus st = LL_Init(out);
    if (st != LL_OK)
    {
        return st;
    }

    LNode *pa = a->next;
    LNode *pb = b->next;
    LNode *tail = *out;

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
        LNode *node = LL_NewNode(val);
        if (node == NULL)
        {
            LL_Destroy(out);
            return LL_ERR_NOMEM;
        }
        tail->next = node;
        tail = node;
    }
    while (pa != NULL)
    {
        LNode *node = LL_NewNode(pa->data);
        if (node == NULL)
        {
            LL_Destroy(out);
            return LL_ERR_NOMEM;
        }
        tail->next = node;
        tail = node;
        pa = pa->next;
    }
    while (pb != NULL)
    {
        LNode *node = LL_NewNode(pb->data);
        if (node == NULL)
        {
            LL_Destroy(out);
            return LL_ERR_NOMEM;
        }
        tail->next = node;
        tail = node;
        pb = pb->next;
    }
    return LL_OK;
}

LNode *LL_MiddleNode(LinkList list)
{
    if (list == NULL || list->next == NULL)
    {
        return NULL;
    }
    LNode *slow = list->next;
    LNode *fast = list->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool LL_HasCycle(LinkList list)
{
    if (list == NULL)
    {
        return false;
    }
    LNode *slow = list->next;
    LNode *fast = list->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return true;
        }
    }
    return false;
}
