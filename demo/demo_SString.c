/**
 * @file    demo.c
 * @brief   定长顺序串功能演示：赋值、比较、连接、求子串、BF/KMP 定位。
 * @author  aatroxfans
 * @date    2026-10-30
 */

#include "SString.h"
#include <stdio.h>

int main(void)
{
    SString S, T, R, Sub;
    int pos;

    SStringAssign(&S, "Hello, Data Structure!");
    SStringAssign(&T, "Data");
    printf("S = ");
    SStringPrint(&S);
    printf("S 长度 = %d\n", SStringLength(&S));

    /* 比较 */
    SStringAssign(&R, "Hello");
    printf("比较 S 与 \"Hello\"：%d\n", SStringCompare(&S, &R));

    /* 连接 */
    SStringAssign(&R, "abc");
    SStringAssign(&Sub, "def");
    SStringConcat(&R, &R, &Sub);
    printf("连接结果：");
    SStringPrint(&R);

    /* 求子串：从第 8 位起取 4 个字符 */
    if (SStringSubString(&Sub, &S, 8, 4))
    {
        printf("S 第 8 位起 4 个字符：");
        SStringPrint(&Sub);
    }

    /* BF 定位 */
    pos = SStringIndexBF(&S, &T, 1);
    printf("BF 定位 \"Data\"：%d\n", pos);

    /* KMP 定位 */
    SStringAssign(&S, "ababcabcacbab");
    SStringAssign(&T, "abcac");
    pos = SStringIndexKMP(&S, &T, 1);
    printf("KMP 在 \"ababcabcacbab\" 中定位 \"abcac\"：%d\n", pos);

    /* 越界测试 */
    if (!SStringSubString(&Sub, &S, 100, 2))
    {
        printf("越界取子串被正确拒绝\n");
    }

    return 0;
}
