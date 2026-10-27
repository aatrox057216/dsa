/**
 * @file    main.c
 * @brief   带头结点循环单链表使用示例
 */

#include "CircularList.h"
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
    CircularList headList, tailList;
    CL_CreateHead(&headList, arr, n);
    printf("头插法建表（数组 1..5）：");
    CL_Print(headList); /* [5 -> 4 -> 3 -> 2 -> 1] */

    CL_CreateTail(&tailList, arr, n);
    printf("尾插法建表（数组 1..5）：");
    CL_Print(tailList); /* [1 -> 2 -> 3 -> 4 -> 5] */

    /* ---------- 判空与长度 ---------- */
    CircularList empty;
    CL_Init(&empty);
    printf("空表判空：%s，长度：%d\n", CL_IsEmpty(empty) ? "true" : "false", CL_Length(empty));

    /* ---------- 插入 ---------- */
    CL_InsertHead(tailList, 0);
    printf("头插 0 后：");
    CL_Print(tailList);

    CL_PushBack(tailList, 6);
    printf("尾插 6 后：");
    CL_Print(tailList);

    CL_InsertAt(tailList, 3, 99);
    printf("在下标 3 插入 99 后：");
    CL_Print(tailList);

    /* ---------- 查找 ---------- */
    ElemType val;
    CL_GetElem(tailList, 3, &val);
    printf("下标 3 的元素：%d\n", val);
    printf("99 的下标：%d\n", CL_LocateElem(tailList, 99));

    /* ---------- 删除 ---------- */
    CL_PopFront(tailList, &val);
    printf("删除表头（值 %d）后：", val);
    CL_Print(tailList);

    CL_PopBack(tailList, &val);
    printf("删除表尾（值 %d）后：", val);
    CL_Print(tailList);

    CL_RemoveElem(tailList, 99);
    printf("删除值 99 后：");
    CL_Print(tailList);

    /* ---------- 反转 ---------- */
    CL_Reverse(tailList);
    printf("反转后：");
    CL_Print(tailList);

    /* ---------- 删除所有指定值 ---------- */
    CL_PushBack(tailList, 3);
    CL_PushBack(tailList, 3);
    int removed = CL_RemoveAll(tailList, 3);
    printf("删除所有 3（共 %d 个）后：", removed);
    CL_Print(tailList);

    /* ---------- 合并有序循环链表 ---------- */
    CircularList a, b, merged;
    CL_Init(&a);
    CL_Init(&b);
    for (int i = 1; i <= 5; i += 2)
    {
        CL_PushBack(a, i); /* 1 3 5 */
    }
    for (int i = 2; i <= 6; i += 2)
    {
        CL_PushBack(b, i); /* 2 4 6 */
    }
    CL_MergeSorted(a, b, &merged);
    printf("合并有序循环链表后：");
    CL_Print(merged);

    /* ---------- 有序去重 ---------- */
    CircularList dup;
    int dupArr[] = { 1, 1, 2, 2, 2, 3, 4, 4, 5 };
    CL_CreateTail(&dup, dupArr, 9);
    removed = CL_UniqueSorted(dup);
    printf("去重删除 %d 个结点后：", removed);
    CL_Print(dup);

    /* ---------- 约瑟夫环 ---------- */
    int order[16] = { 0 };
    CL_Josephus(7, 3, order);
    printf("约瑟夫环 n=7, m=3 出列顺序：");
    for (int i = 0; order[i] != 0; ++i)
    {
        printf("%d ", order[i]);
    }
    printf("\n");

    /* ---------- 遍历回调 ---------- */
    printf("遍历输出（尾插表）：\n");
    CL_Traverse(tailList, print_cb, NULL);

    /* ---------- 清空与销毁 ---------- */
    CL_Clear(tailList);
    printf("清空后：");
    CL_Print(tailList);

    CL_Destroy(&headList);
    CL_Destroy(&tailList);
    CL_Destroy(&empty);
    CL_Destroy(&a);
    CL_Destroy(&b);
    CL_Destroy(&merged);
    CL_Destroy(&dup);

    return 0;
}
