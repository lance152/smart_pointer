#include <iostream>
#include "SmartPointer.h"

class SomeClass: public RefBase{
public:
  SomeClass(){
    std::cout<<"SomeClass default constructor !"<<std::endl;
  }
  ~SomeClass(){
    std::cout<<"SomeClass deconstructor !"<<std::endl;
  }
};

void testcase3(void){
  SomeClass *pSomeClass = new SomeClass();
  SmartPointer<SomeClass> spOuter = pSomeClass;
  std::cout<<"SomeClass Ref Count ("<<pSomeClass->getRefCount()<<") outer 1."<<std::endl;
  {//inner 语句块
    SmartPointer<SomeClass> spInner = spOuter; //这里spInner只在这个语句块中存活
    std::cout<<"SomeClass Ref Count ("<<pSomeClass->getRefCount()<<") inner 1."<<std::endl;
  }
  std::cout<<"SomeClass Ref Count ("<<pSomeClass->getRefCount()<<") outer 2."<<std::endl;

  std::cout<<"new another SomeClass class for spOuter."<<std::endl;
  SmartPointer<SomeClass> spOuter2 = new SomeClass();
  spOuter = spOuter2;
}

int main(void){
  testcase3();
  return 0;
}
