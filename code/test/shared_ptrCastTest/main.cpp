#include<iostream>
#include <memory>

class Base {
protected:
	Base(const Base& other) : m_val(other.m_val) {}
	Base& operator=(const Base& other) = delete;

public:
	Base(int val) : m_val(val) {}
	virtual ~Base() {}

	virtual std::shared_ptr<Base> CloneThis() 
	{ 
		return std::shared_ptr<Base>(new Base(*this)); 
	};

//protected:
	int m_val;
};

class Derived : public Base {
protected:
	Derived(const Derived& other) : Base(other), m_derivedVal(other.m_derivedVal) {}
	Derived& operator=(const Derived& other) = delete;
public:
	Derived(int val, int derivedVal) : Base(val), m_derivedVal(derivedVal) {}
	virtual ~Derived() {}

	virtual std::shared_ptr<Base> CloneThis() 
	{
		return std::shared_ptr<Derived>(new Derived(*this));
	};
//private:
	int m_derivedVal;
};

int main() {
	//Derived d1(1, 2);
	//Derived d2 = d1; // 调用拷贝构造函数
	//Derived d3(3, 4);
	//d3 = d2; // 调用赋值运算符

	std::shared_ptr<Base> pValue1(new Derived(10, 20));
	std::shared_ptr<Base>  pValue2 = pValue1->CloneThis();;

	pValue1->m_val = 30;

	return 0;
}