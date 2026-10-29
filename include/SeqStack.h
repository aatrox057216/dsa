/**
 * @file    SeqStack.h
 * @brief   顺序栈（Sequential Stack）接口定义
 * @details 基于定长数组 + 栈顶指针 top 实现；top = -1 表示空栈，
 *          top 指向当前栈顶元素。遵循后进先出（LIFO）原则。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef SEQ_STACK_H
#define SEQ_STACK_H

#include <stdbool.h>

/** @brief 栈最大容量 */
#define MAX_SIZE 100

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/**
 * @brief 顺序栈结构体
 *
 * data 定长数组存储栈元素
 * top  栈顶指针，-1 表示空栈，指向当前栈顶元素的下标
 */
typedef struct
{
    ElemType data[MAX_SIZE]; /**< 存储空间 */
    int top;                 /**< 栈顶指针，-1 表示空栈 */
} SeqStack;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    SS_OK = 0,          /**< 操作成功 */
    SS_ERR_FULL = 1,    /**< 栈已满 */
    SS_ERR_EMPTY = 2,   /**< 栈为空 */
    SS_ERR_NOMEM = 3,   /**< 内存分配失败（保留） */
    SS_ERR_INVALID = 4, /**< 无效参数 */
} SSStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化顺序栈
 * @param  stack 待初始化的顺序栈指针
 * @return SS_OK 成功；SS_ERR_INVALID 参数为空
 * @note   将 top 置 -1，表示空栈
 */
SSStatus SS_Init(SeqStack *stack);

/**
 * @brief  清空顺序栈
 * @param  stack 顺序栈指针
 * @return SS_OK 成功；SS_ERR_INVALID 参数为空
 * @note   仅将 top 置 -1，不修改 data 内容
 */
SSStatus SS_Clear(SeqStack *stack);

/**
 * @brief  销毁顺序栈
 * @param  stack 顺序栈指针
 * @return SS_OK 成功；SS_ERR_INVALID 参数为空
 * @note   静态存储，语义上等价于 Clear
 */
SSStatus SS_Destroy(SeqStack *stack);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取当前栈中元素个数
 * @param  stack 顺序栈指针
 * @return 元素个数；参数为空返回 -1
 * @note   O(1)；长度为 top + 1
 */
int SS_Size(const SeqStack *stack);

/**
 * @brief  获取栈最大容量
 * @param  stack 顺序栈指针
 * @return 最大容量；参数为空返回 -1
 */
int SS_Capacity(const SeqStack *stack);

/**
 * @brief  判断栈是否为空
 * @param  stack 顺序栈指针
 * @return true 为空；false 非空或参数为空
 * @note   O(1)；判空条件 top == -1
 */
bool SS_IsEmpty(const SeqStack *stack);

/**
 * @brief  判断栈是否已满
 * @param  stack 顺序栈指针
 * @return true 已满；false 未满或参数为空
 * @note   O(1)；判满条件 top == MAX_SIZE - 1
 */
bool SS_IsFull(const SeqStack *stack);

/* ==================== 核心操作 ==================== */

/**
 * @brief  压栈（入栈）
 * @param  stack 顺序栈指针
 * @param  elem  待压入元素
 * @return SS_OK 成功；SS_ERR_FULL 栈满；SS_ERR_INVALID 参数为空
 * @note   O(1)；先 ++top，再写入 data[top]
 */
SSStatus SS_Push(SeqStack *stack, ElemType elem);

/**
 * @brief  弹栈（出栈）
 * @param  stack 顺序栈指针
 * @param  out   用于返回被弹出元素的指针，可为 NULL
 * @return SS_OK 成功；SS_ERR_EMPTY 栈空；SS_ERR_INVALID 参数为空
 * @note   O(1)；先取 data[top]，再 --top
 */
SSStatus SS_Pop(SeqStack *stack, ElemType *out);

/**
 * @brief  取栈顶元素（不出栈）
 * @param  stack 顺序栈指针
 * @param  out   用于返回栈顶元素的指针
 * @return SS_OK 成功；SS_ERR_EMPTY 栈空；SS_ERR_INVALID 参数为空
 * @note   O(1)
 */
SSStatus SS_Top(const SeqStack *stack, ElemType *out);

/**
 * @brief  获取栈顶下标
 * @param  stack 顺序栈指针
 * @return 栈顶下标；空栈返回 -1；参数为空返回 -2
 * @note   O(1)
 */
int SS_TopIndex(const SeqStack *stack);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找（从栈底数起）
 * @param  stack 顺序栈指针
 * @param  index 逻辑下标，范围 [0, size-1]，0 表示栈底
 * @param  out   用于返回元素值的指针
 * @return SS_OK 成功；SS_ERR_RANGE 越界；SS_ERR_INVALID 参数为空
 * @note   O(1)；直接访问 data[index]
 */
SSStatus SS_GetElem(const SeqStack *stack, int index, ElemType *out);

/**
 * @brief  按值查找（从栈顶向栈底搜索）
 * @param  stack 顺序栈指针
 * @param  elem  目标元素值
 * @return 距栈顶的距离（0 表示栈顶）；未找到返回 -1；参数为空返回 -1
 * @note   O(n)
 */
int SS_LocateFromTop(const SeqStack *stack, ElemType elem);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  从栈底到栈顶遍历
 * @param  stack    顺序栈指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return SS_OK 成功；SS_ERR_INVALID 参数为空
 */
SSStatus SS_TraverseBottomUp(const SeqStack *stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  从栈顶到栈底遍历
 * @param  stack    顺序栈指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return SS_OK 成功；SS_ERR_INVALID 参数为空
 */
SSStatus SS_TraverseTopDown(const SeqStack *stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印栈内容（栈底在左，栈顶在右）
 * @param  stack 顺序栈指针
 * @return SS_OK 成功；SS_ERR_INVALID 参数为空
 */
SSStatus SS_Print(const SeqStack *stack);

/* ==================== 经典应用 ==================== */

/**
 * @brief  括号匹配检测
 * @param  expr 待检测的字符串表达式
 * @return true 括号匹配；false 不匹配或参数为空
 * @note   支持 () [] {} 三种括号；O(n)
 */
bool SS_CheckBrackets(const char *expr);

/**
 * @brief  十进制转任意进制（2 ~ 36）
 * @param  decimal 十进制数（非负）
 * @param  base    目标进制
 * @param  out     输出缓冲区，调用方分配，建议长度 >= 33
 * @return SS_OK 成功；SS_ERR_INVALID 参数非法
 * @note   利用栈后进先出特性逆序输出余数
 */
SSStatus SS_DecimalToBase(int decimal, int base, char *out);

/**
 * @brief  逆波兰表达式（后缀表达式）求值
 * @param  expr 后缀表达式字符串，操作数与操作数以空格分隔
 * @param  out  用于返回求值结果
 * @return SS_OK 成功；SS_ERR_INVALID 表达式非法
 * @note   支持 + - * / 四种运算符与整数操作数；O(n)
 */
SSStatus SS_EvalRPN(const char *expr, int *out);

/**
 * @brief  用两个栈实现队列的演示
 * @param  ops    操作序列：0 表示入队，1 表示出队
 * @param  vals   操作数序列（出队操作时忽略）
 * @param  n      操作个数
 * @param  out    输出出队元素序列
 * @param  outLen 输出长度
 * @return SS_OK 成功；SS_ERR_INVALID 参数非法
 * @note   入队压 in 栈，出队时若 out 栈空则将 in 全部倒入 out
 */
SSStatus SS_TwoStacksQueue(const int *ops, const int *vals, int n, int *out, int *outLen);

#endif /* SEQ_STACK_H */
