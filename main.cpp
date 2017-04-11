/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.10
project name: Polyn
file name: main.cpp

多项式计算器菜单界面
int PrintManu()
    输出菜单
int string_to_int(string& str)
    string类型转int类型
double string_to_double(string& str)
    string类型转double类型
Polynomial string_to_polynomial(string& str)
    输入数字组成的string类型，输出对应编号的多项式

***************************************************/

#include <iostream>
#include "polynomial.h"
#include "expression.h"
using namespace std;

#define REQUIRE_EXIST_POLYNOMIAL(t) if(pol[t].empty()){cout << "Polynomial[" << t << "] doesn't exist" << endl; break;}
    //要求编号为t的多项式已存在
#define REQUIRE_NOT_EXIST_POLYNOMIAL(t) if(!pol[t].empty()){cout << "Polynomial[" << t << "] already exists" << endl; break;}
    //要求编号为t的多项式不存在

int PrintManu()
{
    cout << "请输入功能前对应的序号" << endl
         << "    0.退出" << endl
         << "    多项式部分:" << endl
         << "        1.创建        2.显示        3.复制" << endl
         << "        4.销毁        5.清空        6.修改        7.求值" << endl
         << "        8.加法(+)     9.减法(-)     10.乘法(*)    11.除法(/,%)" << endl
         << "        12.乘方       13.微分       14.不定积分   15.定积分" << endl
         << "        16.最大公因式、最小公倍式       17.四则运算" << endl
         << "    非多项式部分:" << endl
         << "        18.浮点数四则运算" << endl
        ;
    return 0;
}

    Polynomial pol[101];
//    Polynomial pol_empty(0);

int string_to_int(string& str)
{
    int ans = 0;
    for (int i=0; i<str.length(); i++)
        ans = ans * 10 + (str[i] - '0');
    return ans;
}

double string_to_double(string& str)
{
    double ans = 0, right = 0;
    for (int i=0; str[i]!='\0'; i++)
        if (isdigit(str[i])){
            if (right==0)
                ans = ans * 10 + (str[i] - '0');
            else{
                right = right / 10.0;
                ans = ans + (str[i] - '0') * right;
            }
        }
        else
            if (str[i] == '.')
                right = 1;
    return ans;
}

Polynomial string_to_polynomial(string& str)
{
    int i = string_to_int(str);
    if (!pol[i].empty())
        return pol[i];
    else{
        cout << "Polynomial[" << i << "] doesn't exist" << endl;
        return pol[0];
    }
}

int main()
{
    int t,src,src1,dest,dest1,order;
    int fun;
    double a,b,x;
    do{
        PrintManu();
        cin >> fun;
        switch (fun) {
            case 1:{ //创建多项式
                cout << "存储为第几个多项式? (可用编号1~100)" << endl;
                cin >> t;
                REQUIRE_NOT_EXIST_POLYNOMIAL(t);
                pol[t].InitList();
                pol[t].CreatPolyn();
                cout << "Creat success\n\tPolynomial[" << t << "] = " << pol[t] << endl;
            }break;
            case 2:{ //显示多项式
                cout << "显示第几个多项式? " << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                cout << "\tPolynomial[" << t << "] = " << pol[t] << endl;
            }break;
            case 3:{ //复制多项式
                cout << "从第几个多项式复制到第几个? " << endl;
                cin >> src >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest].CopyPolyn(pol[src]);
                cout << "Copy success\n\tPolynomial[" << dest << "] = " << pol[dest] << endl;
            }break;
            case 4:{ //销毁多项式
                cout << "销毁第几个多项式?" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                pol[t].DestroyList();
                cout << "Destroy success\n\tPolynomial[" << t << "] doesn't exist now." << endl;
            } break;
            case 5:{ //清空多项式
                cout << "清空第几个多项式?" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                pol[t].ClearList();
                cout << "Clear success\n\tPolynomial[" << t << "] = " << pol[t] << endl;
            } break;
            case 6:{ //修改多项式
                cout << "请输入要修改的多项式的序号" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                double exp,co;
                cout << "请输入要修改的项的指数(若不存在将会插入)" << endl;
                cin >> exp;
                cout << "请输入要修改的项的系数(0表示删除改项)" << endl;
                cin >> co;
                pol[t].ChangeNode(co,exp);
                cout << "Polynomial[" << t << "] = " << pol[t] << endl;
            } break;
            case 7:{ //求值
                cout << "求第几个多项式?" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                cout << "x = ? ";
                cin >> x;
                cout << "( " << pol[t] << " ) = " << pol[t].Value(x) << " for x = " << x << endl;
            }break;
            case 8:{ //求和
                cout << "第几个和第几个相加放到第几个?" << endl;
                cin >> src >> src1 >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = pol[src] + pol[src1];
                cout << "( " << pol[src] << " ) + ( " << pol[src1] << " ) = " << pol[dest] << endl;
            }break;
            case 9:{ //求差
                cout << "第几个和第几个相减放到第几个?" << endl;
                cin >> src >> src1 >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = pol[src] - pol[src1];
                cout << "( " << pol[src] << " ) - ( " << pol[src1] << " ) = " << pol[dest] << endl;
            }break;
            case 10:{ //乘法
                cout << "第几个和第几个相乘放到第几个?" << endl;
                cin >> src >> src1 >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = pol[src] * pol[src1];
                cout << "( " << pol[src] << " ) * ( " << pol[src1] << ") = " << pol[dest] << endl;
            }break;
            case 11:{ //除法
                cout << "第几个和第几个相除，商和余项分别放到第几个?" << endl;
                cin >> src >> src1 >> dest >> dest1;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest1);
                if (pol[src1].Coef() == 0){
                    cout << "Warning, divisor=0" << endl;
                    break;
                }
                pol[dest] = pol[src] / pol[src1];
                pol[dest1] = pol[src] % pol[src1];
                cout << "( " << pol[src] << " ) / ( " << pol[src1] << ") = " << pol[dest] << endl;
                cout << "( " << pol[src] << " ) % ( " << pol[src1] << ") = " << pol[dest1] << endl;
            }break;
            case 12:{ //求乘方
                int expon;
                cout << "对第几个多项式几次幂,存为第几个多项式?" << endl;
                cin >> src >> expon >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = Power(pol[src],expon);
                cout << "( " << pol[src] << " )^" << expon << " = " << pol[dest] << endl;
            }break;
            case 13:{ //求微分
                cout << "对第几个多项式求微分,求几阶微分,存为第几个多项式?" << endl;
                cin >> src >> order >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = Differential(pol[src],order);
                cout << "d^" << order << "( " << pol[src] << " )/dx^" << order << " = " << pol[dest] << endl;
            } break;
            case 14:{ //不定积分
                cout << "对第几个多项式求不定积分,存为第几个多项式?" << endl;
                cin >> src >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = InIntegral(pol[src]);
                cout << "∫("<< pol[src] <<")dx = " <<pol[dest] << "+Const" << endl;
            } break;
            case 15:{ //定积分
                cout << "对第几个多项式求定积分,积分范围从几到几?" << endl;
                cin >> src >> a >> b;
                REQUIRE_EXIST_POLYNOMIAL(src);
                cout << "Integral (" << pol[src] << ") from " << a << " to " << b << " = " << DeIntegral(pol[src], a, b) << endl;
            } break;
            case 16:{ //gcd & lcm
                cout << "取第几个和第几个多项式，gcd 和 lcm 分别放到第几个?" << endl;
                cin >> src >> src1 >> dest >> dest1;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest1);
                if (pol[src].Coef() == 0 || pol[src1].Coef() == 0){
                    cout << "Warning, one of the polynomial=0" << endl;
                    break;
                }
                pol[dest] = GCD(pol[src], pol[src1]);
                pol[dest1] = LCM(pol[src], pol[src1]);
                cout << "gcd( " << pol[src] << " , " << pol[src1] << " ) = " << pol[dest] << endl;
                cout << "lcm( " << pol[src] << " , " << pol[src1] << " ) = " << pol[dest1] << endl;
            }break;
            case 17:{ //多项式四则运算
                cout << "请输入四则运算表达式,支持+-*/(),请用多项式的编号代替多项式,以井号(#)结尾" << endl;
                cout << "请保证输入的多项式编号已经存在，且在运算过程中不会出现除以0" << endl;
                Expression<Polynomial> expr;
                expr.Operand = string_to_polynomial;
                Polynomial ans = expr.Evaluate();
                cout << "Ans = " << ans << endl;
                ans.DestroyList();
            }break;
            case 18:{ //浮点数四则运算
                cout << "请输入四则运算表达式,以井号(#)结尾,支持+-*/(),不支持负号" << endl;
                Expression<double> expr;
                expr.Operand = string_to_double;
                cout << "Ans = " << expr.Evaluate() << endl;
            }break;
        }
    }while(fun);
    return 0;
}

#undef REQUIRE_EXIST_POLYNOMIAL
#undef REQUIRE_NOT_EXIST_POLYNOMIAL
