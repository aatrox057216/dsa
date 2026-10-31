/**
 * @file    SString.c
 * @brief   定长顺序串的具体实现。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 */

#include "SString.h"
#include <stdio.h>
#include <string.h>

bool SStringAssign(SString *S, const char *chars)
{
    if (S == NULL)
    {
        return false;
    }
    S->length = 0;
    if (chars == NULL)
    {
        return true;
    }
    int n = (int)strlen(chars);
    bool ok = true;
    if (n > MAX_SIZE - 1)
    { /* 超长截断 */
        n = MAX_SIZE - 1;
        ok = false;
    }
    for (int i = 0; i < n; ++i)
    {
        S->data[i + 1] = chars[i]; /* 字符从下标 1 开始 */
    }
    S->length = n;
    return ok;
}

bool SStringCopy(SString *T, const SString *S)
{
    if (T == NULL || S == NULL)
    {
        return false;
    }
    for (int i = 1; i <= S->length; ++i)
    {
        T->data[i] = S->data[i];
    }
    T->length = S->length;
    return true;
}

bool SStringEmpty(const SString *S)
{
    if (S == NULL)
    {
        return true;
    }
    return S->length == 0;
}

int SStringLength(const SString *S)
{
    if (S == NULL)
    {
        return 0;
    }
    return S->length;
}

int SStringCompare(const SString *S, const SString *T)
{
    if (S == NULL || T == NULL)
    {
        return 0;
    }
    int i = 1;
    while (i <= S->length && i <= T->length)
    {
        if (S->data[i] != T->data[i])
        {
            return (unsigned char)S->data[i] - (unsigned char)T->data[i];
        }
        ++i;
    }
    return S->length - T->length; /* 前缀相同则长串更大 */
}

bool SStringConcat(SString *R, const SString *S, const SString *T)
{
    if (R == NULL || S == NULL || T == NULL)
    {
        return false;
    }
    SString tmp;
    tmp.length = 0;
    int i = 1;
    bool ok = true;
    /* 先拷 S，超长截断 */
    while (i <= S->length && i <= MAX_SIZE - 1)
    {
        tmp.data[i] = S->data[i];
        ++i;
    }
    if (i <= S->length)
    {
        ok = false; /* S 已占满 */
    }
    /* 再拷 T */
    int j = 1;
    while (j <= T->length && i <= MAX_SIZE - 1)
    {
        tmp.data[i] = T->data[j];
        ++i;
        ++j;
    }
    if (j <= T->length)
    {
        ok = false; /* T 被截断 */
    }
    tmp.length = i - 1;
    SStringCopy(R, &tmp); /* 用临时串避免 R 与 S/T 别名问题 */
    return ok;
}

bool SStringSubString(SString *Sub, const SString *S, int pos, int len)
{
    if (Sub == NULL || S == NULL)
    {
        return false;
    }
    if (pos < 1 || pos > S->length)
    {
        return false;
    }
    if (len < 0 || pos + len - 1 > S->length)
    {
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        Sub->data[i + 1] = S->data[pos + i];
    }
    Sub->length = len;
    return true;
}

int SStringIndexBF(const SString *S, const SString *T, int pos)
{
    if (S == NULL || T == NULL)
    {
        return 0;
    }
    int i = pos, j = 1;
    while (i <= S->length && j <= T->length)
    {
        if (S->data[i] == T->data[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 2; /* 主串回溯到本轮起点的下一个 */
            j = 1;
        }
    }
    if (j > T->length)
    {
        return i - T->length;
    }
    return 0;
}

/** @brief 计算 KMP 的 next 数组（1-based，next[1]=0） */
static void SStringGetNext(const SString *T, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T->length)
    {
        if (j == 0 || T->data[i] == T->data[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

int SStringIndexKMP(const SString *S, const SString *T, int pos)
{
    if (S == NULL || T == NULL || T->length == 0)
    {
        return 0;
    }
    if (pos < 1 || pos > S->length)
    {
        return 0;
    }
    int next[MAX_SIZE + 1];
    SStringGetNext(T, next);
    int i = pos, j = 1;
    while (i <= S->length && j <= T->length)
    {
        if (j == 0 || S->data[i] == T->data[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j]; /* 主串不回溯，模式串右滑 */
        }
    }
    if (j > T->length)
    {
        return i - T->length;
    }
    return 0;
}

void SStringPrint(const SString *S)
{
    if (S == NULL)
    {
        return;
    }
    for (int i = 1; i <= S->length; ++i)
    {
        putchar(S->data[i]);
    }
    putchar('\n');
}
