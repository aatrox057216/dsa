/**
 * @file    CircularQueue.h
 * @brief   定长数组循环队列的接口声明，依据严蔚敏《数据结构》C语言版。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdbool.h>

/** @brief 数组最大长度（实际可存 MAXSIZE - 1 个元素） */
#define MAXSIZE 100

/**
 * @brief 定长数组循环队列结构体（牺牲一个单元判满）
 */
typedef struct
{
    int data[MAXSIZE]; /**< 数组用于存储队列元素 */
    int front;         /**< 队头指针，指向队头元素 */
    int rear;          /**< 队尾指针，指向队尾元素的下一个位置 */
} CircularQueue;

/**
 * @brief  初始化循环队列。
 * @param  Q 待初始化的队列指针。
 * @post   front = rear = 0。
 * @note   数组为内嵌定长空间，无需动态分配。
 */
void Ci_InitQueue(CircularQueue *Q);

/**
 * @brief  清空队列，仅重置首尾指针，数据区内容不作清除。
 * @param  Q 队列指针。
 * @post   front = rear = 0。
 */
void Ci_ClearQueue(CircularQueue *Q);

/**
 * @brief  判断队列是否为空。
 * @param  Q 队列指针（只读）。
 * @return 空返回 true，否则返回 false。
 */
bool Ci_QueueEmpty(const CircularQueue *Q);

/**
 * @brief  判断队列是否已满（牺牲一个单元判满）。
 * @param  Q 队列指针（只读）。
 * @return 满返回 true，否则返回 false。
 */
bool Ci_QueueFull(const CircularQueue *Q);

/**
 * @brief  获取队列当前元素个数。
 * @param  Q 队列指针（只读）。
 * @return 元素个数，范围 [0, MAXSIZE-1]。
 */
int Ci_QueueLength(const CircularQueue *Q);

/**
 * @brief  入队：将元素 e 插入队尾。
 * @param  Q 队列指针。
 * @param  e 待入队元素。
 * @return 成功返回 true，队满返回 false。
 * @note   rear 循环后移：(rear + 1) % MAXSIZE。
 */
bool Ci_EnQueue(CircularQueue *Q, int e);

/**
 * @brief  出队：删除队头元素并用 e 返回其值。
 * @param  Q 队列指针。
 * @param  e 输出参数，保存被删除的队头元素。
 * @return 成功返回 true，队空返回 false。
 * @note   front 循环后移：(front + 1) % MAXSIZE。
 */
bool Ci_DeQueue(CircularQueue *Q, int *e);

/**
 * @brief  取队头元素，不删除。
 * @param  Q 队列指针（只读）。
 * @param  e 输出参数，保存队头元素。
 * @return 成功返回 true，队空返回 false。
 */
bool Ci_GetHead(const CircularQueue *Q, int *e);

/**
 * @brief  从队头到队尾遍历打印队列元素。
 * @param  Q 队列指针（只读）。
 */
void Ci_QueueTraverse(const CircularQueue *Q);

#endif /* CIRCULAR_QUEUE_H */
