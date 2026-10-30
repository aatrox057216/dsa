/**
 * @file    BothStack.h
 * @brief   双栈共享存储空间（Shared Stack）接口定义
 * @details 两个栈共享同一数组，top1 从 0 向高位增长，
 *          top2 从 MAX_SIZE-1 向低位下降，相向而行。
 *          判满条件：top1 + 1 == top2。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef BOTH_STACK_H
#define BOTH_STACK_H

#include <stdbool.h>

/** @brief 共享数组最大容量 */
#define MAX_SIZE 100

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/** @brief 栈编号：栈 1 与栈 2 */
#define STACK_1 1
#define STACK_2 2

/**
 * @brief 双栈共享存储空间结构体
 *
 * data 共享数组
 * top1 栈 1 栈顶指针，初始 -1，从 0 开始向高位增长
 * top2 栈 2 栈顶指针，初始 MAX_SIZE，从 MAX_SIZE-1 开始向低位下降
 */
typedef struct
{
    ElemType data[MAX_SIZE]; /**< 共享存储空间 */
    int top1;                /**< 栈 1 栈顶，从 0 开始增长 */
    int top2;                /**< 栈 2 栈顶，从 MAX_SIZE-1 开始下降 */
} BothStack;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    BS_OK = 0,          /**< 操作成功 */
    BS_ERR_FULL = 1,    /**< 共享空间已满 */
    BS_ERR_EMPTY = 2,   /**< 目标栈为空 */
    BS_ERR_NOMEM = 3,   /**< 内存分配失败（保留） */
    BS_ERR_INVALID = 4, /**< 无效参数（含非法栈号） */
} BSStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化双栈
 * @param  bs 双栈指针
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空
 * @note   top1 置 -1，top2 置 MAX_SIZE
 */
BSStatus BS_Init(BothStack *bs);

/**
 * @brief  清空指定栈
 * @param  bs      双栈指针
 * @param  stackNo 栈编号（STACK_1 或 STACK_2）
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空或栈号非法
 * @note   只重置目标栈的 top，不影响另一个栈
 */
BSStatus BS_Clear(BothStack *bs, int stackNo);

/**
 * @brief  清空两个栈
 * @param  bs 双栈指针
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空
 */
BSStatus BS_ClearAll(BothStack *bs);

/**
 * @brief  销毁双栈
 * @param  bs 双栈指针
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空
 * @note   静态存储，语义上等价于 ClearAll
 */
BSStatus BS_Destroy(BothStack *bs);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取指定栈的元素个数
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @return 元素个数；参数非法返回 -1
 */
int BS_Size(const BothStack *bs, int stackNo);

/**
 * @brief  获取共享数组总容量
 * @param  bs 双栈指针
 * @return 总容量；参数为空返回 -1
 */
int BS_Capacity(const BothStack *bs);

/**
 * @brief  获取共享空间剩余可用槽位
 * @param  bs 双栈指针
 * @return 剩余槽位数；参数为空返回 -1
 * @note   O(1)；= MAX_SIZE - size1 - size2
 */
int BS_Remaining(const BothStack *bs);

/**
 * @brief  判断指定栈是否为空
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @return true 为空；false 非空或参数非法
 */
bool BS_IsEmpty(const BothStack *bs, int stackNo);

/**
 * @brief  判断共享空间是否已满
 * @param  bs 双栈指针
 * @return true 已满；false 未满或参数为空
 * @note   判满条件：top1 + 1 == top2
 */
bool BS_IsFull(const BothStack *bs);

/* ==================== 核心操作 ==================== */

/**
 * @brief  压栈
 * @param  bs      双栈指针
 * @param  stackNo 栈编号（STACK_1 或 STACK_2）
 * @param  elem    待压入元素
 * @return BS_OK 成功；BS_ERR_FULL 共享空间已满；
 *         BS_ERR_INVALID 参数为空或栈号非法
 * @note   O(1)
 */
BSStatus BS_Push(BothStack *bs, int stackNo, ElemType elem);

/**
 * @brief  弹栈
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @param  out     用于返回被弹出元素的指针，可为 NULL
 * @return BS_OK 成功；BS_ERR_EMPTY 目标栈为空；
 *         BS_ERR_INVALID 参数为空或栈号非法
 * @note   O(1)
 */
BSStatus BS_Pop(BothStack *bs, int stackNo, ElemType *out);

/**
 * @brief  取栈顶元素（不出栈）
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @param  out     用于返回栈顶元素的指针
 * @return BS_OK 成功；BS_ERR_EMPTY 目标栈为空；
 *         BS_ERR_INVALID 参数为空或栈号非法
 * @note   O(1)
 */
BSStatus BS_Top(const BothStack *bs, int stackNo, ElemType *out);

/**
 * @brief  获取指定栈的栈顶下标
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @return 栈顶下标；参数非法返回 -2
 */
int BS_TopIndex(const BothStack *bs, int stackNo);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找（从栈底数起）
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @param  index   逻辑下标，范围 [0, size-1]
 * @param  out     用于返回元素值的指针
 * @return BS_OK 成功；BS_ERR_RANGE 越界；
 *         BS_ERR_INVALID 参数为空或栈号非法
 * @note   O(1)
 */
BSStatus BS_GetElem(const BothStack *bs, int stackNo, int index, ElemType *out);

/**
 * @brief  按值查找（从栈顶向栈底搜索）
 * @param  bs      双栈指针
 * @param  stackNo 栈编号
 * @param  elem    目标元素值
 * @return 距栈顶的距离（0 表示栈顶）；未找到或参数非法返回 -1
 * @note   O(n)
 */
int BS_LocateFromTop(const BothStack *bs, int stackNo, ElemType elem);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  从栈底到栈顶遍历指定栈
 * @param  bs       双栈指针
 * @param  stackNo  栈编号
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return BS_OK 成功；BS_ERR_INVALID 参数非法
 */
BSStatus BS_TraverseBottomUp(const BothStack *bs, int stackNo, bool (*callback)(ElemType elem, int index, void *ctx),
                             void *ctx);

/**
 * @brief  从栈顶到栈底遍历指定栈
 * @param  bs       双栈指针
 * @param  stackNo  栈编号
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return BS_OK 成功；BS_ERR_INVALID 参数非法
 */
BSStatus BS_TraverseTopDown(const BothStack *bs, int stackNo, bool (*callback)(ElemType elem, int index, void *ctx),
                            void *ctx);

/**
 * @brief  打印双栈的整体布局
 * @param  bs 双栈指针
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空
 * @note   以 [栈1元素 | 空闲 | 栈2元素] 的形式直观展示
 */
BSStatus BS_Print(const BothStack *bs);

/* ==================== 高级操作 ==================== */

/**
 * @brief  将栈 1 的所有元素逆序（仅栈 1）
 * @param  bs 双栈指针
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空
 * @note   O(n)；原地交换，不影响栈 2
 */
BSStatus BS_ReverseStack1(BothStack *bs);

/**
 * @brief  将栈 2 的所有元素逆序（仅栈 2）
 * @param  bs 双栈指针
 * @return BS_OK 成功；BS_ERR_INVALID 参数为空
 * @note   O(n)
 */
BSStatus BS_ReverseStack2(BothStack *bs);

/**
 * @brief  在栈 1 与栈 2 之间转移一个元素
 * @param  bs  双栈指针
 * @param  dir 方向：1 表示栈1 → 栈2，2 表示栈2 → 栈1
 * @return BS_OK 成功；BS_ERR_EMPTY 源栈为空；BS_ERR_FULL 目标栈满；
 *         BS_ERR_INVALID 参数非法
 */
BSStatus BS_TransferOne(BothStack *bs, int dir);

#endif /* BOTH_STACK_H */
