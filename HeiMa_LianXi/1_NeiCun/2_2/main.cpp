#include <iostream>

using namespace std;

int main() {

    int a = 10;
    int b = 20;
    //int &c; //�������ñ����ʼ��
    int &c = a; //һ����ʼ���󣬾Ͳ����Ը���
    c = b; //���Ǹ�ֵ���������Ǹ�������
    //��cָ��λ�õ����ݸ���Ϊb�����ݣ�a��cʼ�ն�ָ��ͬһ���ط�

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    /*
    a = 20
    b = 20
    c = 20
    */

    cout<<"a�ĵ�ַ��"<<&a<<endl;
    cout<<"c�ĵ�ַ��"<<&c<<endl;
    /*
    a�ĵ�ַ��0x61fe0c
    c�ĵ�ַ��0x61fe0c
    */

    system("pause");

    return 0;
}
