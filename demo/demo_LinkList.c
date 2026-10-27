/**
 * @file    main.c
 * @brief   带头结点单链表使用示例：对比头插法与尾插法
 */

#include "LinkList.h"
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
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    /* ---------- 头插法建表：结果与数组相反 ---------- */
    LinkList headList;
    LL_CreateHead(&headList, arr, n);
    printf("头插法建表（数组 1..5）：");
    LL_Print(headList); /* 期望 [5, 4, 3, 2, 1] */

    /* ---------- 尾插法建表：结果与数组一致 ---------- */
    LinkList tailList;
    LL_CreateTail(&tailList, arr, n);
    printf("尾插法建表（数组 1..5）：");
    LL_Print(tailList); /* 期望 [1, 2, 3, 4, 5] */

    /* ---------- 单元素操作 ---------- */
    LL_InsertHead(tailList, 0);
    printf("头插 0 后：");
    LL_Print(tailList);

    LL_PushBack(tailList, 6);
    printf("尾插 6 后：");
    LL_Print(tailList);

    LL_InsertAt(tailList, 3, 99);
    printf("在下标 3 插入 99 后：");
    LL_Print(tailList);

    /* ---------- 查找 ---------- */
    ElemType val;
    LL_GetElem(tailList, 3, &val);
    printf("下标 3 的元素：%d\n", val);
    printf("99 的下标：%d\n", LL_LocateElem(tailList, 99));

    /* ---------- 已知结点前后插 ---------- */
    LNode *node = LL_GetNode(tailList, 2); /* 值为 2 的结点 */
    LL_InsertAfter(node, 88);
    printf("在结点 2 之后插入 88：");
    LL_Print(tailList);

    LL_InsertBefore(tailList, node, 77);
    printf("在结点 2 之前插入 77：");
    LL_Print(tailList);

    /* ---------- 删除 ---------- */
    LL_PopFront(tailList, &val);
    printf("删除表头（值 %d）后：", val);
    LL_Print(tailList);

    LL_PopBack(tailList, &val);
    printf("删除表尾（值 %d）后：", val);
    LL_Print(tailList);

    LL_RemoveElem(tailList, 99);
    printf("删除值 99 后：");
    LL_Print(tailList);

    /* ---------- 反转 ---------- */
    LL_Reverse(tailList);
    printf("反转后：");
    LL_Print(tailList);

    /* ---------- 删除所有指定值 ---------- */
    LL_PushBack(tailList, 3);
    LL_PushBack(tailList, 3);
    int removed = LL_RemoveAll(tailList, 3);
    printf("删除所有 3（共 %d 个）后：", removed);
    LL_Print(tailList);

    /* ---------- 中间结点 ---------- */
    LNode *mid = LL_MiddleNode(tailList);
    if (mid != NULL)
    {
        printf("中间结点值：%d\n", mid->data);
    }

    /* ---------- 合并有序链表 ---------- */
    LinkList a, b, merged;
    LL_Init(&a);
    LL_Init(&b);
    for (int i = 1; i <= 5; i += 2)
    {
        LL_PushBack(a, i); /* 1 3 5 */
    }
    for (int i = 2; i <= 6; i += 2)
    {
        LL_PushBack(b, i); /* 2 4 6 */
    }
    LL_MergeSorted(a, b, &merged);
    printf("合并有序链表后：");
    LL_Print(merged);

    /* ---------- 有序去重 ---------- */
    LinkList dup;
    int dupArr[] = { 1, 1, 2, 2, 2, 3, 4, 4, 5 };
    LL_CreateTail(&dup, dupArr, 9);
    removed = LL_UniqueSorted(dup);
    printf("去重删除 %d 个结点后：", removed);
    LL_Print(dup);

    /* ---------- 遍历回调 ---------- */
    printf("遍历输出（尾插表）：\n");
    LL_Traverse(tailList, print_cb, NULL);

    /* ---------- 清空与销毁 ---------- */
    LL_Clear(tailList);
    printf("清空后：");
    LL_Print(tailList);

    LL_Destroy(&headList);
    LL_Destroy(&tailList);
    LL_Destroy(&a);
    LL_Destroy(&b);
    LL_Destroy(&merged);
    LL_Destroy(&dup);

    return 0;
}
