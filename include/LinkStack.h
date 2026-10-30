/**
 * @file    LinkStack.h
 * @brief   链栈（Linked Stack）接口定义
 * @details 栈顶即链表头部，LinkStack 指针直接指向栈顶结点（不带头结点）。
 *          压栈 = 头插 O(1)，弹栈 = 删头 O(1)，天然动态扩容。
 * @author  aatroxfans
 * @date    2024
 */

#ifndef LINK_STACK_H
#define LINK_STACK_H

#include <stdbool.h>

/** @brief 元素类型别名，便于统一修改 */
typedef int ElemType;

/**
 * @brief 链栈结点结构体
 *
 * data 存储有效数据
 * next 指向下一个结点；栈底结点 next 为 NULL
 */
typedef struct StackNode
{
    ElemType data;          /**< 数据域 */
    struct StackNode *next; /**< 指针域，指向下一个结点 */
} StackNode, *LinkStack;

/* ==================== 状态码定义 ==================== */

/** @brief 操作状态码 */
typedef enum
{
    LS_OK = 0,          /**< 操作成功 */
    LS_ERR_FULL = 1,    /**< 栈已满（链栈仅内存耗尽时出现） */
    LS_ERR_EMPTY = 2,   /**< 栈为空 */
    LS_ERR_NOMEM = 3,   /**< 内存分配失败 */
    LS_ERR_INVALID = 4, /**< 无效参数 */
} LSStatus;

/* ==================== 生命周期 ==================== */

/**
 * @brief  初始化链栈（置空）
 * @param  stack 指向链栈头指针的指针
 * @return LS_OK 成功；LS_ERR_INVALID 参数为空
 * @note   将 *stack 置 NULL，表示空栈
 */
LSStatus LS_Init(LinkStack *stack);

/**
 * @brief  清空链栈
 * @param  stack 指向链栈头指针的指针
 * @return LS_OK 成功；LS_ERR_INVALID 参数为空
 * @note   释放所有结点，*stack 置 NULL
 */
LSStatus LS_Clear(LinkStack *stack);

/**
 * @brief  销毁链栈
 * @param  stack 指向链栈头指针的指针
 * @return LS_OK 成功；LS_ERR_INVALID 参数为空
 * @note   与 Clear 等价（链栈无独立头结点）
 */
LSStatus LS_Destroy(LinkStack *stack);

/* ==================== 容量与状态 ==================== */

/**
 * @brief  获取栈中元素个数
 * @param  stack 链栈头指针
 * @return 元素个数；参数为空返回 -1
 * @note   O(n)；如需 O(1) 可额外维护 size 字段
 */
int LS_Size(LinkStack stack);

/**
 * @brief  判断栈是否为空
 * @param  stack 链栈头指针
 * @return true 为空；false 非空或参数为空
 * @note   O(1)
 */
bool LS_IsEmpty(LinkStack stack);

/* ==================== 核心操作 ==================== */

/**
 * @brief  压栈（入栈）
 * @param  stack 指向链栈头指针的指针
 * @param  elem  待压入元素
 * @return LS_OK 成功；LS_ERR_NOMEM 内存不足；LS_ERR_INVALID 参数为空
 * @note   O(1)；头插法
 */
LSStatus LS_Push(LinkStack *stack, ElemType elem);

/**
 * @brief  弹栈（出栈）
 * @param  stack 指向链栈头指针的指针
 * @param  out   用于返回被弹出元素的指针，可为 NULL
 * @return LS_OK 成功；LS_ERR_EMPTY 栈空；LS_ERR_INVALID 参数为空
 * @note   O(1)；删除头结点
 */
LSStatus LS_Pop(LinkStack *stack, ElemType *out);

/**
 * @brief  取栈顶元素（不出栈）
 * @param  stack 链栈头指针
 * @param  out   用于返回栈顶元素的指针
 * @return LS_OK 成功；LS_ERR_EMPTY 栈空；LS_ERR_INVALID 参数为空
 * @note   O(1)
 */
LSStatus LS_Top(LinkStack stack, ElemType *out);

/* ==================== 查找 ==================== */

/**
 * @brief  按位置查找（从栈底数起）
 * @param  stack 链栈头指针
 * @param  index 逻辑下标，范围 [0, size-1]，0 表示栈底
 * @param  out   用于返回元素值的指针
 * @return LS_OK 成功；LS_ERR_RANGE 越界；LS_ERR_INVALID 参数为空
 * @note   O(n)
 */
LSStatus LS_GetElem(LinkStack stack, int index, ElemType *out);

/**
 * @brief  按值查找（从栈顶向栈底搜索）
 * @param  stack 链栈头指针
 * @param  elem  目标元素值
 * @return 距栈顶的距离（0 表示栈顶）；未找到返回 -1；参数为空返回 -1
 * @note   O(n)
 */
int LS_LocateFromTop(LinkStack stack, ElemType elem);

/* ==================== 遍历与显示 ==================== */

/**
 * @brief  从栈底到栈顶遍历
 * @param  stack    链栈头指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return LS_OK 成功；LS_ERR_INVALID 参数为空
 * @note   O(n)；需借助递归或临时数组逆序
 */
LSStatus LS_TraverseBottomUp(LinkStack stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  从栈顶到栈底遍历
 * @param  stack    链栈头指针
 * @param  callback 回调函数，返回 false 可提前终止
 * @param  ctx      用户上下文
 * @return LS_OK 成功；LS_ERR_INVALID 参数为空
 * @note   O(n)；直接沿 next 遍历
 */
LSStatus LS_TraverseTopDown(LinkStack stack, bool (*callback)(ElemType elem, int index, void *ctx), void *ctx);

/**
 * @brief  打印栈内容（栈底在左，栈顶在右）
 * @param  stack 链栈头指针
 * @return LS_OK 成功；LS_ERR_INVALID 参数为空
 */
LSStatus LS_Print(LinkStack stack);

/* ==================== 经典应用 ==================== */

/**
 * @brief  括号匹配检测
 * @param  expr 待检测的字符串表达式
 * @return true 括号匹配；false 不匹配或参数为空
 * @note   支持 () [] {} 三种括号；O(n)
 */
bool LS_CheckBrackets(const char *expr);

/**
 * @brief  十进制转任意进制（2 ~ 36）
 * @param  decimal 十进制数（非负）
 * @param  base    目标进制
 * @param  out     输出缓冲区，调用方分配，建议长度 >= 33
 * @return LS_OK 成功；LS_ERR_INVALID 参数非法
 * @note   利用栈后进先出特性逆序输出余数
 */
LSStatus LS_DecimalToBase(int decimal, int base, char *out);

/**
 * @brief  逆波兰表达式（后缀表达式）求值
 * @param  expr 后缀表达式字符串，操作数与操作数以空格分隔
 * @param  out  用于返回求值结果
 * @return LS_OK 成功；LS_ERR_INVALID 表达式非法
 * @note   支持 + - * / 四种运算符与整数操作数；O(n)
 */
LSStatus LS_EvalRPN(const char *expr, int *out);

/**
 * @brief  用链栈实现简单表达式求值（中缀，仅支持 + - * / 和括号）
 * @param  expr 中缀表达式字符串
 * @param  out  用于返回求值结果
 * @return LS_OK 成功；LS_ERR_INVALID 表达式非法
 * @note   双栈法：操作数栈 + 运算符栈；O(n)
 */
LSStatus LS_EvalInfix(const char *expr, int *out);

/**
 * @brief  判断给定入栈序列是否可能存在对应的出栈序列
 * @param  pushSeq 入栈序列数组
 * @param  popSeq  出栈序列数组
 * @param  n       序列长度
 * @return true 可能；false 不可能或参数非法
 * @note   模拟压栈弹栈过程；O(n)
 */
bool LS_IsPopOrderValid(const int *pushSeq, const int *popSeq, int n);

#endif /* LINK_STACK_H */
