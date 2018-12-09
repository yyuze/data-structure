#include "sequential_list.h"
#include<iostream>

using namespace std;
int main() {
	SequentialList<int>* list = new SequentialList<int>();
	cout << "insert 10 elements in list" << endl;
	for (int i = 0; i < 10; i++) {
		list->insert(i+1, i);
	}

	cout << "now length of list is " << list->getLength() << endl;
	
	cout << "the 3rd element is " << list->getElelment(3) << endl;
	
	cout << "first index of element \"5\" is " << list->getFirstIndexOf(5)<< endl;
	
	cout << "remove element \"5\"" << endl;
	list->remove(list->getElelment(list->getFirstIndexOf(5)));

	cout << "current element in list is :" << endl;
	list->traverse();

	cout << "list scend sorted" << endl;
	list->sort();

	cout << "get a sorted cloned list:" << endl;
	SequentialList<int>& clist = list->clone();
	clist.traverse();

	return 0;
}