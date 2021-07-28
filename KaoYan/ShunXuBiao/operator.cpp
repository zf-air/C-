//
// Created by Hi! J.Smith on 2021/7/28.
//

#include "defineList.h"
#include "operator.h"

//��ʼ��
void Operator::initList(Sqlist &L) {
    L.data = new ElemType[InitSize];
    L.length = 0;
    L.MaxSize = InitSize;
    return;
}

//����Ԫ��
bool Operator::insertList(Sqlist &L, int i, ElemType e) {
    //�ж��Ƿ�Խ��
    if (i <= 0 || i > L.length + 1)
        return false;
    //�ж��Ƿ���λ��
    if (L.length == L.MaxSize)
        return false;
    //������
    for (int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j - 1];
    }
    //���
    L.data[i - 1] = e;
    //���ȼ�һ
    L.length++;
    return true;
}

//ɾ��Ԫ��
bool Operator::deleteList(Sqlist &L, int i, ElemType &e) {
    //�ж��Ƿ�Խ��
    if (i <= 0 || i > L.length)
        return false;
    //�ж��Ƿ�Ϊ��
    if (L.length == 0)
        return false;
    e = L.data[i - 1];
    for (int j = i - 1; j < L.length - 1; j++) {
        L.data[j] = L.data[j + 1];
    }
    L.length--;
    return true;
}

//����Ԫ��
int Operator::locateList(Sqlist L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            cout << "���ҵ�Ԫ��" << e << ",�ڵ�" << i << "��λ��" << endl;
            return i;
        }
    }
    cout << "δ���ҵ�Ԫ��" << e << endl;
    return -1;
}

//��ӡ����Ԫ��
void Operator::printList(Sqlist &L) {
    cout << "[";
    for (int i = 0; i < L.length; i++) {
        if (i == L.length - 1) {
            cout << L.data[i];
        } else {
            cout << L.data[i] << ",";
        }
    }
    cout << "]" << endl;
    return;
}

//�����б�
void Operator::destroyList(Sqlist &L) {
    delete[] L.data;
}