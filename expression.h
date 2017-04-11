/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.9
file name: expression.h

功能说明
    exanmlp.          //explanation

***************************************************/
#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include <iostream>
#include <string>
#include "link_stack.h"


template <typename T>
class Expression{
public :
    // constructors & destructor
    Expression():op_set_("+-*/()#"),dig_set_("0123456789."){};
    ~Expression(){}

    T (*Operand)(std::string& str);
    T Evaluate();

private :
    LinkStack<char> operator_stack; //操作符栈
    LinkStack<T> operand_stack; //操作数栈
    char* op_set_;  //操作符集
    char* dig_set_;  //数字相关字符集

};

/*********************************************************
//
//                 declaration
*/
char Priority(char top_op, char op);

template <typename T>
T Operate(char& op, T& a, T& b);

#include <iostream>
#include <string.h>
/*********************************************************
//
//                 definition
*/

//#define DEBUG

/*********************************************************
//
//             general member function
*/

template <typename T>
T Expression<T>::Evaluate()
{
    operator_stack.Push('#');
    char op,top_op,theta;
  //  char ch;
    std::string str;
  //  do{
        std::cin >> op;
  //  }while(strchr(op_set_, op)==NULL && strchr(dig_set_, op)==NULL);
    //std::cin >> op;

    T a,b;
    while (op!='#' || operator_stack.top_data()!='#'){
#ifdef DEBUG
        std::cout<<" op = "<<op<<endl;
#endif // DEBUG
        if (strchr(op_set_, op)==NULL){ //输入不在运算符集中
            do{
                str = str + op;
                std::cin >> op;
            }while(strchr(op_set_, op)==NULL);
            operand_stack.Push(Operand(str));
            str = "";
#ifdef DEBUG
            cout<<"op = "<<op<<endl;
#endif // DEBUG
        }
        else{
            top_op = operator_stack.top_data();
            switch(Priority(top_op, op)){
                case '<':{ //栈顶优先级低
                    operator_stack.Push(op);
                    std::cin >> op;
                    break;
                }
                case '=':{ //等优先级，脱括号
                    operator_stack.Pop();
                    std::cin >> op;
                    break;
                }
                case '>':{ //栈顶优先级高
                    b = operand_stack.Pop();
                    a = operand_stack.Pop();
                    theta = operator_stack.Pop();
                    operand_stack.Push(Operate(theta,a,b));
                    break;
                }
            }//switch
        }//else
    }//while
    return operand_stack.top_data();
}

/*********************************************************
//
//                other function
*/
template <typename T>
T Operate(char& op, T& a, T& b)
{
#ifdef DEBUG
    cout<<"do "<<op<<" "<<a<<", "<<b<<endl;
#endif // DEBUG
    switch (op){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
    return 0;
}


#ifdef DEBUG
#undef DEBUG
#endif // DEBUG

#endif //_EXPRESSION_H
