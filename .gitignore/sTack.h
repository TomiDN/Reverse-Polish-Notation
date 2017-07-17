/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Tomislav Nikolov
* @idnumber 45211
* @task 1
* @compiler VC
*
*/
#ifndef __STACK_HEADER_INCLUDED_
#define __STACK_HEADER_INCLUDED_
#include <iostream>

template<class T>
class sTack
{
public:
	sTack();
	~sTack();
	bool Empty()const;
	size_t Size()const{ return size; }
	size_t Capacity()const{ return cap; }
	T& Top();
	void Push(const T&);
	void Pop();
private:
	void Remove();
	void EditSize();
	void Resize(size_t);
private:
	T* cont;
	size_t size;
	size_t cap;
};

template<class T>
sTack<T>::sTack()
{
	cont = NULL;
	size = 0;
	cap = 0;
}

template<class T>
sTack<T>::~sTack()
{
	Remove();
}

template<class T>
bool sTack<T>::Empty()const
{
	if (size == 0)
		return true;
	return false;
}

template<class T>
T& sTack<T>::Top()
{
	if (size > 0)
		return cont[size - 1];
}

template<class T>
void sTack<T>::Push(const T& el)
{
	if (size == 0)
		Resize(2);
	if (size == cap)
		Resize(cap * 2);
	cont[size++] = el;
}

template<class T>
void sTack<T>::Pop()
{
	if (size > 0)
	{
		size--;
		if (size <= cap / 2)
			EditSize();
	}
}

template<class T>
void sTack<T>::Remove()
{
	delete[]cont;
	size = 0;
	cap = 0;
}

template<class T>
void sTack<T>::EditSize()
{
	Resize(cap / 2);
}

template<class T>
void sTack<T>::Resize(size_t newcap)
{
	T* newcont = new T[newcap];
	if (size != 0)
	{
		for (size_t i = 0; i < newcap; i++)
			newcont[i] = cont[i];
	}
	cap = newcap;
	delete[]cont;
	cont = newcont;
}

#endif