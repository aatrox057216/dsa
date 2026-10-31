/**
 * @file    SqQueue.c
 * @brief   循环队列（顺序存储）的具体实现。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#include "SqQueue.h"
#include <stdio.h>
#include <stdlib.h>

bool Sq_InitQueue(SqQueue *Q)
{
    if (Q == NULL)
    {
        return false;
    }
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (Q->base == NULL)
    {
        return false;
    }
    Q->front = Q->rear = 0;
    return true;
}

void Sq_DestroyQueue(SqQueue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    free(Q->base);
    Q->base = NULL;
    Q->front = Q->rear = 0;
}

void Sq_ClearQueue(SqQueue *Q)
{
    if (Q == NULL || Q->base == NULL)
    {
        return;
    }
    Q->front = Q->rear = 0; /* 逻辑清空，空间保留 */
}

bool Sq_QueueEmpty(const SqQueue *Q)
{
    if (Q == NULL || Q->base == NULL)
    {
        return true;
    }
    return Q->front == Q->rear;
}

bool Sq_QueueFull(const SqQueue *Q)
{
    if (Q == NULL || Q->base == NULL)
    {
        return false;
    }
    return (Q->rear + 1) % MAXQSIZE == Q->front; /* 牺牲一个单元判满 */
}

int Sq_QueueLength(const SqQueue *Q)
{
    if (Q == NULL || Q->base == NULL)
    {
        return 0;
    }
    return (Q->rear - Q->front + MAXQSIZE) % MAXQSIZE;
}

bool Sq_EnQueue(SqQueue *Q, QElemType e)
{
    if (Q == NULL || Q->base == NULL || Sq_QueueFull(Q))
    {
        return false;
    }
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXQSIZE; /* 循环后移 */
    return true;
}

bool Sq_DeQueue(SqQueue *Q, QElemType *e)
{
    if (Q == NULL || Q->base == NULL || Sq_QueueEmpty(Q))
    {
        return false;
    }
    if (e != NULL)
    {
        *e = Q->base[Q->front];
    }
    Q->front = (Q->front + 1) % MAXQSIZE; /* 循环后移 */
    return true;
}

bool Sq_GetHead(const SqQueue *Q, QElemType *e)
{
    if (Q == NULL || Q->base == NULL || Sq_QueueEmpty(Q))
    {
        return false;
    }
    if (e != NULL)
    {
        *e = Q->base[Q->front];
    }
    return true;
}

void Sq_QueueTraverse(const SqQueue *Q)
{
    if (Q == NULL || Q->base == NULL)
    {
        return;
    }
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXQSIZE)
    {
        printf("%d ", Q->base[i]);
    }
    printf("\n");
}
