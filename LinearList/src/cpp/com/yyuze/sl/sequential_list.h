#ifndef LINEARLIST_CPP_COM_YYUZE_SL_SEQUENTIALLIST_H_
#define LINEARLIST_CPP_COM_YYUZE_SL_SEQUENTIALLIST_H_

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
		free(this->addr);
	}

	void clearList();

	int getLength();

	T& getElelment(int index);

	int getFirstIndexOf(T element);

	bool insert(T element,int index);

	bool remove(T& element);

	void traverse();
	
	SequentialList<T>& clone();

	void sort();
};


#endif // !LINEARLIST_CPP_COM_YYUZE_DS_SEQUENTIALLIST_H_