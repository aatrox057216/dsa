/**
 * @file    main.c
 * @brief   带头结点双向链表使用示例
 */

#include "DuLinkList.h"
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

    /* ---------- 头插法 vs 尾插法 ---------- */
    DuLinkList headList, tailList;
    DL_CreateHead(&headList, arr, n);
    printf("头插法建表（数组 1..5）：");
    DL_Print(headList); /* [5, 4, 3, 2, 1] */

    DL_CreateTail(&tailList, arr, n);
    printf("尾插法建表（数组 1..5）：");
    DL_Print(tailList); /* [1, 2, 3, 4, 5] */

    /* ---------- 双向遍历 ---------- */
    printf("正向遍历：\n");
    DL_TraverseForward(tailList, print_cb, NULL);

    printf("反向遍历：\n");
    DL_TraverseBackward(tailList, print_cb, NULL);

    DL_PrintReverse(tailList);

    /* ---------- 插入 ---------- */
    DL_InsertHead(tailList, 0);
    printf("头插 0 后：");
    DL_Print(tailList);

    DL_PushBack(tailList, 6);
    printf("尾插 6 后：");
    DL_Print(tailList);

    DL_InsertAt(tailList, 3, 99);
    printf("在下标 3 插入 99 后：");
    DL_Print(tailList);

    /* ---------- 已知结点 O(1) 前后插 ---------- */
    DuLNode *node = DL_GetNode(tailList, 2); /* 值为 2 的结点 */
    DL_InsertAfter(node, 88);
    printf("在结点 2 之后插入 88：");
    DL_Print(tailList);

    DL_InsertBefore(node, 77);
    printf("在结点 2 之前插入 77：");
    DL_Print(tailList);

    /* ---------- 查找 ---------- */
    ElemType val;
    DL_GetElem(tailList, 3, &val);
    printf("下标 3 的元素：%d\n", val);
    printf("99 的下标：%d\n", DL_LocateElem(tailList, 99));

    /* ---------- 删除 ---------- */
    DL_PopFront(tailList, &val);
    printf("删除表头（值 %d）后：", val);
    DL_Print(tailList);

    DL_PopBack(tailList, &val);
    printf("删除表尾（值 %d）后：", val);
    DL_Print(tailList);

    /* ---------- 已知结点 O(1) 删除 ---------- */
    DuLNode *victim = DL_GetNode(tailList, 1);
    DL_DeleteNode(victim, &val);
    printf("删除下标 1（值 %d）后：", val);
    DL_Print(tailList);

    DL_RemoveElem(tailList, 99);
    printf("删除值 99 后：");
    DL_Print(tailList);

    /* ---------- 反转 ---------- */
    DL_Reverse(tailList);
    printf("反转后：");
    DL_Print(tailList);
    DL_PrintReverse(tailList);

    /* ---------- 删除所有指定值 ---------- */
    DL_PushBack(tailList, 3);
    DL_PushBack(tailList, 3);
    int removed = DL_RemoveAll(tailList, 3);
    printf("删除所有 3（共 %d 个）后：", removed);
    DL_Print(tailList);

    /* ---------- 合并有序双向链表 ---------- */
    DuLinkList a, b, merged;
    DL_Init(&a);
    DL_Init(&b);
    for (int i = 1; i <= 5; i += 2)
    {
        DL_PushBack(a, i); /* 1 3 5 */
    }
    for (int i = 2; i <= 6; i += 2)
    {
        DL_PushBack(b, i); /* 2 4 6 */
    }
    DL_MergeSorted(a, b, &merged);
    printf("合并有序双向链表后：");
    DL_Print(merged);

    /* ---------- 有序去重 ---------- */
    DuLinkList dup;
    int dupArr[] = { 1, 1, 2, 2, 2, 3, 4, 4, 5 };
    DL_CreateTail(&dup, dupArr, 9);
    removed = DL_UniqueSorted(dup);
    printf("去重删除 %d 个结点后：", removed);
    DL_Print(dup);

    /* ---------- 清空与销毁 ---------- */
    DL_Clear(tailList);
    printf("清空后：");
    DL_Print(tailList);

    DL_Destroy(&headList);
    DL_Destroy(&tailList);
    DL_Destroy(&a);
    DL_Destroy(&b);
    DL_Destroy(&merged);
    DL_Destroy(&dup);

    return 0;
}
