/**
 * @file    SqQueue.h
 * @brief   循环队列（顺序存储）的接口声明，依据严蔚敏《数据结构》C语言版。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#ifndef SQ_QUEUE_H
#define SQ_QUEUE_H

#include <stdbool.h>

/** @brief 队列最大容量（实际可存 MAXQSIZE - 1 个元素） */
#define MAXQSIZE 100

/** @brief 队列元素类型 */
typedef int QElemType;

/**
 * @brief 循环队列结构体（牺牲一个单元判满）
 */
typedef struct
{
    QElemType *base; /**< 指向队列存储空间的基址 */
    int front;       /**< 队头指针，指向队头元素 */
    int rear;        /**< 队尾指针，指向队尾元素的下一个位置 */
} SqQueue;

/**
 * @brief  初始化循环队列，动态分配 MAXQSIZE 个元素空间。
 * @param  Q 待初始化的队列指针。
 * @return 成功返回 true，内存分配失败返回 false。
 * @post   front = rear = 0。
 */
bool Sq_InitQueue(SqQueue *Q);

/**
 * @brief  销毁循环队列，释放动态数组。
 * @param  Q 队列指针。
 * @post   base 置为 NULL，front = rear = 0。
 */
void Sq_DestroyQueue(SqQueue *Q);

/**
 * @brief  清空队列，仅重置首尾指针，不释放空间。
 * @param  Q 队列指针。
 * @post   front = rear = 0。
 */
void Sq_ClearQueue(SqQueue *Q);

/**
 * @brief  判断队列是否为空。
 * @param  Q 队列指针（只读）。
 * @return 空返回 true，否则返回 false。
 */
bool Sq_QueueEmpty(const SqQueue *Q);

/**
 * @brief  判断队列是否已满（牺牲一个单元判满）。
 * @param  Q 队列指针（只读）。
 * @return 满返回 true，否则返回 false。
 */
bool Sq_QueueFull(const SqQueue *Q);

/**
 * @brief  获取队列当前元素个数。
 * @param  Q 队列指针（只读）。
 * @return 元素个数，范围 [0, MAXQSIZE-1]。
 */
int Sq_QueueLength(const SqQueue *Q);

/**
 * @brief  入队：将元素 e 插入队尾。
 * @param  Q 队列指针。
 * @param  e 待入队元素。
 * @return 成功返回 true，队满返回 false。
 * @note   rear 循环后移：(rear + 1) % MAXQSIZE。
 */
bool Sq_EnQueue(SqQueue *Q, QElemType e);

/**
 * @brief  出队：删除队头元素并用 e 返回其值。
 * @param  Q 队列指针。
 * @param  e 输出参数，保存被删除的队头元素。
 * @return 成功返回 true，队空返回 false。
 * @note   front 循环后移：(front + 1) % MAXQSIZE。
 */
bool Sq_DeQueue(SqQueue *Q, QElemType *e);

/**
 * @brief  取队头元素，不删除。
 * @param  Q 队列指针（只读）。
 * @param  e 输出参数，保存队头元素。
 * @return 成功返回 true，队空返回 false。
 */
bool Sq_GetHead(const SqQueue *Q, QElemType *e);

/**
 * @brief  从队头到队尾遍历打印队列元素。
 * @param  Q 队列指针（只读）。
 */
void Sq_QueueTraverse(const SqQueue *Q);

#endif /* SQ_QUEUE_H */
