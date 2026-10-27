/**
 * @file    CircularList.h
 * @brief   带头结点的循环单链表接口定义
 * @details 尾结点 next 指向头结点，形成闭环；判空条件为 head->next == head。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <stdbool.h>

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/**
 * @brief 循环单链表结点结构体
 *
 * data 存储有效数据（头结点中不使用）
 * next 指向下一个结点；尾结点 next 指向头结点（而非 NULL）
 */
typedef struct LNode
{
    ElemType data;      /**< 数据域 */
    struct LNode *next; /**< 指针域，尾结点指向头结点 */
} LNode, *CircularList;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    CL_OK = 0,         /**< 操作成功 */
    CL_ERR_EMPTY = 1,  /**< 表为空 */
    CL_ERR_RANGE = 2,  /**< 位置越界 / 未找到 */
    CL_ERR_NOMEM = 3,  /**< 内存分配失败 */
    CL_ERR_INVALID = 4 /**< 无效参数 */
} CLStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化带头结点的空循环链表
 * @param  list 指向链表头指针的指针
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   分配头结点后 head->next 指向 head 自身
 */
CLStatus CL_Init(CircularList *list);

/**
 * @brief  清空循环链表（保留头结点）
 * @param  list 链表头指针
 * @return CL_OK 成功；CL_ERR_INVALID 参数为空
 * @note   释放所有数据结点，头结点 next 重新指向自身
 */
CLStatus CL_Clear(CircularList list);

/**
 * @brief  销毁循环链表（含头结点）
 * @param  list 指向链表头指针的指针
 * @return CL_OK 成功；CL_ERR_INVALID 参数为空
 * @note   释放全部结点，并将 *list 置 NULL
 */
CLStatus CL_Destroy(CircularList *list);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取链表长度（不含头结点）
 * @param  list 链表头指针
 * @return 元素个数；参数为空返回 -1
 * @note   O(n)；从 head->next 遍历至 head
 */
int CL_Length(CircularList list);

/**
 * @brief  判断链表是否为空
 * @param  list 链表头指针
 * @return true 为空；false 非空或参数为空
 * @note   判空条件：head->next == head
 */
bool CL_IsEmpty(CircularList list);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找结点
 * @param  list  链表头指针
 * @param  index 逻辑下标，范围 [0, length-1]
 * @return 结点指针；越界或参数为空返回 NULL
 */
LNode *CL_GetNode(CircularList list, int index);

/**
 * @brief  按位置查找元素值
 * @param  list  链表头指针
 * @param  index 逻辑下标，范围 [0, length-1]
 * @param  out   用于返回元素值的指针
 * @return CL_OK 成功；CL_ERR_RANGE 越界；CL_ERR_INVALID 参数为空
 */
CLStatus CL_GetElem(CircularList list, int index, ElemType *out);

/**
 * @brief  按值查找首个匹配结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 结点指针；未找到或参数为空返回 NULL
 */
LNode *CL_LocateNode(CircularList list, ElemType elem);

/**
 * @brief  按值查找首个匹配元素的下标
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 下标；未找到返回 -1；参数为空返回 -1
 */
int CL_LocateElem(CircularList list, ElemType elem);

/* ==================== 插入 ==================== */

/**
 * @brief  头插法：在头结点之后插入元素
 * @param  list 链表头指针
 * @param  elem 待插入元素
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   O(1)
 */
CLStatus CL_InsertHead(CircularList list, ElemType elem);

/**
 * @brief  尾插法：在表尾追加元素
 * @param  list 链表头指针
 * @param  elem 待追加元素
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   O(n)；与单链表不同，尾结点 next 需指向头结点
 */
CLStatus CL_PushBack(CircularList list, ElemType elem);

/**
 * @brief  在指定位置插入元素
 * @param  list  链表头指针
 * @param  index 插入位置，范围 [0, length]
 * @param  elem  待插入元素
 * @return CL_OK 成功；CL_ERR_RANGE 越界；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 */
CLStatus CL_InsertAt(CircularList list, int index, ElemType elem);

/**
 * @brief  在指定结点之后插入（后插）
 * @param  node 目标结点指针
 * @param  elem 待插入元素
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   O(1)
 */
CLStatus CL_InsertAfter(LNode *node, ElemType elem);

/* ==================== 删除 ==================== */

/**
 * @brief  删除指定位置的结点
 * @param  list  链表头指针
 * @param  index 删除位置，范围 [0, length-1]
 * @param  out   用于返回被删元素的指针，可为 NULL
 * @return CL_OK 成功；CL_ERR_EMPTY 表空；CL_ERR_RANGE 越界；CL_ERR_INVALID 参数为空
 */
CLStatus CL_DeleteAt(CircularList list, int index, ElemType *out);

/**
 * @brief  删除首个值等于 elem 的结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return CL_OK 成功；CL_ERR_EMPTY 表空；CL_ERR_RANGE 未找到；CL_ERR_INVALID 参数为空
 */
CLStatus CL_RemoveElem(CircularList list, ElemType elem);

/**
 * @brief  删除表头结点（第一个数据结点）
 * @param  list 链表头指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return CL_OK 成功；CL_ERR_EMPTY 表空；CL_ERR_INVALID 参数为空
 */
CLStatus CL_PopFront(CircularList list, ElemType *out);

/**
 * @brief  删除表尾结点
 * @param  list 链表头指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return CL_OK 成功；CL_ERR_EMPTY 表空；CL_ERR_INVALID 参数为空
 * @note   O(n)
 */
CLStatus CL_PopBack(CircularList list, ElemType *out);

/* ==================== 建表 ==================== */

/**
 * @brief  头插法批量建表
 * @param  list 指向链表头指针的指针
 * @param  arr  元素数组
 * @param  n    元素个数
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   结果顺序与数组相反
 */
CLStatus CL_CreateHead(CircularList *list, const ElemType *arr, int n);

/**
 * @brief  尾插法批量建表
 * @param  list 指向链表头指针的指针
 * @param  arr  元素数组
 * @param  n    元素个数
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   结果顺序与数组一致
 */
CLStatus CL_CreateTail(CircularList *list, const ElemType *arr, int n);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  遍历循环链表并对每个元素调用回调
 * @param  list     链表头指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return CL_OK 成功；CL_ERR_INVALID 参数为空
 * @note   终止条件为 cur != head，而非 cur != NULL
 */
CLStatus CL_Traverse(CircularList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印链表内容
 * @param  list 链表头指针
 * @return CL_OK 成功；CL_ERR_INVALID 参数为空
 */
CLStatus CL_Print(CircularList list);

/* ==================== 高级操作 ==================== */

/**
 * @brief  原地反转循环链表（不含头结点）
 * @param  list 链表头指针
 * @return CL_OK 成功；CL_ERR_INVALID 参数为空
 * @note   O(n)；反转后需修复尾结点指向头结点
 */
CLStatus CL_Reverse(CircularList list);

/**
 * @brief  删除所有值等于 elem 的结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 实际删除的结点数；参数为空返回 -1
 */
int CL_RemoveAll(CircularList list, ElemType elem);

/**
 * @brief  去重（仅适用于有序循环链表）
 * @param  list 链表头指针
 * @return 去重删除的结点数；参数为空返回 -1
 */
int CL_UniqueSorted(CircularList list);

/**
 * @brief  合并两个有序循环链表到新表
 * @param  a   有序循环链表 A
 * @param  b   有序循环链表 B
 * @param  out 结果循环链表头指针的指针（需先 CL_Init）
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 */
CLStatus CL_MergeSorted(CircularList a, CircularList b, CircularList *out);

/**
 * @brief  约瑟夫环问题：每数到 m 出列
 * @param  n 总人数（编号 1..n）
 * @param  m 报数上限
 * @param  outOrder 输出出列顺序的数组（调用方分配，长度 >= n）
 * @return CL_OK 成功；CL_ERR_NOMEM 内存不足；CL_ERR_INVALID 参数为空
 * @note   内部构建循环链表，演示环形结构的典型应用
 */
CLStatus CL_Josephus(int n, int m, int *outOrder);

#endif /* CIRCULAR_LIST_H */
