/**
 * @file    CircularQueue.c
 * @brief   定长数组循环队列的具体实现。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#include "CircularQueue.h"
#include <stdio.h>

void Ci_InitQueue(CircularQueue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    Q->front = Q->rear = 0; /* 定长数组，无需分配空间 */
}

void Ci_ClearQueue(CircularQueue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    Q->front = Q->rear = 0; /* 逻辑清空，数组内容保留 */
}

bool Ci_QueueEmpty(const CircularQueue *Q)
{
    if (Q == NULL)
    {
        return true;
    }
    return Q->front == Q->rear;
}

bool Ci_QueueFull(const CircularQueue *Q)
{
    if (Q == NULL)
    {
        return false;
    }
    return (Q->rear + 1) % MAXSIZE == Q->front; /* 牺牲一个单元判满 */
}

int Ci_QueueLength(const CircularQueue *Q)
{
    if (Q == NULL)
    {
        return 0;
    }
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

bool Ci_EnQueue(CircularQueue *Q, int e)
{
    if (Q == NULL || Ci_QueueFull(Q))
    {
        return false;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE; /* 循环后移 */
    return true;
}

bool Ci_DeQueue(CircularQueue *Q, int *e)
{
    if (Q == NULL || Ci_QueueEmpty(Q))
    {
        return false;
    }
    if (e != NULL)
    {
        *e = Q->data[Q->front];
    }
    Q->front = (Q->front + 1) % MAXSIZE; /* 循环后移 */
    return true;
}

bool Ci_GetHead(const CircularQueue *Q, int *e)
{
    if (Q == NULL || Ci_QueueEmpty(Q))
    {
        return false;
    }
    if (e != NULL)
    {
        *e = Q->data[Q->front];
    }
    return true;
}

void Ci_QueueTraverse(const CircularQueue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE)
    {
        printf("%d ", Q->data[i]);
    }
    printf("\n");
}
