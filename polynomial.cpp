/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.10
file name: polynomial.cpp

���۷���
    example.          //explanation
Polynomial operator+(const Polynomial&, const Polynomial&);
Polynomial operator-(const Polynomial&, const Polynomial&);
Polynomial operator*(const Polynomial&, const Polynomial&);
    ����ʽ�����ʽ���
Polynomial operator*(const Polynomial&, const NodeData&);
    ����ʽ�뵥��ʽ���
Polynomial operator/(const Polynomial&, const Polynomial&);
Polynomial operator%(const Polynomial&, const Polynomial&);
Polynomial Differential(const Polynomial&, int order);
    ��߽�΢��
Polynomial InIntegral(const Polynomial&);
    ��������
double DeIntegral(const Polynomial&, double x0, double x1);
    ��x0��x1�Ķ�����
Polynomial Power(const Polynomial&, int expon);
Polynomial GCD(const Polynomial&, const Polynomial&);
Polynomial LCM(const Polynomial&, const Polynomial&);
std::ostream &operator<<(std::ostream&, const Polynomial&);

Polynomial(){};
    default constructors
Polynomial(int);
    ����һ������ʽ��ʹ��ֵΪ0
Polynomial(const Polynomial&);
    ����һ��������Ķ���ʽ��ȵĶ���ʽ

CreatPolyn();
    �������ݴ�������ʽ
CopyPolyn(const Polynomial&);
    ���ƶ���ʽ
ChangeNode(double coe,int expo);
    �ı����ʽ��һ���ڵ�
OrderInsert(NodeData node_data);
    �������һ���ڵ�
Value(const double x);
    �����ʽ��ֵ
get_degree() const;
    �����ʽ�Ĵ���
Coef() const;
    �����ʽ��ߴ���ϵ��

***************************************************/
#include <iostream>
#include <assert.h>
#include <math.h>
#include "polynomial.h"

using namespace std;

//#define DEBUG

//Pol_node* MakeNode(double coe,int expo){
//    Pol_node* ptr = new Pol_node;
//    ptr->data.co = coe;
//    ptr->data.exp = expo;
//    ptr->next = NULL;
//    return ptr;
//}
//
//Pol_node* MakeNode(Pol_node* node_src){  //����
//    Pol_node* ptr = new Pol_node;
//    ptr->data = node_src->data;
//   // ptr->data.exp = node_src->data.exp;
//    ptr->next = NULL;
//    return ptr;
//}

/**
int Polynomial::CreatPolyn(){ //β��
    int coe,expo;
    LNode* p = polyn_ = new LNode;
    do{
        cin>>coe>>expo;
      //  cout<<"creating"<<endl;
        if (coe!=0){
            p->next = MakeNode(coe,expo);
            p = p->next;
            //p->next = new LNode;     p = p->next;         p->co = coe;            p->exp = expo;
            p->next = NULL;
        }
    }while(coe);
    return 0;
}*/

double DifferentialFactor(int exponent, int dn)
{  //��΢������
    double ans = 1.0;
    while(dn>0){
        ans *= exponent;
        exponent--;
        dn--;
    }
    return ans;
}


/*********************************************************
//
//             friend function
*/
Polynomial operator+(const Polynomial& polyn1, const Polynomial& polyn2)
{
    PolNode* node_ptr1 = polyn1.list_ptr_->next;
    PolNode* node_ptr2 = polyn2.list_ptr_->next;
    Polynomial polyn_ans(0);// = new Polynomial;
    PolNode* node_ptr0 = polyn_ans.list_ptr_;
    while(node_ptr1 || node_ptr2){
        if ((node_ptr1 && node_ptr2 && node_ptr1->data.exp > node_ptr2->data.exp) || (node_ptr2 == NULL)){ //����ʽ1�ĵ�ǰ��ָ���ϴ�����ʽ2�Ѿ�û��
            node_ptr0->InsertNext(node_ptr1->data);
            NEXT(node_ptr1);
        }
        else
            if ((node_ptr1 && node_ptr2 && node_ptr1->data.exp < node_ptr2->data.exp) || (node_ptr1 == NULL)){ //����ʽ2�ĵ�ǰ��ָ���ϴ�����ʽ1�Ѿ�û��
                node_ptr0->InsertNext(node_ptr2->data);
                NEXT(node_ptr2);
            }
            else{
                node_ptr0->InsertNext(NodeData(node_ptr1->data.co + node_ptr2->data.co, node_ptr1->data.exp));//����ʽ1��2�ĵ�ǰ��ָ����ͬ
                NEXT(node_ptr1);
                NEXT(node_ptr2);
            }
        NEXT(node_ptr0);
        }
    polyn_ans.DeleteZore();
#ifdef DEBUG
    polyn_ans.Print();
#endif // DEBUG
    return polyn_ans;
}

Polynomial operator-(const Polynomial& polyn1, const Polynomial& polyn2)
{
    PolNode* node_ptr1 = polyn1.list_ptr_->next;
    PolNode* node_ptr2 = polyn2.list_ptr_->next;
    Polynomial polyn_ans(0);// = new Polynomial;
    PolNode* node_ptr0 = polyn_ans.list_ptr_;
    while(node_ptr1 || node_ptr2){
        if ((node_ptr1 && node_ptr2 && node_ptr1->data.exp > node_ptr2->data.exp) || (node_ptr2 == NULL)){ //����ʽ1�ĵ�ǰ��ָ���ϴ�����ʽ2�Ѿ�û��
                node_ptr0->InsertNext(node_ptr1->data);
            NEXT(node_ptr1);
        }
        else
            if ((node_ptr1 && node_ptr2 && node_ptr1->data.exp < node_ptr2->data.exp) || (node_ptr1 == NULL)){ //����ʽ2�ĵ�ǰ��ָ���ϴ�����ʽ1�Ѿ�û��
                node_ptr0->InsertNext(NodeData(-node_ptr2->data.co, node_ptr2->data.exp));
                NEXT(node_ptr2);
            }
            else{
                node_ptr0->InsertNext(NodeData(node_ptr1->data.co - node_ptr2->data.co, node_ptr1->data.exp));//����ʽ1��2�ĵ�ǰ��ָ����ͬ
                NEXT(node_ptr1);
                NEXT(node_ptr2);
            }
        NEXT(node_ptr0);
        }
    polyn_ans.DeleteZore();
#ifdef DEBUG
    polyn_ans.Print();
#endif // DEBUG
    return polyn_ans;
}

Polynomial operator*(const Polynomial& polyn1, const Polynomial& polyn2)
{
    PolNode* node_ptr1 = polyn1.list_ptr_->next;
    PolNode* node_ptr2 = polyn2.list_ptr_->next;
    Polynomial polyn_ans(0);
    while(node_ptr1){
        node_ptr2 = polyn2.list_ptr_->next;
        while(node_ptr2){
            NodeData node_data(node_ptr1->data.co * node_ptr2->data.co, node_ptr1->data.exp + node_ptr2->data.exp);
            polyn_ans.OrderInsert(node_data);
            NEXT(node_ptr2);
        }
        NEXT(node_ptr1);
    }
    polyn_ans.DeleteZore();
    return polyn_ans;
}

Polynomial operator*(const Polynomial& polyn_src, const NodeData& node_data)
{
#ifdef DEBUG
    cout<<"src "<<node_src.co<<" "<<node_src.exp<<" "; polyn_src.Print(); cout<<endl;
#endif // DEBUG
    Polynomial polyn_ans(0);
    PolNode* node_dest = polyn_ans.list_ptr_;
    PolNode* node_ptr = polyn_src.list_ptr_->next;
    while(node_ptr){
        node_dest->InsertNext(NodeData(node_ptr->data.co*node_data.co, node_ptr->data.exp+node_data.exp));
        NEXT(node_dest);
        NEXT(node_ptr);
    }
    polyn_ans.DeleteZore();
    return polyn_ans;
}

Polynomial operator/(const Polynomial& polyn1, const Polynomial& polyn_divisor)
{
    Polynomial polyn_quot(0); //quotient
    Polynomial polyn_rem(polyn1); //remainder
    Polynomial polyn_tmp;
    int delta_degree; //�̽ڵ��ָ��
    double coef; //�̽ڵ��ϵ��
    do{
        delta_degree = polyn_rem.get_degree() - polyn_divisor.get_degree();
        if (delta_degree>=0){
            coef = polyn_rem.Coef() / polyn_divisor.Coef();
            NodeData node_data(coef, delta_degree);
            polyn_tmp = polyn_divisor * node_data;
            polyn_rem = polyn_rem - polyn_tmp;
            polyn_quot.OrderInsert(node_data);
        }
    }while(delta_degree>0);
    polyn_quot.DeleteZore();
    return polyn_quot;
}

Polynomial operator%(const Polynomial& polyn1, const Polynomial& polyn_divisor)
{
    Polynomial polyn_quot(0); //quotient
    Polynomial polyn_rem(polyn1); //remainder
    Polynomial polyn_tmp;
    int delta_degree; //�̽ڵ��ָ��
    double coef; //�̽ڵ��ϵ��
    do{
        delta_degree = polyn_rem.get_degree() - polyn_divisor.get_degree();
        if (delta_degree>=0){
            coef = polyn_rem.Coef() / polyn_divisor.Coef();
            NodeData node_data(coef, delta_degree);
            polyn_tmp = polyn_divisor * node_data;
            polyn_rem = polyn_rem - polyn_tmp;
            polyn_quot.OrderInsert(node_data);
        }
    }while(delta_degree>0);
    polyn_rem.DeleteZore();
    return polyn_rem;
}

Polynomial Differential(const Polynomial& polyn_src, int order)
{
    PolNode* node_src = polyn_src.list_ptr_->next;
    Polynomial polyn_ans(0);
    PolNode* node_dest = polyn_ans.list_ptr_;
    double factor;
    while(node_src){
        if (node_src->data.exp >= order){
            factor = DifferentialFactor(node_src->data.exp, order);
            node_dest->InsertNext(NodeData(factor * node_src->data.co, node_src->data.exp - order));
        }
        else
            break;
        NEXT(node_src);
        NEXT(node_dest);
    }
    polyn_ans.DeleteZore();
    return polyn_ans;
}

Polynomial InIntegral(const Polynomial& polyn_src)
{ //��������
    PolNode* node_src = polyn_src.list_ptr_->next;
    Polynomial polyn_ans(0);// = new Polynomial;
    PolNode* node_dest = polyn_ans.list_ptr_;
    while(node_src){
        node_dest->InsertNext(NodeData(node_src->data.co / (node_src->data.exp+1), node_src->data.exp + 1));
        NEXT(node_src);
        NEXT(node_dest);
    }
    polyn_ans.DeleteZore();
    return polyn_ans;
}

double DeIntegral(const Polynomial& polyn_src, double x0, double x1)
{ //������
    Polynomial polyn_tmp;
    polyn_tmp = InIntegral(polyn_src);
    double ans = polyn_tmp.Value(x1) - polyn_tmp.Value(x0);
    polyn_tmp.DestroyList();
    return ans;
}


Polynomial Power(const Polynomial& polyn_src, int expon)
{
    Polynomial polyn1(polyn_src);
    Polynomial polyn0(0);
    Polynomial* p = &polyn1;
    Polynomial* q = &polyn0;
    Polynomial* polyn_ans = p;

    for (int i=1; i<expon; i++)
        if (polyn_ans==p){
            (*q) = (*p) * polyn_src;
            polyn_ans = q;
            p->DestroyList();
        } else{
            (*p) = (*q) * polyn_src;
            polyn_ans = p;
            q->DestroyList();
        }
    polyn_ans->DeleteZore();
    return (*polyn_ans);
}

Polynomial GCD(const Polynomial& polyn1, const Polynomial& polyn2)
{
    Polynomial polyn_dividend(polyn1);
    Polynomial polyn_divisor(polyn2);
    Polynomial polyn_remainder;
    do{
        polyn_remainder = polyn_dividend % polyn_divisor;
        polyn_dividend.DestroyList();
        polyn_dividend = polyn_divisor;
        polyn_divisor = polyn_remainder;
    }while(polyn_divisor.Coef()!=0);
    return polyn_dividend;
}

Polynomial LCM(const Polynomial& polyn1, const Polynomial& polyn2)
{
  //  Polynomial polyn_ans;
  //  polyn_ans = polyn1 * polyn2 / GCD(polyn1, polyn2);
    return polyn1 * polyn2 / GCD(polyn1, polyn2);
}

ostream &operator<<(ostream &os, const Polynomial& polyn)
{
    PolNode* p = polyn.list_ptr_;
    if (p->next == NULL){
        os << 0;
        return os;
    }
    while (p->next){
        NEXT(p);
        switch(p->data.exp){
            case 1:
                if (p->data.co == -1)
                    os << " - ";
                else if (p->data.co != 1)
                    os << p->data.co;
                os << "x";
                break;
            case 0:
                os << p->data.co;
                break;
            default:
                if (p->data.co == -1)
                    os << " - ";
                else if (p->data.co != 1)
                    os << p->data.co;
                os << "x^" << p->data.exp;
        }
        if (p->next){
            if (p->next->data.co>0)
                os << " + ";
            else
                os << " ";
        }
    }
    return os;
}



/*********************************************************
//
//                 constructors an
*/
Polynomial::Polynomial(int i)
{
    InitList();
}

Polynomial::Polynomial(const Polynomial& polyn_src)
{  //�������죿
    CopyPolyn(polyn_src);
}


/*********************************************************
//
//               general member function
*/
int Polynomial::CreatPolyn()
{  //
    double coe;
    int expo;
  //  LNode* p;
    cout << "��������������ָ����ϵ��,��ϵ��0����" << endl;
    do{
        cin >> expo >> coe;
        if (coe!=0){
            OrderInsert(NodeData(coe, expo));
            cout << "\tmake node success: ";
            switch(expo){
                case 1:
                    if (coe == -1)
                        cout << '-';
                    else if (coe != 1)
                        cout << coe;
                    cout << "x";
                    break;
                case 0:
                    cout << coe;
                    break;
                default:
                    if (coe == -1)
                        cout << '-';
                    else if (coe != 1)
                        cout << coe;
                    cout << "x^" << expo;
            }
            cout << endl;
        }
    }while(coe);
    DeleteZore();
    return 0;
}

int Polynomial::CopyPolyn(const Polynomial& polyn_src)
{ //���ƶ���ʽ(��һ������)
    InitList();
    PolNode* node_dest = list_ptr_;// = MakeNode(0, 0);
    PolNode* node_src = polyn_src.list_ptr_->next;
    while(node_src){
        node_dest->InsertNext(node_src->data);
        NEXT(node_dest);
        NEXT(node_src);
    }
    return 0;
}

int Polynomial::ChangeNode(double coe,int expo)
{ //�ı�ڵ����
    PolNode* p = list_ptr_;
    while (p->next && (p->next->data.exp > expo)){
        NEXT(p);
    }
    if (p->next == NULL || ((p->next->data.exp < expo))){  //û����Ӧ�Ľڵ㣬�����½ڵ�
        if (coe)
            p->InsertNext(NodeData(coe, expo));
    }
    else  // (p->next->exp == expo)���޸�ԭ�нڵ�
        if (coe==0)
            p->DeleteNext();
        else{
            p->next->data.co = coe;
        }
    return 0;
}

int Polynomial::DeleteZore()
{ //ɾ����Ч(ϵ��Ϊ0)�Ľڵ�
    PolNode* p = list_ptr_;
    while(p->next){
        if (p->next->data.co == 0)
            p->DeleteNext();
        else
            NEXT(p);
    }
    return 0;
}

int Polynomial::OrderInsert(NodeData node_data)
{  //��ָ���������ڵ�
    assert (list_ptr_);
    PolNode* p = list_ptr_;
    while (p->next && (p->next->data.exp > node_data.exp)){
        NEXT(p);
        //p = p->next;
    }
    if (p->next && (p->next->data.exp == node_data.exp))
        p->next->data.co += node_data.co;
    else
        p->InsertNext(node_data);
    return 0;
}

double Polynomial::Value(double x)
{ //��ֵ
    assert(list_ptr_);
    PolNode* node_ptr = list_ptr_->next;
    double ans = 0;
    while(node_ptr){
        ans += node_ptr->data.co * pow(x, node_ptr->data.exp);
        NEXT(node_ptr);
    }
    return ans;
}

/*********************************************************
//
//               input/output function
*/
int Polynomial::get_degree() const
{
    if (list_ptr_->next)
        return(list_ptr_->next->data.exp);
    else
        return 0;
}

double Polynomial::Coef() const
{
    if (list_ptr_->next)
        return(list_ptr_->next->data.co);
    else
        return 0;
};

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
