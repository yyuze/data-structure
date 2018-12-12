#include<iostream>


int main() {
	int* a = new int();
	*a = 0;
	int& b = *a;
	a++;
	b++;
	int& c = b;
	c++;
}