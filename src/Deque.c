/**
 * @file    Deque.c
 * @brief   链式双端队列（双向链表、不带头结点）的具体实现。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#include "Deque.h"
#include <stdio.h>
#include <stdlib.h>

void DequeInit(Deque *D)
{
    if (D == NULL)
    {
        return;
    }
    D->front = NULL;
    D->rear = NULL;
    D->size = 0;
}

void DequeDestroy(Deque *D)
{
    if (D == NULL)
    {
        return;
    }
    DequePtr p = D->front;
    while (p != NULL)
    {
        DequePtr temp = p;
        p = p->next;
        free(temp);
    }
    D->front = D->rear = NULL;
    D->size = 0;
}

void DequeClear(Deque *D)
{
    if (D == NULL)
    {
        return;
    }
    DequePtr p = D->front;
    while (p != NULL)
    {
        DequePtr temp = p;
        p = p->next;
        free(temp);
    }
    D->front = D->rear = NULL;
    D->size = 0;
}

bool DequeIsEmpty(const Deque *D)
{
    if (D == NULL)
    {
        return true;
    }
    return D->front == NULL;
}

int DequeSize(const Deque *D)
{
    if (D == NULL)
    {
        return 0;
    }
    return D->size;
}

bool DequePushFront(Deque *D, int e)
{
    if (D == NULL)
    {
        return false;
    }
    DequePtr p = (DequePtr)malloc(sizeof(DNode));
    if (p == NULL)
    {
        return false;
    }
    p->data = e;
    p->prev = NULL;
    p->next = D->front;
    if (D->front != NULL)
    {
        D->front->prev = p; /* 原头结点前驱指向新结点 */
    }
    else
    {
        D->rear = p; /* 空队插入：rear 同时指向新结点 */
    }
    D->front = p;
    D->size++;
    return true;
}

bool DequePushBack(Deque *D, int e)
{
    if (D == NULL)
    {
        return false;
    }
    DequePtr p = (DequePtr)malloc(sizeof(DNode));
    if (p == NULL)
    {
        return false;
    }
    p->data = e;
    p->next = NULL;
    p->prev = D->rear;
    if (D->rear != NULL)
    {
        D->rear->next = p; /* 原尾结点后继指向新结点 */
    }
    else
    {
        D->front = p; /* 空队插入：front 同时指向新结点 */
    }
    D->rear = p;
    D->size++;
    return true;
}

bool DequePopFront(Deque *D, int *e)
{
    if (D == NULL || D->front == NULL)
    {
        return false;
    }
    DequePtr p = D->front;
    if (e != NULL)
    {
        *e = p->data;
    }
    D->front = p->next;
    if (D->front != NULL)
    {
        D->front->prev = NULL; /* 新头结点前驱置空 */
    }
    else
    {
        D->rear = NULL; /* 删除唯一结点：尾指针同步置空 */
    }
    free(p);
    D->size--;
    return true;
}

bool DequePopBack(Deque *D, int *e)
{
    if (D == NULL || D->rear == NULL)
    {
        return false;
    }
    DequePtr p = D->rear;
    if (e != NULL)
    {
        *e = p->data;
    }
    D->rear = p->prev;
    if (D->rear != NULL)
    {
        D->rear->next = NULL; /* 新尾结点后继置空 */
    }
    else
    {
        D->front = NULL; /* 删除唯一结点：头指针同步置空 */
    }
    free(p);
    D->size--;
    return true;
}

bool DequeGetFront(const Deque *D, int *e)
{
    if (D == NULL || D->front == NULL)
    {
        return false;
    }
    if (e != NULL)
    {
        *e = D->front->data;
    }
    return true;
}

bool DequeGetBack(const Deque *D, int *e)
{
    if (D == NULL || D->rear == NULL)
    {
        return false;
    }
    if (e != NULL)
    {
        *e = D->rear->data;
    }
    return true;
}

void DequeTraverseForward(const Deque *D)
{
    if (D == NULL)
    {
        return;
    }
    DequePtr p = D->front;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void DequeTraverseBackward(const Deque *D)
{
    if (D == NULL)
    {
        return;
    }
    DequePtr p = D->rear;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
}
