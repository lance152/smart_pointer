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
  void func(){
    std::cout<<"SomeClass func()"<<std::endl;
  }
};

class OtherClass: public RefBase{
public:
  OtherClass(){
    std::cout<<"OtherClass default constructor !"<<std::endl;
  }
  ~OtherClass(){
    std::cout<<"OtherClass deconstructor !"<<std::endl;
  }
  void func(){
    std::cout<<"OtherClass func()"<<std::endl;
  }
};

//解引用测试
void testcase4_1(void){
  std::cout<<"=======testcase4_1======="<<std::endl;
  SmartPointer<SomeClass> spsomeclass = new SomeClass();
  (*spsomeclass).func();
  spsomeclass->func();
  std::cout<<"========================="<<std::endl;
}

//判空与比较测试
void testcase4_2(void){
  std::cout<<"=======testcase4_2======="<<std::endl;
  SomeClass *pSomeClass = new SomeClass();
  SmartPointer<SomeClass> spsomeclass = pSomeClass;

  SmartPointer<OtherClass> spotherclass = new OtherClass();
  SmartPointer<OtherClass> spotherclass2 = spotherclass;

  if(spsomeclass==NULL) std::cout<<"spsomeclass is NULL pointer"<<std::endl;
  if(spotherclass!=NULL) std::cout<<"spotherclass is not NULL pointer"<<std::endl;
  if(spsomeclass == pSomeClass) std::cout<<"spsomeclass and pSomeClass are same pointer"<<std::endl;
  if(spsomeclass!=pSomeClass) std::cout<<"spsomeclass and pSomeClass are not same pointer"<<std::endl;

  //     if (spsomeclass != spotherclass) // ERROR !
  //        std::cout<< "spsomeclass and spotherclass are not same pointer" << std::endl;
  //     if (spsomeclass == spotherclass) // ERROR !
  //        std::cout<< "spsomeclass and spotherclass are same pointer" << std::endl;
  if (spotherclass == spotherclass2) std::cout<< "spotherclass and spotherclass2 are same pointer" << std::endl;
  if (spotherclass != spotherclass2) std::cout<< "spotherclass and spotherclass2 are not same pointer" << std::endl;
  std::cout << "==========================" <<std::endl;
}

int main(void){
  testcase4_1();
  testcase4_2();
  return 0;
}
