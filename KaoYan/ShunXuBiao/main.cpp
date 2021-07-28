#include <iostream>
#include "defineList.h"
#include "operator.h"

using namespace std;

int main() {
    //��ʼ��
    Sqlist L;
    Operator ope;
    ope.initList(L);

    //��������
    ope.insertList(L, 1, 5);
    ope.insertList(L, 2, 3);
    ope.insertList(L, 1, 7);

    //��ӡ�б�
    ope.printList(L);

    //����Ԫ��
    int site;
    site = ope.locateList(L, 5);

    //ɾ������
    ElemType e;
    ope.deleteList(L, 2, e);
    cout << "ɾ����Ԫ��" << e << endl;
    ope.printList(L);

    //����Ԫ��
    site = ope.locateList(L, 5);

    //�����б�
    ope.destroyList(L);
    return 0;
}
