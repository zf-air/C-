#include <iostream>

using namespace std;

//����Ȩ��
//����Ȩ��  public     ���ڿ��Է���  ������Է���
//����Ȩ��  protected  ���ڿ��Է���  ���ⲻ���Է���
//˽��Ȩ��  private    ���ڿ��Է���  ���ⲻ���Է���

class Person
{
    //����  ����Ȩ��
public:
    string m_Name;

    //����  ����Ȩ��
protected:
    string m_Car;

    //���п�����  ˽��Ȩ��
private:
    int m_Password;

public:
    void func()
    {
        m_Name = "����";
        m_Car = "������";
        m_Password = 123456;
    }
};

int main() {

    Person p;
    p.m_Name = "����";
    //p.m_Car = "����";  //����Ȩ��������ʲ���
    //p.m_Password = 123; //˽��Ȩ��������ʲ���

    system("pause");

    return 0;
}
