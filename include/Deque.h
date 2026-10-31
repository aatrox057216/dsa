/**
 * @file    Deque.h
 * @brief   链式双端队列（双向链表、不带头结点）的接口声明。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

/** @brief 双端队列结点结构体 */
typedef struct DNode
{
    int data;           /**< 数据域 */
    struct DNode *prev; /**< 指向前驱结点的指针 */
    struct DNode *next; /**< 指向后继结点的指针 */
} DNode, *DequePtr;

/** @brief 双端队列结构体（不带头结点） */
typedef struct
{
    DequePtr front; /**< 队头指针 */
    DequePtr rear;  /**< 队尾指针 */
    int size;       /**< 当前双端队列中元素的个数 */
} Deque;

/**
 * @brief  初始化双端队列。
 * @param  D 待初始化的双端队列指针。
 * @post   front = rear = NULL，size = 0。
 */
void DequeInit(Deque *D);

/**
 * @brief  销毁双端队列，释放全部结点。
 * @param  D 双端队列指针。
 * @post   front = rear = NULL，size = 0。
 */
void DequeDestroy(Deque *D);

/**
 * @brief  清空双端队列，释放所有元素结点，保留队列结构。
 * @param  D 双端队列指针。
 * @post   front = rear = NULL，size = 0。
 */
void DequeClear(Deque *D);

/**
 * @brief  判断双端队列是否为空。
 * @param  D 双端队列指针（只读）。
 * @return 空返回 true，否则返回 false。
 */
bool DequeIsEmpty(const Deque *D);

/**
 * @brief  获取双端队列当前元素个数。
 * @param  D 双端队列指针（只读）。
 * @return 元素个数。
 */
int DequeSize(const Deque *D);

/**
 * @brief  从队头插入元素 e。
 * @param  D 双端队列指针。
 * @param  e 待插入元素。
 * @return 成功返回 true，内存分配失败返回 false。
 * @note   头插法，时间复杂度 O(1)。
 */
bool DequePushFront(Deque *D, int e);

/**
 * @brief  从队尾插入元素 e。
 * @param  D 双端队列指针。
 * @param  e 待插入元素。
 * @return 成功返回 true，内存分配失败返回 false。
 * @note   尾插法，时间复杂度 O(1)。
 */
bool DequePushBack(Deque *D, int e);

/**
 * @brief  从队头删除元素并用 e 返回其值。
 * @param  D 双端队列指针。
 * @param  e 输出参数，保存被删除的队头元素。
 * @return 成功返回 true，队列为空返回 false。
 */
bool DequePopFront(Deque *D, int *e);

/**
 * @brief  从队尾删除元素并用 e 返回其值。
 * @param  D 双端队列指针。
 * @param  e 输出参数，保存被删除的队尾元素。
 * @return 成功返回 true，队列为空返回 false。
 */
bool DequePopBack(Deque *D, int *e);

/**
 * @brief  获取队头元素，不删除。
 * @param  D 双端队列指针（只读）。
 * @param  e 输出参数，保存队头元素。
 * @return 成功返回 true，队列为空返回 false。
 */
bool DequeGetFront(const Deque *D, int *e);

/**
 * @brief  获取队尾元素，不删除。
 * @param  D 双端队列指针（只读）。
 * @param  e 输出参数，保存队尾元素。
 * @return 成功返回 true，队列为空返回 false。
 */
bool DequeGetBack(const Deque *D, int *e);

/**
 * @brief  从队头到队尾遍历打印双端队列元素。
 * @param  D 双端队列指针（只读）。
 */
void DequeTraverseForward(const Deque *D);

/**
 * @brief  从队尾到队头逆序遍历打印双端队列元素。
 * @param  D 双端队列指针（只读）。
 */
void DequeTraverseBackward(const Deque *D);

#endif /* DEQUE_H */
