#include<iostream>
#include "link_list_with_head.h"
#include<string>
using namespace std;

int main() {
	LinkListWithHead<string>& list = *(new LinkListWithHead<string>());
	cout << "append 0~9" << endl;
	for (int i = 0; i < 10; i++) {
		list.append(i+"");
	}
	cout << "list now has:" << endl;
	list.traversePrint();
	cout << "list insert -1,7,11" << endl;
	list.insert(-1+"", 0);
	list.insert(7 + "", 6);
	list.insert(11 + "", 10);
	cout << "list now has:" << endl;
	list.traversePrint();
}