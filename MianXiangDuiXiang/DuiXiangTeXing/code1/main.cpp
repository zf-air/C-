#include <iostream>

using namespace std;

class Person{
public:
    Person(){
        cout<<"Person���޲ι��캯��"<<endl;
    }
    Person(int a){
        age=a;
        cout<<"Person���вι��캯��"<<endl;
    }

    //�������캯��
    Person(const Person &p){
        age=p.age;
        cout<<"Person�Ŀ������캯��"<<endl;
    }

    ~Person(){
        cout<<"Person����������"<<endl;
    }
private:
    int age;
};

void test(){
    Person p;
    Person p1(10);
    Person p2(p1);

}
int main()
{
    test();

    return 0;
}
