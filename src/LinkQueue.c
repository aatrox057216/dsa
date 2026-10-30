/**
 * @file    LinkQueue.c
 * @brief   链队列（带头结点）的具体实现。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#include "LinkQueue.h"
#include <stdio.h>
#include <stdlib.h>

bool InitQueue(LinkQueue *Q)
{
    if (Q == NULL)
    {
        return false;
    }
    Q->front = (QueuePtr)malloc(sizeof(QueueNode));
    if (Q->front == NULL)
    {
        return false;
    }
    Q->front->next = NULL;
    Q->rear = Q->front; /* 空队：front 与 rear 同时指向头结点 */
    Q->size = 0;
    return true;
}

void DestroyQueue(LinkQueue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    QueuePtr p = Q->front;
    while (p != NULL)
    {
        QueuePtr temp = p;
        p = p->next;
        free(temp);
    }
    Q->front = Q->rear = NULL;
    Q->size = 0;
}

void ClearQueue(LinkQueue *Q)
{
    if (Q == NULL || Q->front == NULL)
    {
        return;
    }
    QueuePtr p = Q->front->next;
    while (p != NULL)
    {
        QueuePtr temp = p;
        p = p->next;
        free(temp);
    }
    Q->front->next = NULL;
    Q->rear = Q->front;
    Q->size = 0;
}

bool QueueEmpty(const LinkQueue *Q)
{
    if (Q == NULL || Q->front == NULL)
    {
        return true;
    }
    return Q->front == Q->rear; /* 带头结点：首尾相同即空 */
}

int QueueLength(const LinkQueue *Q)
{
    if (Q == NULL)
    {
        return 0;
    }
    return Q->size;
}

bool EnQueue(LinkQueue *Q, int e)
{
    if (Q == NULL || Q->front == NULL)
    {
        return false;
    }
    QueuePtr p = (QueuePtr)malloc(sizeof(QueueNode));
    if (p == NULL)
    {
        return false;
    }
    p->data = e;
    p->next = NULL;
    Q->rear->next = p; /* 尾插 */
    Q->rear = p;
    Q->size++;
    return true;
}

bool DeQueue(LinkQueue *Q, int *e)
{
    if (Q == NULL || Q->front == NULL || QueueEmpty(Q))
    {
        return false;
    }
    QueuePtr p = Q->front->next; /* 被删除的是队头元素结点 */
    if (e != NULL)
    {
        *e = p->data;
    }
    Q->front->next = p->next;
    if (Q->rear == p)
    {                       /* 删除的是最后一个元素结点 */
        Q->rear = Q->front; /* 关键：尾指针回退到头结点 */
    }
    free(p);
    Q->size--;
    return true;
}

bool GetHead(const LinkQueue *Q, int *e)
{
    if (Q == NULL || Q->front == NULL || QueueEmpty(Q))
    {
        return false;
    }
    if (e != NULL)
    {
        *e = Q->front->next->data;
    }
    return true;
}

void QueueTraverse(const LinkQueue *Q)
{
    if (Q == NULL || Q->front == NULL)
    {
        return;
    }
    QueuePtr p = Q->front->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
