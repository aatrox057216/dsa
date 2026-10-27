/**
 * @file    LinkList.h
 * @brief   带头结点的单链表（Singly Linked List with Dummy Head）接口定义
 * @details 采用头结点统一边界处理；区分头插法与尾插法两种建表方式。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <stdbool.h>

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/**
 * @brief 单链表结点结构体
 *
 * data 存储有效数据（头结点中不使用）
 * next 指向下一个结点；尾结点 next 为 NULL
 */
typedef struct LNode
{
    ElemType data;      /**< 数据域 */
    struct LNode *next; /**< 指针域 */
} LNode, *LinkList;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    LL_OK = 0,         /**< 操作成功 */
    LL_ERR_EMPTY = 1,  /**< 表为空 */
    LL_ERR_RANGE = 2,  /**< 位置越界 / 未找到 */
    LL_ERR_NOMEM = 3,  /**< 内存分配失败 */
    LL_ERR_INVALID = 4 /**< 无效参数 */
} LLStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化带头结点的空链表
 * @param  list 指向链表头指针的指针
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   分配头结点，head->next = NULL
 */
LLStatus LL_Init(LinkList *list);

/**
 * @brief  清空链表（保留头结点）
 * @param  list 链表头指针
 * @return LL_OK 成功；LL_ERR_INVALID 参数为空
 * @note   释放所有数据结点，仅保留头结点
 */
LLStatus LL_Clear(LinkList list);

/**
 * @brief  销毁链表（含头结点）
 * @param  list 指向链表头指针的指针
 * @return LL_OK 成功；LL_ERR_INVALID 参数为空
 * @note   释放全部结点，并将 *list 置 NULL
 */
LLStatus LL_Destroy(LinkList *list);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取链表长度（不含头结点）
 * @param  list 链表头指针
 * @return 元素个数；参数为空返回 -1
 * @note   时间复杂度 O(n)
 */
int LL_Length(LinkList list);

/**
 * @brief  判断链表是否为空
 * @param  list 链表头指针
 * @return true 为空；false 非空或参数为空
 */
bool LL_IsEmpty(LinkList list);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找结点（返回结点指针）
 * @param  list  链表头指针
 * @param  index 逻辑下标，范围 [0, length-1]
 * @return 结点指针；越界或参数为空返回 NULL
 * @note   O(n)；返回值可用于后续 O(1) 增删
 */
LNode *LL_GetNode(LinkList list, int index);

/**
 * @brief  按位置查找元素值
 * @param  list  链表头指针
 * @param  index 逻辑下标，范围 [0, length-1]
 * @param  out   用于返回元素值的指针
 * @return LL_OK 成功；LL_ERR_RANGE 越界；LL_ERR_INVALID 参数为空
 */
LLStatus LL_GetElem(LinkList list, int index, ElemType *out);

/**
 * @brief  按值查找首个匹配结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 结点指针；未找到或参数为空返回 NULL
 * @note   O(n)
 */
LNode *LL_LocateNode(LinkList list, ElemType elem);

/**
 * @brief  按值查找首个匹配元素的下标
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 下标；未找到返回 -1；参数为空返回 -1
 */
int LL_LocateElem(LinkList list, ElemType elem);

/* ==================== 插入 ==================== */

/**
 * @brief  头插法：在头结点之后插入元素
 * @param  list 链表头指针
 * @param  elem 待插入元素
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   O(1)；新元素成为第一个数据结点
 */
LLStatus LL_InsertHead(LinkList list, ElemType elem);

/**
 * @brief  尾插法：在表尾追加元素
 * @param  list 链表头指针
 * @param  elem 待追加元素
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   O(n)；若需 O(1) 尾插可额外维护尾指针
 */
LLStatus LL_PushBack(LinkList list, ElemType elem);

/**
 * @brief  在指定位置插入元素（前插）
 * @param  list  链表头指针
 * @param  index 插入位置，范围 [0, length]
 * @param  elem  待插入元素
 * @return LL_OK 成功；LL_ERR_RANGE 越界；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   O(n)；index = 0 等价于头插，index = length 等价于尾插
 */
LLStatus LL_InsertAt(LinkList list, int index, ElemType elem);

/**
 * @brief  在指定结点之后插入（后插）
 * @param  node 目标结点指针（不可为头结点）
 * @param  elem 待插入元素
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   O(1)；常用于已知结点场景
 */
LLStatus LL_InsertAfter(LNode *node, ElemType elem);

/**
 * @brief  在指定结点之前插入（前插）
 * @param  list 链表头指针（用于定位前驱）
 * @param  node 目标结点指针
 * @param  elem 待插入元素
 * @return LL_OK 成功；LL_ERR_RANGE 未找到；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   O(n)；通过"偷梁换柱"可优化为 O(1)（见实现注释）
 */
LLStatus LL_InsertBefore(LinkList list, LNode *node, ElemType elem);

/* ==================== 删除 ==================== */

/**
 * @brief  删除指定位置的结点
 * @param  list  链表头指针
 * @param  index 删除位置，范围 [0, length-1]
 * @param  out   用于返回被删元素的指针，可为 NULL
 * @return LL_OK 成功；LL_ERR_EMPTY 表空；
 *         LL_ERR_RANGE 越界；LL_ERR_INVALID 参数为空
 * @note   O(n)
 */
LLStatus LL_DeleteAt(LinkList list, int index, ElemType *out);

/**
 * @brief  删除首个值等于 elem 的结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return LL_OK 成功；LL_ERR_EMPTY 表空；
 *         LL_ERR_RANGE 未找到；LL_ERR_INVALID 参数为空
 */
LLStatus LL_RemoveElem(LinkList list, ElemType elem);

/**
 * @brief  删除表头结点（第一个数据结点）
 * @param  list 链表头指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return LL_OK 成功；LL_ERR_EMPTY 表空；LL_ERR_INVALID 参数为空
 * @note   O(1)
 */
LLStatus LL_PopFront(LinkList list, ElemType *out);

/**
 * @brief  删除表尾结点
 * @param  list 链表头指针
 * @param  out  用于返回被删元素的指针，可为 NULL
 * @return LL_OK 成功；LL_ERR_EMPTY 表空；LL_ERR_INVALID 参数为空
 * @note   O(n)
 */
LLStatus LL_PopBack(LinkList list, ElemType *out);

/* ==================== 建表 ==================== */

/**
 * @brief  头插法批量建表
 * @param  list 指向链表头指针的指针
 * @param  arr  元素数组
 * @param  n    元素个数
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   结果顺序与数组相反；时间复杂度 O(n)
 */
LLStatus LL_CreateHead(LinkList *list, const ElemType *arr, int n);

/**
 * @brief  尾插法批量建表
 * @param  list 指向链表头指针的指针
 * @param  arr  元素数组
 * @param  n    元素个数
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   结果顺序与数组一致；时间复杂度 O(n)
 */
LLStatus LL_CreateTail(LinkList *list, const ElemType *arr, int n);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  遍历链表并对每个元素调用回调
 * @param  list     链表头指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return LL_OK 成功；LL_ERR_INVALID 参数为空
 */
LLStatus LL_Traverse(LinkList list, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印链表内容
 * @param  list 链表头指针
 * @return LL_OK 成功；LL_ERR_INVALID 参数为空
 */
LLStatus LL_Print(LinkList list);

/* ==================== 高级操作 ==================== */

/**
 * @brief  原地反转链表（不含头结点）
 * @param  list 链表头指针
 * @return LL_OK 成功；LL_ERR_INVALID 参数为空
 * @note   O(n)；三指针法，头结点保持不动
 */
LLStatus LL_Reverse(LinkList list);

/**
 * @brief  删除所有值等于 elem 的结点
 * @param  list 链表头指针
 * @param  elem 目标元素值
 * @return 实际删除的结点数；参数为空返回 -1
 * @note   O(n)
 */
int LL_RemoveAll(LinkList list, ElemType elem);

/**
 * @brief  去重（仅适用于有序链表）
 * @param  list 链表头指针
 * @return 去重删除的结点数；参数为空返回 -1
 * @note   O(n)；要求链表已升序
 */
int LL_UniqueSorted(LinkList list);

/**
 * @brief  合并两个有序链表到新表（尾插法构建）
 * @param  a   有序链表 A
 * @param  b   有序链表 B
 * @param  out 结果链表头指针的指针（需先 LL_Init）
 * @return LL_OK 成功；LL_ERR_NOMEM 内存不足；LL_ERR_INVALID 参数为空
 * @note   O(m+n)
 */
LLStatus LL_MergeSorted(LinkList a, LinkList b, LinkList *out);

/**
 * @brief  查找中间结点（快慢指针）
 * @param  list 链表头指针
 * @return 中间结点指针；空表或参数为空返回 NULL
 * @note   O(n)；偶数个结点时返回靠后的中间结点
 */
LNode *LL_MiddleNode(LinkList list);

/**
 * @brief  判断链表是否有环（快慢指针）
 * @param  list 链表头指针
 * @return true 有环；false 无环或参数为空
 */
bool LL_HasCycle(LinkList list);

#endif /* LINK_LIST_H */
