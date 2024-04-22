#include<iostream>
#include<cstring>
#include<cctype>
#include<vector>
#include<cstdlib>
#include<cassert>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
// void change(int);
// int main(){
//     int a=3;
//     change(a);
//     cout<<a<<endl;
//     return 0;
// }
// void change(int a){
//     a=5;
// }
//交换两个指针所指的值
// void exchange(int* &pa,int* &pb){
// int* temp=pa;
// pa=pb;
// pb=temp;
// }
// int main(){
//     int a=3,b=5;
//     int*pa=&a;
//     int*pb=&b;
//     exchange(pa,pb);
//     cout<<*pa<<endl<<*pb<<endl;
//     return 0;
// }
//交换两个值
// void change(int &a,int &b){
// int temp=a;
// a=b;
// b=temp;
// }
// int main(){
//     int a=1;
//     int b=10;
//     change(a,b);
//     cout<<a<<endl<<b;
// }
//使用尾置返回类型声明一个返回数组指针的函数
// auto doit(int i)->int(*)[10];
//使用decltype声明一个返回数组指针的函数
//...
class Person{
    public:
    string name;
    string address;
    private:
    string getname(){
        return name;
    }
    string getaddress(){
        return address;
    }
};
int main(){
    class Person person={"wanggang","xian"};
    cout<<person.getname()<<endl<<person.getaddress();
}
// Sales_data::Sales_data(std::istream &is){
//     read(is,*this);
// }
