//定义smartpointer类
//每次析构的时候计数-1
//当计数为0的时候自动释放内存

//普通指针的创建
//char* punkown; 创建一个不知所指的指针
//char* pnull=NULL; 创建空指针
//const char* pstr = "Hello World!"; 创建字符串指针
//SomeClass *pclass = new SomeClass(); 创建指向类的实例的指针
//SomeClass *pclassother = pclass; 从同类型指针创建

//所以我们的smartpointer也要满足相应的用法
//SmartPointer spunknown;
//SmartPointer spnull = NULL;
//SmartPointer spstr = "Hello World!";
//SmartPointer spclass = new SomeClass();

//但是这样会丢失所指对象的类型信息
//所以我们要将smartpointer定义为模板类

//SmartPointer<char> spunknown; 创建一个不知所指的智能指针
//SmartPointer<char> spnull = NULL;创建空智能指针
//SmartPointer<SomeClass> spclass = new SomeClass; 创建指向具体类的智能指针
//SmartPointer<const char> spstr = "Hello world!"; 创建字符串的智能指针

#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

template<typename T>
class SmartPointer
{
public:
  //根据上面的描述，我们首先要有一个默认的构造函数来创建不知所指的smartpointer
  //还需要一个可以指定任何指针类型的参数的构造函数，创建指向具体内存资源或者null的smartpointer
  SmartPointer():mPointer(NULL){
    std::cout<<"create unknown smart pointer."<<std::endl;
  } //默认构造函数
  SmartPointer(T* p):mPointer(p){
    std::cout<<"create smart pointer at "<<static_cast<const void*>(p)<<std::endl;

    //这里类的引用计数要加1
    if(mPointer) mPointer->incRefCount();
  }//接受指定类型的指针参数

  //析构函数
  ~SmartPointer(){
    std::cout<<"release smart pointer at "<<static_cast<const void*>(mPointer)<<std::endl;
    //这里除非引用计数为0才销毁
    if(mPointer && mPointer->decRefCount()==0) delete mPointer;
  }

  //拷贝构造函数
  //解决 SmartPointer<SomeClass> spclassother = spclass1这种情况
  SmartPointer(const SmartPointer& other):mPointer(other.mPointer){
    std::cout<<"Copy smart pointer at "<<static_cast<const void*>(other.mPointer)<<std::endl;

    if(mPointer) mPointer->incRefCount();
  }

  //重载=
  //处理
  //spclass1=new SomeClass
  //SmartPointer<SomeClass> spclass2 = new SomeClass;
  //spclass2 = spclass1
  SmartPointer& operator=(const SmartPointer &other){
    // //处理自我赋值
    // if(this==&other) return *this;
    // //处理底层指针
    // if(mPointer) delete mPointer;
    // mPointer = other.mPointer;
    // std::cout<<"Assign smart pointer at "<<static_cast<const void*>(other.mPointer)<<std::endl;
    // return *this;

    //这里的实现需要把新指向的对象引用计数加1，并把原指向的对象引用计数减1，如果原指向的对象计数为0则要delete

    T *temp(other.mPointer); //新指向的对象
    if (temp) temp->incRefCount(); //新指向的对象引用计数加1
    if(mPointer && mPointer->decRefCount()==0) delete mPointer; //原指向对象引用计数减1，如果为0则delete

    mPointer = temp;
    return *this;
  }

  //重载->和*使smartpointer可以和正常指针一样使用
  T* operator->() const{
    return mPointer;
  }

  T& operator*() const{
    return *mPointer;
  }

  //实现需求1 if(!sp) or if(sp)
  //需求2 if(sp==NULL),if(sp!=null),if(sp==p)
  //需求3 if(sp1==sp2)
  //对于需求1，我们可以用重载bool()的方式，但是这样会导致需求3返回错误信息
  //我们当然也可以用safe bool idiom来实现需求1
  //但考虑到需求2可以包含需求1，我们只要重载==和!=即可
  //重载==和!=
  //每一个都要实现smartpointer和原指针的比较以及智能指针之间的比较
  bool operator ==(const T* o) const{
    return mPointer == o;
  }

  bool operator ==(const SmartPointer& o) const{
    return mPointer==o.mPointer;
  }

  bool operator !=(const T* o) const{
    return mPointer!=o;
  }

  bool operator !=(const SmartPointer& o) const{
    return mPointer!=o.mPointer;
  }

private:
  T* mPointer; //指向smartpointer实际对应的资源对象
};

//这里定义一个引用计数基类
//这样我们可以让我们的类继承自这个基类来实现引用计数
//这样我们的类就不用每次都加上引用计数
class RefBase
{
public:
  RefBase():mCount(0){}

  void incRefCount(){
    mCount++;
  }

  int decRefCount(){
    return --mCount;
  }
  //返回引用计数
  int getRefCount(){
    return mCount;
  }

private:
  int mCount;
};

#endif
