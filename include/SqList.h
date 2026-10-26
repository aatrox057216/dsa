/**
 * @file    SqList.h
 * @brief   动态顺序表（SqList）接口定义
 * @details 基于动态数组实现的线性表，容量可由 realloc 动态扩展。
 *          结构定义遵循严蔚敏《数据结构》教材风格。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef SQ_LIST_H
#define SQ_LIST_H

#include <stdbool.h>

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/** @brief 初始分配容量（以元素个数为单位） */
#define SQ_LIST_INIT_SIZE 10

/** @brief 扩容增量（每次扩容新增的元素个数） */
#define SQ_LIST_INCREMENT 5

/**
 * @brief 动态顺序表结构体
 *
 * elem    指向动态分配的连续存储空间
 * length  当前有效元素个数，有效下标范围 [0, length-1]
 * listsize 当前已分配的容量（以 sizeof(ElemType) 为单位）
 */
typedef struct
{
    ElemType *elem; /**< 存储空间基址（动态数组指针） */
    int length;     /**< 当前长度（实际元素个数） */
    int listsize;   /**< 当前分配的存储容量（以 sizeof(ElemType) 为单位） */
} SqList;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    SQ_OK = 0,         /**< 操作成功 */
    SQ_ERR_FULL = 1,   /**< 表已满（保留，扩容失败时使用） */
    SQ_ERR_EMPTY = 2,  /**< 表为空 */
    SQ_ERR_RANGE = 3,  /**< 下标越界 */
    SQ_ERR_NOMEM = 4,  /**< 内存分配失败 */
    SQ_ERR_INVALID = 5 /**< 无效参数 */
} SqStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化顺序表
 * @param  list 待初始化的顺序表指针
 * @return SQ_OK 成功；SQ_ERR_NOMEM 内存不足；SQ_ERR_INVALID 参数为空
 * @note   分配 SQ_LIST_INIT_SIZE 个元素空间，length 置 0
 */
SqStatus Sq_Init(SqList *list);

/**
 * @brief  清空顺序表
 * @param  list 顺序表指针
 * @return SQ_OK 成功；SQ_ERR_INVALID 参数为空
 * @note   仅将 length 置 0，保留已分配空间
 */
SqStatus Sq_Clear(SqList *list);

/**
 * @brief  销毁顺序表
 * @param  list 顺序表指针
 * @return SQ_OK 成功；SQ_ERR_INVALID 参数为空
 * @note   释放 elem 指向的内存，并将指针置 NULL
 */
SqStatus Sq_Destroy(SqList *list);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取当前长度
 * @param  list 顺序表指针
 * @return 当前元素个数；参数为空返回 -1
 */
int Sq_Length(const SqList *list);

/**
 * @brief  获取当前容量
 * @param  list 顺序表指针
 * @return 已分配容量；参数为空返回 -1
 */
int Sq_Capacity(const SqList *list);

/**
 * @brief  判断表是否为空
 * @param  list 顺序表指针
 * @return true 为空；false 非空或参数为空
 */
bool Sq_IsEmpty(const SqList *list);

/**
 * @brief  判断表是否已满
 * @param  list 顺序表指针
 * @return true 已满；false 未满或参数为空
 */
bool Sq_IsFull(const SqList *list);

/**
 * @brief  扩容到指定容量
 * @param  list     顺序表指针
 * @param  newSize  目标容量（元素个数），须 >= length
 * @return SQ_OK 成功；SQ_ERR_NOMEM 内存不足；
 *         SQ_ERR_INVALID 参数非法或 newSize < length
 * @note   使用 realloc 重新分配，原数据保留
 */
SqStatus Sq_Reserve(SqList *list, int newSize);

/**
 * @brief  确保容量足够，不足时按增量扩容
 * @param  list     顺序表指针
 * @param  needSize 需要的最小容量
 * @return SQ_OK 成功；SQ_ERR_NOMEM 内存不足；SQ_ERR_INVALID 参数为空
 */
SqStatus Sq_EnsureCapacity(SqList *list, int needSize);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找（随机访问）
 * @param  list  顺序表指针
 * @param  index 目标下标，范围 [0, length-1]
 * @param  out   用于返回元素值的指针
 * @return SQ_OK 成功；SQ_ERR_RANGE 越界；SQ_ERR_INVALID 参数为空
 * @note   时间复杂度 O(1)
 */
SqStatus Sq_GetElem(const SqList *list, int index, ElemType *out);

/**
 * @brief  按值查找
 * @param  list 顺序表指针
 * @param  elem 目标元素值
 * @return 首次出现的下标；未找到返回 -1；参数为空返回 -1
 * @note   时间复杂度 O(n)
 */
int Sq_LocateElem(const SqList *list, ElemType elem);

/* ==================== 插入与删除 ==================== */

/**
 * @brief  在指定位置插入元素
 * @param  list  顺序表指针
 * @param  index 插入位置，范围 [0, length]
 * @param  elem  待插入元素
 * @return SQ_OK 成功；SQ_ERR_NOMEM 扩容失败；
 *         SQ_ERR_RANGE 越界；SQ_ERR_INVALID 参数为空
 * @note   时间复杂度 O(n)，插入位置之后元素整体后移；容量不足时自动扩容
 */
SqStatus Sq_Insert(SqList *list, int index, ElemType elem);

/**
 * @brief  在表尾追加元素
 * @param  list 顺序表指针
 * @param  elem 待追加元素
 * @return SQ_OK 成功；SQ_ERR_NOMEM 扩容失败；SQ_ERR_INVALID 参数为空
 * @note   均摊时间复杂度 O(1)
 */
SqStatus Sq_PushBack(SqList *list, ElemType elem);

/**
 * @brief  删除指定位置的元素
 * @param  list  顺序表指针
 * @param  index 删除位置，范围 [0, length-1]
 * @param  out   用于返回被删元素的指针，可为 NULL
 * @return SQ_OK 成功；SQ_ERR_EMPTY 表空；
 *         SQ_ERR_RANGE 越界；SQ_ERR_INVALID 参数为空
 * @note   时间复杂度 O(n)，删除位置之后元素整体前移
 */
SqStatus Sq_DeleteAt(SqList *list, int index, ElemType *out);

/**
 * @brief  删除首个值等于 elem 的元素
 * @param  list 顺序表指针
 * @param  elem 目标元素值
 * @return SQ_OK 成功；SQ_ERR_EMPTY 表空；
 *         SQ_ERR_RANGE 未找到；SQ_ERR_INVALID 参数为空
 */
SqStatus Sq_RemoveElem(SqList *list, ElemType elem);

/**
 * @brief  删除表尾元素
 * @param  list 顺序表指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return SQ_OK 成功；SQ_ERR_EMPTY 表空；SQ_ERR_INVALID 参数为空
 */
SqStatus Sq_PopBack(SqList *list, ElemType *out);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  遍历顺序表并对每个元素调用回调
 * @param  list     顺序表指针
 * @param  callback 回调函数，返回 false 可提前终止遍历
 * @param  ctx      用户上下文，透传给回调
 * @return SQ_OK 成功；SQ_ERR_INVALID 参数为空
 */
SqStatus Sq_Traverse(const SqList *list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印顺序表内容到标准输出
 * @param  list 顺序表指针
 * @return SQ_OK 成功；SQ_ERR_INVALID 参数为空
 */
SqStatus Sq_Print(const SqList *list);

/* ==================== 高级操作 ==================== */

/**
 * @brief  反转顺序表
 * @param  list 顺序表指针
 * @return SQ_OK 成功；SQ_ERR_INVALID 参数为空
 * @note   原地交换，时间复杂度 O(n)，空间 O(1)
 */
SqStatus Sq_Reverse(SqList *list);

/**
 * @brief  删除所有值等于 elem 的元素
 * @param  list 顺序表指针
 * @param  elem 目标元素值
 * @return 实际删除的元素个数；参数为空返回 -1
 * @note   双指针原地压缩，时间复杂度 O(n)
 */
int Sq_RemoveAll(SqList *list, ElemType elem);

/**
 * @brief  去重（仅适用于有序表）
 * @param  list 顺序表指针
 * @return 去重后删除的元素个数；参数为空返回 -1
 * @note   双指针法，时间复杂度 O(n)，要求表已升序
 */
int Sq_UniqueSorted(SqList *list);

/**
 * @brief  合并两个有序顺序表到新表
 * @param  a   有序表 A
 * @param  b   有序表 B
 * @param  out 结果表（需已初始化，容量不足时自动扩容）
 * @return SQ_OK 成功；SQ_ERR_NOMEM 内存不足；SQ_ERR_INVALID 参数为空
 * @note   时间复杂度 O(m + n)
 */
SqStatus Sq_MergeSorted(const SqList *a, const SqList *b, SqList *out);

/**
 * @brief  收缩容量至刚好容纳当前元素
 * @param  list 顺序表指针
 * @return SQ_OK 成功；SQ_ERR_NOMEM 内存不足；SQ_ERR_INVALID 参数为空
 * @note   释放多余空间，适用于大数据删除后回收内存
 */
SqStatus Sq_ShrinkToFit(SqList *list);

#endif /* SQ_LIST_H */
