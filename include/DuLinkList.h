/**
 * @file    DuLinkList.h
 * @brief   带头结点的双向链表接口定义
 * @details 每个结点含 prior 与 next 两个指针；头结点 prior 为 NULL，
 *          尾结点 next 为 NULL。已知结点可 O(1) 前插/删除。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef DU_LINK_LIST_H
#define DU_LINK_LIST_H

#include <stdbool.h>

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/**
 * @brief 双向链表结点结构体
 *
 * data  存储有效数据（头结点中不使用）
 * prior 指向前驱结点；头结点 prior 为 NULL
 * next  指向后继结点；尾结点 next 为 NULL
 */
typedef struct DuLNode
{
    ElemType data;         /**< 数据域 */
    struct DuLNode *prior; /**< 前驱指针 */
    struct DuLNode *next;  /**< 后继指针 */
} DuLNode, *DuLinkList;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    DL_OK = 0,         /**< 操作成功 */
    DL_ERR_EMPTY = 1,  /**< 表为空 */
    DL_ERR_RANGE = 2,  /**< 位置越界 / 未找到 */
    DL_ERR_NOMEM = 3,  /**< 内存分配失败 */
    DL_ERR_INVALID = 4 /**< 无效参数 */
} DLStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化带头结点的空双向链表
 * @param  list 指向链表头指针的指针
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   头结点 prior 与 next 均置 NULL
 */
DLStatus DL_Init(DuLinkList *list);

/**
 * @brief  清空双向链表（保留头结点）
 * @param  list 链表头指针
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 * @note   释放所有数据结点，头结点 prior/next 置 NULL
 */
DLStatus DL_Clear(DuLinkList list);

/**
 * @brief  销毁双向链表（含头结点）
 * @param  list 指向链表头指针的指针
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 * @note   释放全部结点，并将 *list 置 NULL
 */
DLStatus DL_Destroy(DuLinkList *list);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取链表长度（不含头结点）
 * @param  list 链表头指针
 * @return 元素个数；参数为空返回 -1
 * @note   O(n)
 */
int DL_Length(DuLinkList list);

/**
 * @brief  判断链表是否为空
 * @param  list 链表头指针
 * @return true 为空；false 非空或参数为空
 */
bool DL_IsEmpty(DuLinkList list);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找结点
 * @param  list  链表头指针
 * @param  index 逻辑下标，范围 [0, length-1]
 * @return 结点指针；越界或参数为空返回 NULL
 * @note   O(n)；可选优化：index < length/2 从头部走，否则从尾部走
 */
DuLNode *DL_GetNode(DuLinkList list, int index);

/**
 * @brief  按位置查找元素值
 * @param  list  链表头指针
 * @param  index 逻辑下标，范围 [0, length-1]
 * @param  out   用于返回元素值的指针
 * @return DL_OK 成功；DL_ERR_RANGE 越界；DL_ERR_INVALID 参数为空
 */
DLStatus DL_GetElem(DuLinkList list, int index, ElemType *out);

/**
 * @brief  按值查找首个匹配结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 结点指针；未找到或参数为空返回 NULL
 * @note   O(n)
 */
DuLNode *DL_LocateNode(DuLinkList list, ElemType elem);

/**
 * @brief  按值查找首个匹配元素的下标
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 下标；未找到返回 -1；参数为空返回 -1
 */
int DL_LocateElem(DuLinkList list, ElemType elem);

/* ==================== 插入 ==================== */

/**
 * @brief  头插法：在头结点之后插入元素
 * @param  list 链表头指针
 * @param  elem 待插入元素
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   O(1)；需同时维护原首结点的 prior
 */
DLStatus DL_InsertHead(DuLinkList list, ElemType elem);

/**
 * @brief  尾插法：在表尾追加元素
 * @param  list 链表头指针
 * @param  elem 待追加元素
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   O(n)；若额外维护尾指针可优化为 O(1)
 */
DLStatus DL_PushBack(DuLinkList list, ElemType elem);

/**
 * @brief  在指定位置插入元素（前插）
 * @param  list  链表头指针
 * @param  index 插入位置，范围 [0, length]
 * @param  elem  待插入元素
 * @return DL_OK 成功；DL_ERR_RANGE 越界；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   O(n)
 */
DLStatus DL_InsertAt(DuLinkList list, int index, ElemType elem);

/**
 * @brief  在指定结点之后插入（后插）
 * @param  node 目标结点指针（不可为 NULL）
 * @param  elem 待插入元素
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   O(1)；双向链表的核心优势之一
 */
DLStatus DL_InsertAfter(DuLNode *node, ElemType elem);

/**
 * @brief  在指定结点之前插入（前插）
 * @param  node 目标结点指针（不可为 NULL）
 * @param  elem 待插入元素
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   O(1)；双向链表相对单链表的关键优势
 */
DLStatus DL_InsertBefore(DuLNode *node, ElemType elem);

/* ==================== 删除 ==================== */

/**
 * @brief  删除指定位置的结点
 * @param  list  链表头指针
 * @param  index 删除位置，范围 [0, length-1]
 * @param  out   用于返回被删元素的指针，可为 NULL
 * @return DL_OK 成功；DL_ERR_EMPTY 表空；DL_ERR_RANGE 越界；DL_ERR_INVALID 参数为空
 * @note   O(n)
 */
DLStatus DL_DeleteAt(DuLinkList list, int index, ElemType *out);

/**
 * @brief  删除指定结点（已知结点指针）
 * @param  node 待删除结点指针（不可为头结点）
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 * @note   O(1)；双向链表的核心优势之一
 */
DLStatus DL_DeleteNode(DuLNode *node, ElemType *out);

/**
 * @brief  删除首个值等于 elem 的结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return DL_OK 成功；DL_ERR_EMPTY 表空；DL_ERR_RANGE 未找到；DL_ERR_INVALID 参数为空
 */
DLStatus DL_RemoveElem(DuLinkList list, ElemType elem);

/**
 * @brief  删除表头结点（第一个数据结点）
 * @param  list 链表头指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return DL_OK 成功；DL_ERR_EMPTY 表空；DL_ERR_INVALID 参数为空
 * @note   O(1)
 */
DLStatus DL_PopFront(DuLinkList list, ElemType *out);

/**
 * @brief  删除表尾结点
 * @param  list 链表头指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return DL_OK 成功；DL_ERR_EMPTY 表空；DL_ERR_INVALID 参数为空
 * @note   O(n)；若维护尾指针可优化为 O(1)
 */
DLStatus DL_PopBack(DuLinkList list, ElemType *out);

/* ==================== 建表 ==================== */

/**
 * @brief  头插法批量建表
 * @param  list 指向链表头指针的指针
 * @param  arr  元素数组
 * @param  n    元素个数
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   结果顺序与数组相反
 */
DLStatus DL_CreateHead(DuLinkList *list, const ElemType *arr, int n);

/**
 * @brief  尾插法批量建表
 * @param  list 指向链表头指针的指针
 * @param  arr  元素数组
 * @param  n    元素个数
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   结果顺序与数组一致
 */
DLStatus DL_CreateTail(DuLinkList *list, const ElemType *arr, int n);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  正向遍历（头 -> 尾）
 * @param  list     链表头指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 */
DLStatus DL_TraverseForward(DuLinkList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  反向遍历（尾 -> 头）
 * @param  list     链表头指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 * @note   双向链表独有的遍历方式
 */
DLStatus DL_TraverseBackward(DuLinkList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印链表内容（正向）
 * @param  list 链表头指针
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 */
DLStatus DL_Print(DuLinkList list);

/**
 * @brief  打印链表内容（反向）
 * @param  list 链表头指针
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 */
DLStatus DL_PrintReverse(DuLinkList list);

/* ==================== 高级操作 ==================== */

/**
 * @brief  原地反转双向链表（不含头结点）
 * @param  list 链表头指针
 * @return DL_OK 成功；DL_ERR_INVALID 参数为空
 * @note   O(n)；交换每个结点的 prior 与 next 后重新连接头结点
 */
DLStatus DL_Reverse(DuLinkList list);

/**
 * @brief  删除所有值等于 elem 的结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 实际删除的结点数；参数为空返回 -1
 * @note   O(n)
 */
int DL_RemoveAll(DuLinkList list, ElemType elem);

/**
 * @brief  去重（仅适用于有序双向链表）
 * @param  list 链表头指针
 * @return 去重删除的结点数；参数为空返回 -1
 * @note   O(n)
 */
int DL_UniqueSorted(DuLinkList list);

/**
 * @brief  合并两个有序双向链表到新表
 * @param  a   有序双向链表 A
 * @param  b   有序双向链表 B
 * @param  out 结果链表头指针的指针（需先 DL_Init）
 * @return DL_OK 成功；DL_ERR_NOMEM 内存不足；DL_ERR_INVALID 参数为空
 * @note   O(m+n)
 */
DLStatus DL_MergeSorted(DuLinkList a, DuLinkList b, DuLinkList *out);

#endif /* DU_LINK_LIST_H */
