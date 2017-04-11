/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.10
file name: polynmial.h

多项式及其运算
功能说明
    example.          //explanation
Polynomial operator+(const Polynomial&, const Polynomial&);
Polynomial operator-(const Polynomial&, const Polynomial&);
Polynomial operator*(const Polynomial&, const Polynomial&);
    多项式与多项式相乘
Polynomial operator*(const Polynomial&, const NodeData&);
    多项式与单项式相乘
Polynomial operator/(const Polynomial&, const Polynomial&);
Polynomial operator%(const Polynomial&, const Polynomial&);
Polynomial Differential(const Polynomial&, int order);
    求高阶微分
Polynomial InIntegral(const Polynomial&);
    求不定积分
double DeIntegral(const Polynomial&, double x0, double x1);
    求x0到x1的定积分
Polynomial Power(const Polynomial&, int expon);
    求乘方
Polynomial GCD(const Polynomial&, const Polynomial&);
    求最大公因式
Polynomial LCM(const Polynomial&, const Polynomial&);
    求最小公倍式
std::ostream &operator<<(std::ostream&, const Polynomial&);
    输出函数
Polynomial(){};
    default constructors
Polynomial(int);
    定义一个多项式并使其值为0
Polynomial(const Polynomial&);
    定义一个与给定的多项式相等的多项式

CreatPolyn();
    初始化已有的多项式从输入的参数
CopyPolyn(const Polynomial&);
    复制多项式
ChangeNode(double coe,int expo);
    改变多项式的一个节点
OrderInsert(NodeData node_data);
    有序插入一个节点
Value(const double x);
    求多项式的值
DeleteZore();
    删除系数为0的节点。
get_degree() const;
    求多项式的次数
Coef() const;
    求多项式最高次项系数

***************************************************/
#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include "link_list.h"

struct NodeData{
    NodeData(){};
    NodeData(double new_co, int new_exp):co(new_co),exp(new_exp){}
    double co;  //系数
    int exp;  //指数
};

//the following two lines are equal
typedef LNode<NodeData> PolNode;
//using PolNode = LNode<NodeData>;

class Polynomial: public LinkList<NodeData>{
friend Polynomial operator+(const Polynomial&, const Polynomial&);
friend Polynomial operator-(const Polynomial&, const Polynomial&);
friend Polynomial operator*(const Polynomial&, const Polynomial&);
friend Polynomial operator*(const Polynomial&, const NodeData&);
friend Polynomial operator/(const Polynomial&, const Polynomial&);
friend Polynomial operator%(const Polynomial&, const Polynomial&);
friend Polynomial Differential(const Polynomial&, int order);
friend Polynomial InIntegral(const Polynomial&);
friend double DeIntegral(const Polynomial&, double x0, double x1);
friend Polynomial Power(const Polynomial&, int expon);
friend Polynomial GCD(const Polynomial&, const Polynomial&);
friend Polynomial LCM(const Polynomial&, const Polynomial&);
friend std::ostream &operator<<(std::ostream&, const Polynomial&);

public :
    // constructors & destructor
    Polynomial(){};
    Polynomial(int);
    Polynomial(const Polynomial&);
    ~Polynomial(){}

    //general member function
    int CreatPolyn();
    int CopyPolyn(const Polynomial&);
    int ChangeNode(double coe,int expo);
    int OrderInsert(NodeData node_data);
    double Value(double x);
private :
    int DeleteZore();
   // int Exist();

public :
    //input/output function
    int get_degree() const;
    double Coef() const;

};

#endif //_POLYNOMIAL_H
