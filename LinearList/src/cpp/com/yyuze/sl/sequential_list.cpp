#include "sequential_list.h"
#include<iostream>
using namespace std;
template<class T>
void SequentialList<T>::clearList()
{
	for (int i = 0; i < this->length; ++i) {
		free(this->addr + i);
	}
}

template<class T>
int SequentialList<T>::getLength()
{
	return this->length;
}

template<class T>
T & SequentialList<T>::getElelment(int index)
{
	return this->addr + index;
}

template<class T>
int SequentialList<T>::getFirstIndexOf(T element)
{
	for (int i = 0; i < this->length; ++i) {
		if (element == *(this->addr + i)) {
			return i;
		}
	}
	return -1;
}

template<class T>
bool SequentialList<T>::insert(T element, int index)
{
	T& temp = this->addr + index;
	for (int i = index; i < this->length; ++i) {
		T& t = this->addr + i + 1;
		this->addr + i + 1 = temp;
		temp = t;
	}
	*(this->addr + index) = element;
	++this->length;
	return true;
}

template<class T>
bool SequentialList<T>::remove(T & element)
{
	T* addr = &element;
	free(addr);
	int position = (addr - this->addr) / sizeof(T*);
	for (int i = position; i < this->length-1; ++i) {
		*(addr + i) = *(addr + i + 1);
	}
	--this->length;
	return true;
}

template<class T>
void SequentialList<T>::traverse()
{
	for (int i = 0; i < this->length; ++i) {
		cout << *this->addr + i << endl;
	}
}

template<class T>
SequentialList<T>& SequentialList<T>::clone()
{
	SequentialList<T>* newList = new SequentialList<T>();
	for (int i = 0; i < this->length; i++) {
		newList->insert(*(this->addr + i), i);
	}
	return newList;
}

template<class T>
void SequentialList<T>::sort()
{
	for (int i = 0; i < this->length; ++i) {
		bool sortedFlag = true;
		for (int j = 0; j < length - i - 1; ++j) {
			if (*(this->addr + j) > *(this->addr + j + 1)) {
				T& temp = this->addr + j + 1;
				*(this->addr + j + i) = *(this->addr + j);
				*(this->addr + j) = temp;
				sortedFlag = false;
			}
		}
		if (sortedFlag) {
			return;
		}
	}
}