#include <iostream>
#include "defineList.h"
#include "operator.h"
using namespace std;

int main() {
    //��ʼ��
    Sqlist L;
    Operator ope;
    ope.initList(L);
    cout<<"�Ұ���"<<endl;
    //��������
    ope.insertList(L,1,5);
    ope.insertList(L,2,3);
    ope.insertList(L,1,7);

    //��ӡ�б�
    ope.printList(L);

    //ɾ������
    ElemType e;
    ope.deleteList(L,2,e);
    cout<<"ɾ����"<<e<<endl;
    ope.printList(L);

    //�����б�
    ope.destroyList(L);
    return 0;
}
