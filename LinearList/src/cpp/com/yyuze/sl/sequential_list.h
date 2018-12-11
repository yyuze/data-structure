#ifndef LINEARLIST_CPP_COM_YYUZE_SL_SEQUENTIALLIST_H_
#define LINEARLIST_CPP_COM_YYUZE_SL_SEQUENTIALLIST_H_
#include<iostream>
using namespace std;
template<class T>
class SequentialList
{
private: 
	T* addr;
	int length;
public:
	SequentialList() 
	{
		this->addr = new T();
	}
	
	~SequentialList() 
	{
		this->clearList();
	} 

	void clearList() {
		for (int i = 0; i < this->length; ++i) {
			*(this->addr + i)=0;
		}
	}

	int getLength() {
		return this->length;
	}

	T& getElelment(int index) {
		return *(this->addr + index);
	}

	int getFirstIndexOf(T element) {
		for (int i = 0; i < this->length; ++i) {
			if (element == *(this->addr + i)) {
				return i;
			}
		}
		return -1;
	}

	bool insert(T element, int index) {
		if (index > this->length) {
			index = this->length;
		}
		T temp = *(this->addr + index);
		for (int i = index; i < this->length; ++i) {
			T t = *(this->addr + i + 1);
			*(this->addr + i + 1 )= temp;
			temp = t;
		}
		*(this->addr + index) = element;
		++this->length;
		return true;
	}

	bool remove(T& element) {
		int position = &element - this->addr;
		for (int i = position; i < this->length - 1; ++i) {
			*(this->addr + i) = *(this->addr + i + 1);
		}
		--this->length;
		return true;
	}

	void traverse() {
		for (int i = 0; i < this->length; ++i) {
			cout << *(this->addr + i )<< endl;
		}
	}
	
	SequentialList<T>& clone() {
		SequentialList<T>* newList = new SequentialList<T>();
		for (int i = 0; i < this->length; i++) {
			newList->insert(*(this->addr + i), i);
		}
		return *newList;
	}

	void sort() {
		for (int i = 0; i < this->length; ++i) {
			bool sortedFlag = true;
			for (int j = 0; j < length - i - 1; ++j) {
				if (*(this->addr + j) > *(this->addr + j + 1)) {
					T temp = *(this->addr + j + 1); 
					*(this->addr + j + 1) = *(this->addr + j);
					*(this->addr + j) = temp;
					sortedFlag = false;
				}
			}
			if (sortedFlag) {
				return;
			}
		}
	}
};


#endif // !LINEARLIST_CPP_COM_YYUZE_DS_SEQUENTIALLIST_H_