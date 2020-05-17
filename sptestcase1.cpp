//简单测试智能指针的创建及销毁

#include<iostream>
#include "SmartPointer.h"

class SomeClass{
public:
  SomeClass(){
    std::cout<<"SomeClass default constructor !"<<std::endl;
  }
};

void testcase1(){
  SmartPointer<char> spunknown; //创建不知所指的智能指针
  SmartPointer<char> spnull = NULL; //创建空指针
  SmartPointer<SomeClass> spclass = new SomeClass;//创建指向类实例的指针
  SmartPointer<const char> spstr = "Hello World!";//创建指向字符串的指针

}

int main(){
  testcase1();
  return 0;
}
