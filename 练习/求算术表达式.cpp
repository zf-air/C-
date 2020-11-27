#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<iostream>
#include<stack>
#include<string>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;
typedef int Status;
typedef char SElemType;
typedef struct
{//˳��ջ�Ĵ洢�ṹ
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
Status InitStack(SqStack &S)
{//��ʼ��������һ����ջS
    S.base=new SElemType[MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return OK;
}
Status Push(SqStack &S,SElemType e)
{//��ջ
    if(S.top-S.base==S.stacksize) return ERROR;
    *S.top++=e;
    return OK;
}
Status Pop(SqStack &S,SElemType &e)
{//��ջ��ɾ��S��ջ��Ԫ�أ���e������ֵ
    if(S.top==S.base)
    return ERROR;
    e=*--S.top;
    return OK;
}
SElemType GetTop(SqStack S)
{//ȡջ��Ԫ�� ������S��ջ��Ԫ�أ����޸�ջ��ָ��
    if(S.top!=S.base)
    return *(S.top-1);
}
int In(SElemType c)
{//�ж�c�Ƿ�Ϊ�����
    switch(c)
    {
    case'+':return OK;
    case'-':return OK;
    case'*':return OK;
    case'/':return OK;
    case'(':return OK;
    case')':return OK;
    case'#':return OVERFLOW;
    default:return ERROR;
    }
}
SElemType Precede(SElemType t1,SElemType t2)
{//�ж������t1��t2�����ȼ�
    SElemType f;
    switch(t2)
    {
    case'+':
    case'-':if(t1=='('||t1=='#')
                f='<';
            else
                f='>';
            break;
    case'*':if(t1=='*'||t1=='/'||t1==')')
                f='>';
            else
                f='<';
            break;
    case'/':if(t1=='*'||t1=='/'||t1==')')
                f='>';
            else
                f='<';
            break;
    case'(':f='<';
    case')':if(t1=='(')
                f='=';
            else
                f='>';
            break;
    case'#':if(t1=='#')
                f='=';
            else
                f='>';
    }
    return f;
}
SElemType Operate(SElemType a,SElemType theta,SElemType b)
{//��a��b���ж�Ԫ����theta
    SElemType c;
    a=a-48;
    b=b-48;
    switch(theta)
    {
    case'+':c=a+b+48;
            break;
    case'-':c=a-b+48;
            break;
    case'*':c=a*b+48;
            break;
    case'/':c=a/b+48;
            break;
    }
    return c;
}
char EvaluateExpression()
{//�������ʽ��ֵ����OPTR��OPND�ֱ�Ϊ�����ջ�Ͳ�����ջ
    SqStack OPND,OPTR;
    InitStack(OPND);
    InitStack(OPTR);
    char ch,a,b,theta,x;
    Push(OPTR,'#');
    cin>>ch;
    while(ch!='#'||GetTop(OPTR)!='#')
    {
        if(!In(ch))
        {
            Push(OPND,ch);
            cin>>ch;
        }
        else
        {
            switch(Precede(GetTop(OPTR),ch))
            {
                case '<':
                    Push(OPTR,ch);
                    cin>>ch;
                    break;
                case '>':
                    Pop(OPTR,theta);
                    Pop(OPND,b);
                    Pop(OPND,a);
                    Push(OPND,Operate(a,theta,b));
                    break;
                case '=':
                    Pop(OPTR,x);
                    cin>>ch;
                    break;
            }
        }
    }
    return GetTop(OPND)-48;
}
int main()
{
   cout<<"�������������ʽ,����#����."<<endl;
   cout<<EvaluateExpression()<<endl;
   return 0;
}

