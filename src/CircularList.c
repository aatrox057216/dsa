/**
 * @file    CircularList.c
 * @brief   带头结点的循环单链表接口实现
 * @author  aatroxfans
 * @date    2024
 */

#include "CircularList.h"
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
 * @note   新结点 next 初始化为 NULL，由调用方决定指向
 */
static LNode *CL_NewNode(ElemType elem)
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

/**
 * @brief 内部函数：定位尾结点
 * @param  list 链表头指针
 * @return 尾结点指针；空表返回头结点
 */
static LNode *CL_TailNode(CircularList list)
{
    LNode *cur = list;
    while (cur->next != list)
    {
        cur = cur->next;
    }
    return cur;
}

/* ==================== 生命周期 ==================== */

CLStatus CL_Init(CircularList *list)
{
    if (list == NULL)
    {
        return CL_ERR_INVALID;
    }
    LNode *head = (LNode *)malloc(sizeof(LNode));
    if (head == NULL)
    {
        *list = NULL;
        return CL_ERR_NOMEM;
    }
    head->data = 0;
    /* 关键：头结点 next 指向自身，形成闭环 */
    head->next = head;
    *list = head;
    return CL_OK;
}

CLStatus CL_Clear(CircularList list)
{
    CHECK_LIST(list, CL_ERR_INVALID);

    LNode *cur = list->next;
    while (cur != list)
    {
        LNode *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    list->next = list;
    return CL_OK;
}

CLStatus CL_Destroy(CircularList *list)
{
    if (list == NULL || *list == NULL)
    {
        return CL_ERR_INVALID;
    }
    CL_Clear(*list);
    free(*list);
    *list = NULL;
    return CL_OK;
}

/* ==================== 容量与状态 ==================== */

int CL_Length(CircularList list)
{
    if (list == NULL)
    {
        return -1;
    }
    int len = 0;
    LNode *cur = list->next;
    while (cur != list)
    {
        ++len;
        cur = cur->next;
    }
    return len;
}

bool CL_IsEmpty(CircularList list)
{
    if (list == NULL)
    {
        return false;
    }
    return list->next == list;
}

/* ==================== 查找 ==================== */

LNode *CL_GetNode(CircularList list, int index)
{
    if (list == NULL || index < 0)
    {
        return NULL;
    }
    LNode *cur = list->next;
    int i = 0;
    while (cur != list && i < index)
    {
        cur = cur->next;
        ++i;
    }
    /* cur == list 表示 index 超过长度 */
    return (cur == list) ? NULL : cur;
}

CLStatus CL_GetElem(CircularList list, int index, ElemType *out)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    if (out == NULL)
    {
        return CL_ERR_INVALID;
    }
    LNode *node = CL_GetNode(list, index);
    if (node == NULL)
    {
        return CL_ERR_RANGE;
    }
    *out = node->data;
    return CL_OK;
}

LNode *CL_LocateNode(CircularList list, ElemType elem)
{
    if (list == NULL)
    {
        return NULL;
    }
    LNode *cur = list->next;
    while (cur != list)
    {
        if (cur->data == elem)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int CL_LocateElem(CircularList list, ElemType elem)
{
    if (list == NULL)
    {
        return -1;
    }
    LNode *cur = list->next;
    int i = 0;
    while (cur != list)
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

CLStatus CL_InsertHead(CircularList list, ElemType elem)
{
    CHECK_LIST(list, CL_ERR_INVALID);

    LNode *node = CL_NewNode(elem);
    if (node == NULL)
    {
        return CL_ERR_NOMEM;
    }
    /* 头插：node 插入到头结点之后 */
    node->next = list->next;
    list->next = node;
    return CL_OK;
}

CLStatus CL_PushBack(CircularList list, ElemType elem)
{
    CHECK_LIST(list, CL_ERR_INVALID);

    LNode *node = CL_NewNode(elem);
    if (node == NULL)
    {
        return CL_ERR_NOMEM;
    }
    /* 定位尾结点，尾结点 next 指向头结点 */
    LNode *tail = CL_TailNode(list);
    node->next = list; /* 新尾结点指向头结点，维持环 */
    tail->next = node;
    return CL_OK;
}

CLStatus CL_InsertAt(CircularList list, int index, ElemType elem)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    CHECK_INDEX(index, CL_Length(list), CL_ERR_RANGE);

    LNode *node = CL_NewNode(elem);
    if (node == NULL)
    {
        return CL_ERR_NOMEM;
    }
    /* 定位到 index 的前驱 */
    LNode *prev = list;
    for (int i = 0; i < index; ++i)
    {
        prev = prev->next;
    }
    node->next = prev->next;
    prev->next = node;
    return CL_OK;
}

CLStatus CL_InsertAfter(LNode *node, ElemType elem)
{
    if (node == NULL)
    {
        return CL_ERR_INVALID;
    }
    LNode *newNode = CL_NewNode(elem);
    if (newNode == NULL)
    {
        return CL_ERR_NOMEM;
    }
    newNode->next = node->next;
    node->next = newNode;
    return CL_OK;
}

/* ==================== 删除 ==================== */

CLStatus CL_DeleteAt(CircularList list, int index, ElemType *out)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    if (list->next == list)
    {
        return CL_ERR_EMPTY;
    }

    int len = CL_Length(list);
    CHECK_INDEX(index, len - 1, CL_ERR_RANGE);

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
    return CL_OK;
}

CLStatus CL_RemoveElem(CircularList list, ElemType elem)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    if (list->next == list)
    {
        return CL_ERR_EMPTY;
    }
    LNode *prev = list;
    while (prev->next != list)
    {
        if (prev->next->data == elem)
        {
            LNode *target = prev->next;
            prev->next = target->next;
            free(target);
            return CL_OK;
        }
        prev = prev->next;
    }
    return CL_ERR_RANGE;
}

CLStatus CL_PopFront(CircularList list, ElemType *out)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    return CL_DeleteAt(list, 0, out);
}

CLStatus CL_PopBack(CircularList list, ElemType *out)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    if (list->next == list)
    {
        return CL_ERR_EMPTY;
    }
    /* 定位尾结点的前驱 */
    LNode *prev = list;
    while (prev->next->next != list)
    {
        prev = prev->next;
    }
    LNode *target = prev->next;
    if (out != NULL)
    {
        *out = target->data;
    }
    prev->next = list; /* 前驱成为新尾结点，指向头结点 */
    free(target);
    return CL_OK;
}

/* ==================== 建表 ==================== */

CLStatus CL_CreateHead(CircularList *list, const ElemType *arr, int n)
{
    if (list == NULL)
    {
        return CL_ERR_INVALID;
    }
    if (arr == NULL && n > 0)
    {
        return CL_ERR_INVALID;
    }

    CLStatus st = CL_Init(list);
    if (st != CL_OK)
    {
        return st;
    }
    /* 头插法：结果与数组顺序相反 */
    for (int i = 0; i < n; ++i)
    {
        st = CL_InsertHead(*list, arr[i]);
        if (st != CL_OK)
        {
            CL_Destroy(list);
            return st;
        }
    }
    return CL_OK;
}

CLStatus CL_CreateTail(CircularList *list, const ElemType *arr, int n)
{
    if (list == NULL)
    {
        return CL_ERR_INVALID;
    }
    if (arr == NULL && n > 0)
    {
        return CL_ERR_INVALID;
    }

    CLStatus st = CL_Init(list);
    if (st != CL_OK)
    {
        return st;
    }
    /* 尾插法：维护尾指针，O(n) 建表 */
    LNode *tail = *list;
    for (int i = 0; i < n; ++i)
    {
        LNode *node = CL_NewNode(arr[i]);
        if (node == NULL)
        {
            CL_Destroy(list);
            return CL_ERR_NOMEM;
        }
        node->next = *list; /* 先指向头结点，维持环 */
        tail->next = node;
        tail = node;
    }
    return CL_OK;
}

/* ==================== 遍历与显示 ==================== */

CLStatus CL_Traverse(CircularList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx)
{
    CHECK_LIST(list, CL_ERR_INVALID);
    if (callback == NULL)
    {
        return CL_ERR_INVALID;
    }
    LNode *cur = list->next;
    int i = 0;
    while (cur != list)
    {
        if (!callback(cur->data, i, ctx))
        {
            break;
        }
        cur = cur->next;
        ++i;
    }
    return CL_OK;
}

CLStatus CL_Print(CircularList list)
{
    CHECK_LIST(list, CL_ERR_INVALID);

    printf("CircularList(len=%d): [", CL_Length(list));
    LNode *cur = list->next;
    while (cur != list)
    {
        printf("%d", cur->data);
        if (cur->next != list)
        {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("] -> (head)\n");
    return CL_OK;
}

/* ==================== 高级操作 ==================== */

CLStatus CL_Reverse(CircularList list)
{
    CHECK_LIST(list, CL_ERR_INVALID);

    if (list->next == list || list->next->next == list)
    {
        /* 空表或单元素，无需反转 */
        return CL_OK;
    }

    LNode *prev = list;
    LNode *cur = list->next;
    LNode *first = cur; /* 记录原首结点，反转后成为尾结点 */

    while (cur != list)
    {
        LNode *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    /* prev 为原尾结点，成为新首结点 */
    list->next = prev;
    /* first 成为新尾结点，指向头结点维持环 */
    first->next = list;
    return CL_OK;
}

int CL_RemoveAll(CircularList list, ElemType elem)
{
    if (list == NULL)
    {
        return -1;
    }
    int removed = 0;
    LNode *prev = list;
    while (prev->next != list)
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

int CL_UniqueSorted(CircularList list)
{
    if (list == NULL)
    {
        return -1;
    }
    if (list->next == list || list->next->next == list)
    {
        return 0;
    }
    int removed = 0;
    LNode *cur = list->next;
    while (cur != list && cur->next != list)
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

CLStatus CL_MergeSorted(CircularList a, CircularList b, CircularList *out)
{
    CHECK_LIST(a, CL_ERR_INVALID);
    CHECK_LIST(b, CL_ERR_INVALID);
    if (out == NULL)
    {
        return CL_ERR_INVALID;
    }

    CLStatus st = CL_Init(out);
    if (st != CL_OK)
    {
        return st;
    }

    LNode *pa = a->next;
    LNode *pb = b->next;
    LNode *tail = *out;

    while (pa != a && pb != b)
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
        LNode *node = CL_NewNode(val);
        if (node == NULL)
        {
            CL_Destroy(out);
            return CL_ERR_NOMEM;
        }
        node->next = *out;
        tail->next = node;
        tail = node;
    }
    while (pa != a)
    {
        LNode *node = CL_NewNode(pa->data);
        if (node == NULL)
        {
            CL_Destroy(out);
            return CL_ERR_NOMEM;
        }
        node->next = *out;
        tail->next = node;
        tail = node;
        pa = pa->next;
    }
    while (pb != b)
    {
        LNode *node = CL_NewNode(pb->data);
        if (node == NULL)
        {
            CL_Destroy(out);
            return CL_ERR_NOMEM;
        }
        node->next = *out;
        tail->next = node;
        tail = node;
        pb = pb->next;
    }
    return CL_OK;
}

CLStatus CL_Josephus(int n, int m, int *outOrder)
{
    if (n <= 0 || m <= 0 || outOrder == NULL)
    {
        return CL_ERR_INVALID;
    }

    /* 构建编号 1..n 的循环链表 */
    CircularList list;
    CLStatus st = CL_Init(&list);
    if (st != CL_OK)
    {
        return st;
    }
    for (int i = 1; i <= n; ++i)
    {
        st = CL_PushBack(list, i);
        if (st != CL_OK)
        {
            CL_Destroy(&list);
            return st;
        }
    }

    /* 模拟报数出列 */
    int count = 0;
    LNode *prev = list; /* 始终指向当前报数起点的前驱 */
    while (list->next != list)
    {
        /* 找到第 m 个结点的前驱：从 prev 开始走 m-1 步 */
        for (int i = 0; i < m - 1; ++i)
        {
            prev = prev->next;
            /* 跳过虚头结点 */
            if (prev == list)
            {
                prev = prev->next;
            }
        }
        LNode *target = prev->next;
        if (target == list)
        {
            /* 防御：理论上不会走到 */
            target = target->next;
        }
        outOrder[count++] = target->data;
        prev->next = target->next;
        free(target);
    }
    outOrder[count] = 0; /* 终止标记 */
    CL_Destroy(&list);
    return CL_OK;
}
