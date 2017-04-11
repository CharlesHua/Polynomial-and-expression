/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.9
file name: expression.cpp

char Priority(char op0, char op1)
    求两个运算符op0和op1之间的优先级关系

***************************************************/
#include <iostream>
#include <string.h>
#include "expression.h"
#include "link_stack.h"

char Priority(char top_op, char op)
{
    char *op_set = "+-*/()#";
    static char priority_table[7][8] = {">><<<>>",
                             ">><<<>>",
                             ">>>><>>",
                             ">>>><>>",
                             "<<<<<=@",
                             ">>>>@>>",
                             "<<<<<@="};
    char *ptr1, *ptr2;
    ptr1 = strchr(op_set, top_op);
    ptr2 = strchr(op_set, op);
    return (priority_table[ptr1 - op_set][ptr2 - op_set]);
}
