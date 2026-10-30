/**
 * @file    LinkQueue.h
 * @brief   链队列（带头结点）的接口声明，依据严蔚敏《数据结构》C语言版。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <stdbool.h>

/** @brief 队列结点结构体 */
typedef struct QueueNode
{
    int data;               /**< 数据域 */
    struct QueueNode *next; /**< 指向下一个结点的指针 */
} QueueNode, *QueuePtr;

/** @brief 链队列结构体（带头结点） */
typedef struct
{
    QueuePtr front; /**< 队头指针，指向头结点 */
    QueuePtr rear;  /**< 队尾指针，指向队尾结点 */
    int size;       /**< 队列当前元素个数 */
} LinkQueue;

/**
 * @brief  初始化链队列。
 * @param  Q 待初始化的队列指针。
 * @return 成功返回 true，内存分配失败返回 false。
 * @note   会创建一个头结点，front 与 rear 同时指向它，size 置 0。
 */
bool InitQueue(LinkQueue *Q);

/**
 * @brief  销毁链队列，释放全部结点（含头结点）。
 * @param  Q 队列指针。
 * @post   Q->front 与 Q->rear 均置为 NULL，size 置 0。
 */
void DestroyQueue(LinkQueue *Q);

/**
 * @brief  清空队列，保留头结点，释放所有元素结点。
 * @param  Q 队列指针。
 * @post   front 与 rear 重新指向头结点，size 置 0。
 */
void ClearQueue(LinkQueue *Q);

/**
 * @brief  判断队列是否为空。
 * @param  Q 队列指针（只读）。
 * @return 空返回 true，否则返回 false。
 */
bool QueueEmpty(const LinkQueue *Q);

/**
 * @brief  获取队列当前元素个数。
 * @param  Q 队列指针（只读）。
 * @return 元素个数。
 */
int QueueLength(const LinkQueue *Q);

/**
 * @brief  入队：将元素 e 插入队尾。
 * @param  Q 队列指针。
 * @param  e 待入队元素。
 * @return 成功返回 true，内存分配失败返回 false。
 * @note   尾插法，时间复杂度 O(1)。
 */
bool EnQueue(LinkQueue *Q, int e);

/**
 * @brief  出队：删除队头元素并用 e 返回其值。
 * @param  Q 队列指针。
 * @param  e 输出参数，保存被删除的队头元素。
 * @return 成功返回 true，队列为空返回 false。
 * @warning 删除最后一个元素后必须执行 rear = front，防止尾指针悬空。
 */
bool DeQueue(LinkQueue *Q, int *e);

/**
 * @brief  取队头元素，不删除。
 * @param  Q 队列指针（只读）。
 * @param  e 输出参数，保存队头元素。
 * @return 成功返回 true，队列为空返回 false。
 */
bool GetHead(const LinkQueue *Q, int *e);

/**
 * @brief  从队头到队尾遍历打印队列元素。
 * @param  Q 队列指针（只读）。
 */
void QueueTraverse(const LinkQueue *Q);

#endif /* LINK_QUEUE_H */
