#include <iostream>

using namespace std;

//���������ã�ת��Ϊ int* const ref = &a;
void func(int& ref){
    ref = 100; // ref�����ã�ת��Ϊ*ref = 100
}
int main(){
    int a = 10;

    //�Զ�ת��Ϊ int* const ref = &a; ָ�볣����ָ��ָ�򲻿ɸģ�Ҳ˵��Ϊʲô���ò��ɸ���
    int& ref = a;
    ref = 20; //�ڲ�����ref�����ã��Զ�������ת��Ϊ: *ref = 20;

    cout << "a:" << a << endl; //20
    cout << "ref:" << ref << endl; //20

    func(a);

    cout << "a:" << a << endl; //100
    cout << "ref:" << ref << endl; //100
    return 0;
}
