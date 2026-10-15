/**
 * @file    demo_StaticList.c
 * @brief   静态顺序表使用示例
 */

#include "StaticList.h"
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

    StaticList list;

    /* 初始化 */
    SL_Init(&list);
    printf("初始化后：");
    SL_Print(&list);

    /* 尾部追加 */
    for (int i = 1; i <= 5; ++i) // NOLINT(readability-magic-numbers)
    {
        SL_PushBack(&list, i * 10); // NOLINT(readability-magic-numbers)
    }
    printf("追加 10/20/30/40/50 后：");
    SL_Print(&list);

    /* 指定位置插入 */
    SL_Insert(&list, 2, 99); // NOLINT(readability-magic-numbers)
    printf("在下标 2 插入 99 后：");
    SL_Print(&list);

    /* 按值查找 */
    int pos = SL_LocateElem(&list, 99); // NOLINT(readability-magic-numbers)
    printf("99 的下标：%d\n", pos);

    /* 按位置查找 */
    ElemType val;
    SL_GetElem(&list, 0, &val);
    printf("下标 0 的元素：%d\n", val);

    /* 删除指定位置 */
    SL_DeleteAt(&list, 1, &val);
    printf("删除下标 1（值 %d）后：", val);
    SL_Print(&list);

    /* 删除指定值 */
    SL_RemoveElem(&list, 99); // NOLINT(readability-magic-numbers)
    printf("删除值 99 后：");
    SL_Print(&list);

    /* 反转 */
    SL_Reverse(&list);
    printf("反转后：");
    SL_Print(&list);

    /* 遍历回调 */
    printf("遍历输出：\n");
    SL_Traverse(&list, print_cb, NULL);

    /* 合并两个有序表 */
    StaticList a, b, merged; // NOLINT(readability-isolate-declaration,readability-identifier-length)
    SL_Init(&a);
    SL_Init(&b);
    SL_Init(&merged);
    for (int i = 1; i <= 5; i += 2) // NOLINT(readability-magic-numbers)
    {
        SL_PushBack(&a, i); /* 1 3 5 */
    }
    for (int i = 2; i <= 6; i += 2) // NOLINT(readability-magic-numbers)
    {
        SL_PushBack(&b, i); /* 2 4 6 */
    }

    SL_MergeSorted(&a, &b, &merged);
    printf("合并有序表后：");
    SL_Print(&merged);

    /* 去重（有序） */
    StaticList dup;
    SL_Init(&dup);
    int arr[] = { 1, 1, 2, 2, 2, 3, 4, 4, 5 }; // NOLINT(readability-magic-numbers)
    for (int i = 0; i < 9; ++i)                // NOLINT(readability-magic-numbers)
    {
        SL_PushBack(&dup, arr[i]);
    }
    int removed = SL_UniqueSorted(&dup);
    printf("去重删除 %d 个元素后：", removed);
    SL_Print(&dup);

    /* 清空 */
    SL_Clear(&list);
    printf("清空后：");
    SL_Print(&list);

    return 0;
}
