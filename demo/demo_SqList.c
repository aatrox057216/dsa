/**
 * @file    main.c
 * @brief   动态顺序表（SqList）使用示例
 */

#include "SqList.h"
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
    SqList list;

    /* 初始化 */
    if (Sq_Init(&list) != SQ_OK)
    {
        printf("初始化失败\n");
        return 1;
    }
    printf("初始化后：");
    Sq_Print(&list);

    /* 尾部追加，观察自动扩容 */
    for (int i = 1; i <= 15; ++i)
    {
        Sq_PushBack(&list, i * 10);
        if (i == SQ_LIST_INIT_SIZE || i == 15)
        {
            printf("追加 %d 个元素后容量：%d\n", i, Sq_Capacity(&list));
        }
    }
    printf("追加 10..150 后：");
    Sq_Print(&list);

    /* 指定位置插入 */
    Sq_Insert(&list, 2, 99);
    printf("在下标 2 插入 99 后：");
    Sq_Print(&list);

    /* 按值查找 */
    int pos = Sq_LocateElem(&list, 99);
    printf("99 的下标：%d\n", pos);

    /* 按位置查找 */
    ElemType val;
    Sq_GetElem(&list, 0, &val);
    printf("下标 0 的元素：%d\n", val);

    /* 删除指定位置 */
    Sq_DeleteAt(&list, 1, &val);
    printf("删除下标 1（值 %d）后：", val);
    Sq_Print(&list);

    /* 删除指定值 */
    Sq_RemoveElem(&list, 99);
    printf("删除值 99 后：");
    Sq_Print(&list);

    /* 反转 */
    Sq_Reverse(&list);
    printf("反转后：");
    Sq_Print(&list);

    /* 遍历回调 */
    printf("遍历输出：\n");
    Sq_Traverse(&list, print_cb, NULL);

    /* 删除所有指定值 */
    Sq_PushBack(&list, 50);
    Sq_PushBack(&list, 50);
    int removed = Sq_RemoveAll(&list, 50);
    printf("删除所有 50（共 %d 个）后：", removed);
    Sq_Print(&list);

    /* 收缩容量 */
    Sq_ShrinkToFit(&list);
    printf("收缩容量后：");
    Sq_Print(&list);

    /* 合并两个有序表 */
    SqList a, b, merged;
    Sq_Init(&a);
    Sq_Init(&b);
    Sq_Init(&merged);
    for (int i = 1; i <= 5; i += 2)
    {
        Sq_PushBack(&a, i); /* 1 3 5 */
    }
    for (int i = 2; i <= 6; i += 2)
    {
        Sq_PushBack(&b, i); /* 2 4 6 */
    }

    Sq_MergeSorted(&a, &b, &merged);
    printf("合并有序表后：");
    Sq_Print(&merged);

    /* 有序去重 */
    SqList dup;
    Sq_Init(&dup);
    int arr[] = { 1, 1, 2, 2, 2, 3, 4, 4, 5 };
    for (int i = 0; i < 9; ++i)
    {
        Sq_PushBack(&dup, arr[i]);
    }
    removed = Sq_UniqueSorted(&dup);
    printf("去重删除 %d 个元素后：", removed);
    Sq_Print(&dup);

    /* 清空 */
    Sq_Clear(&list);
    printf("清空后：");
    Sq_Print(&list);

    /* 销毁 */
    Sq_Destroy(&list);
    Sq_Destroy(&a);
    Sq_Destroy(&b);
    Sq_Destroy(&merged);
    Sq_Destroy(&dup);

    return 0;
}
