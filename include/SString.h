/**
 * @file    SString.h
 * @brief   定长顺序串的接口声明，依据严蔚敏《数据结构》C语言版。
 * @author  aatroxfans
 * @date    2026-10-30
 * @version 1.0
 * @note    data[0] 闲置，字符存于 data[1..length]。
 */

#ifndef SSTRING_H
#define SSTRING_H

#include <stdbool.h>

/** @brief 串的最大长度（含闲置的 data[0]） */
#define MAX_SIZE 256

/** @brief 定长顺序串结构体 */
typedef struct
{
    char data[MAX_SIZE]; /**< 字符数组，data[0] 闲置，字符存于 data[1..length] */
    int length;          /**< 当前串的长度 */
} SString;

/**
 * @brief  由 C 字符串常量初始化顺序串。
 * @param  S 待初始化的串。
 * @param  chars 以 '\0' 结尾的 C 字符串，可为 NULL 表示空串。
 * @return 成功返回 true，超长（> MAX_SIZE-1）返回 false 并截断。
 * @post   S->data[1..length] 存放字符，S->data[0] 闲置。
 */
bool SStringAssign(SString *S, const char *chars);

/**
 * @brief  串拷贝。
 * @param  T 目标串。
 * @param  S 源串（只读）。
 * @return 成功返回 true，参数非法返回 false。
 */
bool SStringCopy(SString *T, const SString *S);

/**
 * @brief  判断串是否为空。
 * @param  S 串指针（只读）。
 * @return 空返回 true。
 */
bool SStringEmpty(const SString *S);

/**
 * @brief  求串长。
 * @param  S 串指针（只读）。
 * @return 串长。
 */
int SStringLength(const SString *S);

/**
 * @brief  串比较（字典序）。
 * @param  S 串 S（只读）。
 * @param  T 串 T（只读）。
 * @return S>T 返回正数，S==T 返回 0，S<T 返回负数。
 */
int SStringCompare(const SString *S, const SString *T);

/**
 * @brief  串连接：将 T 接到 S 末尾，结果存入 R。
 * @param  R 结果串（可与 S 或 T 相同）。
 * @param  S 左串（只读）。
 * @param  T 右串（只读）。
 * @return 成功返回 true；结果超长时截断并返回 false。
 */
bool SStringConcat(SString *R, const SString *S, const SString *T);

/**
 * @brief  求子串：从 S 的第 pos 个字符起取 len 个字符存入 Sub。
 * @param  Sub 结果串。
 * @param  S 源串（只读）。
 * @param  pos 起始位置，1 <= pos <= S->length。
 * @param  len 取字符个数，可为 0。
 * @return 成功返回 true，pos/len 越界返回 false。
 */
bool SStringSubString(SString *Sub, const SString *S, int pos, int len);

/**
 * @brief  定位子串：返回 T 在 S 中首次出现的位置。
 * @param  S 主串（只读）。
 * @param  T 模式串（只读）。
 * @param  pos 从 S 的第 pos 个字符起查找，1 <= pos <= S->length。
 * @return 首次出现的起始位置（1-based），未找到返回 0。
 * @note   采用 BF（Brute-Force）朴素算法，O(n*m)。
 */
int SStringIndexBF(const SString *S, const SString *T, int pos);

/**
 * @brief  KMP 模式匹配，返回 T 在 S 中首次出现的位置。
 * @param  S 主串（只读）。
 * @param  T 模式串（只读）。
 * @param  pos 起始查找位置（1-based）。
 * @return 首次出现的起始位置（1-based），未找到返回 0。
 * @note   预处理 next 数组，O(n+m)。
 */
int SStringIndexKMP(const SString *S, const SString *T, int pos);

/**
 * @brief  打印串内容。
 * @param  S 串指针（只读）。
 */
void SStringPrint(const SString *S);

#endif /* SSTRING_H */
