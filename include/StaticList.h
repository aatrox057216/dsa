/**
 * @file    StaticList.h
 * @brief   静态顺序表（Static Sequential List）接口定义
 * @details 基于固定大小数组实现的线性表，容量在编译期确定，
 *          不支持自动扩容。所有操作均在此容量约束下进行。
 * @author  aatroxfans
 * @date    2026-10-13
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include <stdbool.h>

/** @brief 静态顺序表最大容量 */
#define MAX_SIZE 100

/** @brief 静态顺序表元素类型别名，便于统一修改 */
typedef int ElemType;

/**
 * @brief 静态顺序表结构体
 *
 * 使用定长数组存储元素，length 记录当前有效元素个数。
 * 有效下标范围为 [0, length - 1]。
 */
typedef struct
{
    ElemType data[MAX_SIZE]; /**< 静态数组，大小固定 */
    int length;              /**< 当前长度（有效元素个数） */
} StaticList;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    SL_OK = 0,         /**< 操作成功 */
    SL_ERR_FULL = 1,   /**< 表已满 */
    SL_ERR_EMPTY = 2,  /**< 表为空 */
    SL_ERR_RANGE = 3,  /**< 下标越界 */
    SL_ERR_NOMEM = 4,  /**< 内存分配失败（保留） */
    SL_ERR_INVALID = 5 /**< 无效参数 */
} SLStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化顺序表
 * @param  list 待初始化的顺序表指针
 * @return SL_OK 成功；SL_ERR_INVALID 参数为空
 * @note   将 length 置 0，data 内容清 0
 */
SLStatus SL_Init(StaticList *list);

/**
 * @brief  清空顺序表
 * @param  list 顺序表指针
 * @return SL_OK 成功；SL_ERR_INVALID 参数为空
 * @note   仅将 length 置 0，不修改 data 内容
 */
SLStatus SL_Clear(StaticList *list);

/**
 * @brief  销毁顺序表
 * @param  list 顺序表指针
 * @return SL_OK 成功；SL_ERR_INVALID 参数为空
 * @note   静态顺序表无需释放内存，等价于 Clear
 */
SLStatus SL_Destroy(StaticList *list);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取当前长度
 * @param  list 顺序表指针
 * @return 当前元素个数；参数为空返回 -1
 */
int SL_Length(const StaticList *list);

/**
 * @brief  获取最大容量
 * @param  list 顺序表指针
 * @return 最大容量；参数为空返回 -1
 */
int SL_Capacity(const StaticList *list);

/**
 * @brief  判断表是否为空
 * @param  list 顺序表指针
 * @return true 为空；false 非空或参数为空
 */
bool SL_IsEmpty(const StaticList *list);

/**
 * @brief  判断表是否已满
 * @param  list 顺序表指针
 * @return true 已满；false 未满或参数为空
 */
bool SL_IsFull(const StaticList *list);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找（随机访问）
 * @param  list  顺序表指针
 * @param  index 目标下标，范围 [0, length-1]
 * @param  out   用于返回元素值的指针
 * @return SL_OK 成功；SL_ERR_RANGE 越界；SL_ERR_INVALID 参数为空
 * @note   时间复杂度 O(1)
 */
SLStatus SL_GetElem(const StaticList *list, int index, ElemType *out);

/**
 * @brief  按值查找
 * @param  list 顺序表指针
 * @param  elem 目标元素值
 * @return 首次出现的下标；未找到返回 -1；参数为空返回 -1
 * @note   时间复杂度 O(n)
 */
int SL_LocateElem(const StaticList *list, ElemType elem);

/* ==================== 插入与删除 ==================== */

/**
 * @brief  在指定位置插入元素
 * @param  list  顺序表指针
 * @param  index 插入位置，范围 [0, length]
 * @param  elem  待插入元素
 * @return SL_OK 成功；SL_ERR_FULL 表满；
 *         SL_ERR_RANGE 越界；SL_ERR_INVALID 参数为空
 * @note   时间复杂度 O(n)，插入位置之后元素整体后移
 */
SLStatus SL_Insert(StaticList *list, int index, ElemType elem);

/**
 * @brief  在表尾追加元素
 * @param  list 顺序表指针
 * @param  elem 待追加元素
 * @return SL_OK 成功；SL_ERR_FULL 表满；SL_ERR_INVALID 参数为空
 * @note   时间复杂度 O(1)
 */
SLStatus SL_PushBack(StaticList *list, ElemType elem);

/**
 * @brief  删除指定位置的元素
 * @param  list  顺序表指针
 * @param  index 删除位置，范围 [0, length-1]
 * @param  out   用于返回被删元素的指针，可为 NULL
 * @return SL_OK 成功；SL_ERR_EMPTY 表空；
 *         SL_ERR_RANGE 越界；SL_ERR_INVALID 参数为空
 * @note   时间复杂度 O(n)，删除位置之后元素整体前移
 */
SLStatus SL_DeleteAt(StaticList *list, int index, ElemType *out);

/**
 * @brief  删除首个值等于 elem 的元素
 * @param  list 顺序表指针
 * @param  elem 目标元素值
 * @return SL_OK 成功；SL_ERR_EMPTY 表空；
 *         SL_ERR_RANGE 未找到；SL_ERR_INVALID 参数为空
 */
SLStatus SL_RemoveElem(StaticList *list, ElemType elem);

/**
 * @brief  删除表尾元素
 * @param  list 顺序表指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return SL_OK 成功；SL_ERR_EMPTY 表空；SL_ERR_INVALID 参数为空
 */
SLStatus SL_PopBack(StaticList *list, ElemType *out);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  遍历顺序表并对每个元素调用回调
 * @param  list     顺序表指针
 * @param  callback 回调函数，返回 false 可提前终止遍历
 * @param  ctx      用户上下文，透传给回调
 * @return SL_OK 成功；SL_ERR_INVALID 参数为空
 */
SLStatus SL_Traverse(const StaticList *list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印顺序表内容到标准输出
 * @param  list 顺序表指针
 * @return SL_OK 成功；SL_ERR_INVALID 参数为空
 */
SLStatus SL_Print(const StaticList *list);

/* ==================== 高级操作 ==================== */

/**
 * @brief  反转顺序表
 * @param  list 顺序表指针
 * @return SL_OK 成功；SL_ERR_INVALID 参数为空
 * @note   原地交换，时间复杂度 O(n)，空间 O(1)
 */
SLStatus SL_Reverse(StaticList *list);

/**
 * @brief  删除所有值等于 elem 的元素
 * @param  list 顺序表指针
 * @param  elem 目标元素值
 * @return 实际删除的元素个数；参数为空返回 -1
 * @note   双指针原地压缩，时间复杂度 O(n)
 */
int SL_RemoveAll(StaticList *list, ElemType elem);

/**
 * @brief  去重（仅适用于有序表）
 * @param  list 顺序表指针
 * @return 去重后删除的元素个数；参数为空返回 -1
 * @note   双指针法，时间复杂度 O(n)，要求表已升序
 */
int SL_UniqueSorted(StaticList *list);

/**
 * @brief  合并两个有序顺序表到新表
 * @param  a   有序表 A
 * @param  b   有序表 B
 * @param  out 结果表（需已初始化，容量足够）
 * @return SL_OK 成功；SL_ERR_FULL 结果表容量不足；SL_ERR_INVALID 参数为空
 * @note   时间复杂度 O(m + n)
 */
SLStatus SL_MergeSorted(const StaticList *a, const StaticList *b, StaticList *out); // NOLINT()

#endif /* STATIC_LIST_H */
