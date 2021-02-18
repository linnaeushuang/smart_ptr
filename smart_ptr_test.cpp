#include "shared_ptr.h"
#include <iostream>
#include <memory>


class A{
private:
	int a;
public:
	A():a(0){std::cout<<"class A"<<std::endl;}
	virtual int get(){ return a; }
	virtual void set(int x) { a=x+10; }
	virtual void print(){ std::cout<<"A, value:"<<a<<std::endl; }
	virtual ~A(){}
};


class B: public A{
private:
	int b;
public:
	B():b(100){std::cout<<"class B"<<std::endl;}
	virtual int get(){ return b; }
	virtual void set(int x) { b=x+100; }
	virtual void print(){ std::cout<<"B, value:"<<b<<std::endl; }
	virtual ~B(){}
};


class C: public B{
private:
	int c;
public:
	C():c(1000){std::cout<<"class C"<<std::endl;}
	virtual int get(){ return c; }
	virtual void set(int x) { c=x+1000; }
	virtual void print(){ std::cout<<"C, value:"<<c<<std::endl; }
	virtual ~C(){}
};




int main(){
	//test built-in type
	std::cout<<"-----test built-in type-----"<<std::endl;
	shared_ptr<int> int_ptr1(new int(4));
	shared_ptr<int> int_ptr2;
	std::cout<<"(int) construct, use count: "<<int_ptr1.use_count()<<", value:"<<*int_ptr1<<std::endl;
	int_ptr2 = int_ptr1;
	std::cout<<"(int) copy from ptr1, use count:"<<int_ptr2.use_count()<<", value:"<<*int_ptr2<<std::endl;

	shared_ptr<long> long_ptr1(new long(4));
	shared_ptr<long> long_ptr2;
	std::cout<<"(long) construct, use count: "<<long_ptr1.use_count()<<", value:"<<*long_ptr1<<std::endl;
	long_ptr2 = long_ptr1;
	std::cout<<"(long) copy from ptr1, use count:"<<long_ptr2.use_count()<<", value:"<<*long_ptr2<<std::endl;

	shared_ptr<double> double_ptr1(new double(4));
	shared_ptr<double> double_ptr2;
	std::cout<<"(double) construct, use count: "<<double_ptr1.use_count()<<", value:"<<*double_ptr1<<std::endl;
	double_ptr2 = double_ptr1;
	std::cout<<"(double) copy from ptr1, use count:"<<double_ptr2.use_count()<<", value:"<<*double_ptr2<<std::endl;



	//test class type
	std::cout<<"-----test class type-----"<<std::endl;
	shared_ptr<B> b_ptr(new B);
	std::cout<<"(B) construct, use count:"<<b_ptr.use_count()<<std::endl;
	shared_ptr<A> a_ptr;
	std::cout<<"(A) construct, use count:"<<a_ptr.use_count()<<std::endl;
	a_ptr=b_ptr;
	std::cout<<"(A) copy from b_ptr, use count:"<<a_ptr.use_count()<<std::endl;

	if(b_ptr) std::cout<<"(B) bool(), b_ptr is not empty"<<std::endl;

    a_ptr = std::move(b_ptr);
	if(!b_ptr&&a_ptr){
		std::cout<<"--b_ptr move to a_ptr--"<<std::endl;
		std::cout<<"b_ptr use count:"<<b_ptr.use_count()<<std::endl;
		std::cout<<"a_ptr use count:"<<a_ptr.use_count()<<std::endl;
	}

	std::cout<<"--A dynamic_cast to B--"<<std::endl;
	shared_ptr<A> dyn_a_ptr(new A);
	shared_ptr<B> dyn_b_ptr=dynamic_pointer_cast<B>(dyn_a_ptr);
	std::cout<<"dyn_a_ptr use count:"<<dyn_a_ptr.use_count()<<std::endl;
	std::cout<<"dyn_b_ptr use count:"<<dyn_b_ptr.use_count()<<std::endl;


	std::cout<<"--B dynamic_cast to B--"<<std::endl;
	shared_ptr<B> dyn_b_ptr1(new B);
	shared_ptr<B> dyn_b_ptr2=dynamic_pointer_cast<B>(dyn_b_ptr1);
	std::cout<<"dyn_b_ptr1 use count:"<<dyn_b_ptr1.use_count()<<std::endl;
	std::cout<<"dyn_b_ptr2 use count:"<<dyn_b_ptr2.use_count()<<std::endl;

	std::cout<<"--C dynamic_cast to B--"<<std::endl;
	shared_ptr<C> dyn_c_ptr(new C);
	shared_ptr<B> dyn_b_ptr3=dynamic_pointer_cast<B>(dyn_b_ptr1);
	std::cout<<"dyn_c_ptr use count:"<<dyn_c_ptr.use_count()<<std::endl;
	std::cout<<"dyn_b_ptr3 use count:"<<dyn_b_ptr3.use_count()<<std::endl;

	std::cout<<"--A static_cast to B--"<<std::endl;
	shared_ptr<A> static_a_ptr(new A);
	shared_ptr<B> static_b_ptr=static_pointer_cast<B>(static_a_ptr);
	std::cout<<"static_a_ptr use count:"<<static_a_ptr.use_count()<<std::endl;
	std::cout<<"static_b_ptr use count:"<<static_b_ptr.use_count()<<std::endl;


	std::cout<<"--B static_cast to B--"<<std::endl;
	shared_ptr<B> static_b_ptr1(new B);
	shared_ptr<B> static_b_ptr2=static_pointer_cast<B>(static_b_ptr1);
	std::cout<<"static_b_ptr1 use count:"<<static_b_ptr1.use_count()<<std::endl;
	std::cout<<"static_b_ptr2 use count:"<<static_b_ptr2.use_count()<<std::endl;

	std::cout<<"--C static_cast to B--"<<std::endl;
	shared_ptr<C> static_c_ptr(new C);
	shared_ptr<B> static_b_ptr3=static_pointer_cast<B>(static_b_ptr1);
	std::cout<<"static_c_ptr use count:"<<static_c_ptr.use_count()<<std::endl;
	std::cout<<"static_b_ptr3 use count:"<<static_b_ptr3.use_count()<<std::endl;

	std::cout<<"--const test--"<<std::endl;
	shared_ptr<const int> const_int(new int(3));
	shared_ptr<int> s=const_pointer_cast<int>(const_int);
	*s=10;
	std::cout<<"const_int:"<<*const_int<<", s:"<<*s<<std::endl;

	return 0;

}
