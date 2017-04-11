/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.10
project name: Polyn
file name: main.cpp

����ʽ�������˵�����
int PrintManu()
    ����˵�
int string_to_int(string& str)
    string����תint����
double string_to_double(string& str)
    string����תdouble����
Polynomial string_to_polynomial(string& str)
    ����������ɵ�string���ͣ������Ӧ��ŵĶ���ʽ

***************************************************/

#include <iostream>
#include "polynomial.h"
#include "expression.h"
using namespace std;

#define REQUIRE_EXIST_POLYNOMIAL(t) if(pol[t].empty()){cout << "Polynomial[" << t << "] doesn't exist" << endl; break;}
    //Ҫ����Ϊt�Ķ���ʽ�Ѵ���
#define REQUIRE_NOT_EXIST_POLYNOMIAL(t) if(!pol[t].empty()){cout << "Polynomial[" << t << "] already exists" << endl; break;}
    //Ҫ����Ϊt�Ķ���ʽ������

int PrintManu()
{
    cout << "�����빦��ǰ��Ӧ�����" << endl
         << "    0.�˳�" << endl
         << "    ����ʽ����:" << endl
         << "        1.����        2.��ʾ        3.����" << endl
         << "        4.����        5.���        6.�޸�        7.��ֵ" << endl
         << "        8.�ӷ�(+)     9.����(-)     10.�˷�(*)    11.����(/,%)" << endl
         << "        12.�˷�       13.΢��       14.��������   15.������" << endl
         << "        16.�����ʽ����С����ʽ       17.��������" << endl
         << "    �Ƕ���ʽ����:" << endl
         << "        18.��������������" << endl
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
            case 1:{ //��������ʽ
                cout << "�洢Ϊ�ڼ�������ʽ? (���ñ��1~100)" << endl;
                cin >> t;
                REQUIRE_NOT_EXIST_POLYNOMIAL(t);
                pol[t].InitList();
                pol[t].CreatPolyn();
                cout << "Creat success\n\tPolynomial[" << t << "] = " << pol[t] << endl;
            }break;
            case 2:{ //��ʾ����ʽ
                cout << "��ʾ�ڼ�������ʽ? " << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                cout << "\tPolynomial[" << t << "] = " << pol[t] << endl;
            }break;
            case 3:{ //���ƶ���ʽ
                cout << "�ӵڼ�������ʽ���Ƶ��ڼ���? " << endl;
                cin >> src >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest].CopyPolyn(pol[src]);
                cout << "Copy success\n\tPolynomial[" << dest << "] = " << pol[dest] << endl;
            }break;
            case 4:{ //���ٶ���ʽ
                cout << "���ٵڼ�������ʽ?" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                pol[t].DestroyList();
                cout << "Destroy success\n\tPolynomial[" << t << "] doesn't exist now." << endl;
            } break;
            case 5:{ //��ն���ʽ
                cout << "��յڼ�������ʽ?" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                pol[t].ClearList();
                cout << "Clear success\n\tPolynomial[" << t << "] = " << pol[t] << endl;
            } break;
            case 6:{ //�޸Ķ���ʽ
                cout << "������Ҫ�޸ĵĶ���ʽ�����" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                double exp,co;
                cout << "������Ҫ�޸ĵ����ָ��(�������ڽ������)" << endl;
                cin >> exp;
                cout << "������Ҫ�޸ĵ����ϵ��(0��ʾɾ������)" << endl;
                cin >> co;
                pol[t].ChangeNode(co,exp);
                cout << "Polynomial[" << t << "] = " << pol[t] << endl;
            } break;
            case 7:{ //��ֵ
                cout << "��ڼ�������ʽ?" << endl;
                cin >> t;
                REQUIRE_EXIST_POLYNOMIAL(t);
                cout << "x = ? ";
                cin >> x;
                cout << "( " << pol[t] << " ) = " << pol[t].Value(x) << " for x = " << x << endl;
            }break;
            case 8:{ //���
                cout << "�ڼ����͵ڼ�����ӷŵ��ڼ���?" << endl;
                cin >> src >> src1 >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = pol[src] + pol[src1];
                cout << "( " << pol[src] << " ) + ( " << pol[src1] << " ) = " << pol[dest] << endl;
            }break;
            case 9:{ //���
                cout << "�ڼ����͵ڼ�������ŵ��ڼ���?" << endl;
                cin >> src >> src1 >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = pol[src] - pol[src1];
                cout << "( " << pol[src] << " ) - ( " << pol[src1] << " ) = " << pol[dest] << endl;
            }break;
            case 10:{ //�˷�
                cout << "�ڼ����͵ڼ�����˷ŵ��ڼ���?" << endl;
                cin >> src >> src1 >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_EXIST_POLYNOMIAL(src1);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = pol[src] * pol[src1];
                cout << "( " << pol[src] << " ) * ( " << pol[src1] << ") = " << pol[dest] << endl;
            }break;
            case 11:{ //����
                cout << "�ڼ����͵ڼ���������̺�����ֱ�ŵ��ڼ���?" << endl;
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
            case 12:{ //��˷�
                int expon;
                cout << "�Եڼ�������ʽ������,��Ϊ�ڼ�������ʽ?" << endl;
                cin >> src >> expon >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = Power(pol[src],expon);
                cout << "( " << pol[src] << " )^" << expon << " = " << pol[dest] << endl;
            }break;
            case 13:{ //��΢��
                cout << "�Եڼ�������ʽ��΢��,�󼸽�΢��,��Ϊ�ڼ�������ʽ?" << endl;
                cin >> src >> order >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = Differential(pol[src],order);
                cout << "d^" << order << "( " << pol[src] << " )/dx^" << order << " = " << pol[dest] << endl;
            } break;
            case 14:{ //��������
                cout << "�Եڼ�������ʽ�󲻶�����,��Ϊ�ڼ�������ʽ?" << endl;
                cin >> src >> dest;
                REQUIRE_EXIST_POLYNOMIAL(src);
                REQUIRE_NOT_EXIST_POLYNOMIAL(dest);
                pol[dest] = InIntegral(pol[src]);
                cout << "��("<< pol[src] <<")dx = " <<pol[dest] << "+Const" << endl;
            } break;
            case 15:{ //������
                cout << "�Եڼ�������ʽ�󶨻���,���ַ�Χ�Ӽ�����?" << endl;
                cin >> src >> a >> b;
                REQUIRE_EXIST_POLYNOMIAL(src);
                cout << "Integral (" << pol[src] << ") from " << a << " to " << b << " = " << DeIntegral(pol[src], a, b) << endl;
            } break;
            case 16:{ //gcd & lcm
                cout << "ȡ�ڼ����͵ڼ�������ʽ��gcd �� lcm �ֱ�ŵ��ڼ���?" << endl;
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
            case 17:{ //����ʽ��������
                cout << "����������������ʽ,֧��+-*/(),���ö���ʽ�ı�Ŵ������ʽ,�Ծ���(#)��β" << endl;
                cout << "�뱣֤����Ķ���ʽ����Ѿ����ڣ�������������в�����ֳ���0" << endl;
                Expression<Polynomial> expr;
                expr.Operand = string_to_polynomial;
                Polynomial ans = expr.Evaluate();
                cout << "Ans = " << ans << endl;
                ans.DestroyList();
            }break;
            case 18:{ //��������������
                cout << "����������������ʽ,�Ծ���(#)��β,֧��+-*/(),��֧�ָ���" << endl;
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
