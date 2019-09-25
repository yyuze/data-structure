#pragma once
#include<iostream>
#include<string>
using namespace std;
template<class T>
class LinkListWithHead {

private:


	class Node {

	private:
		T value;

		Node& next;

	public:


	

		void setValue(T value) {
			this->value = value;
		}

		void setNext(Node next) {
			this->next = next;
		}

		Node& getNext() {
			return this->next;
		}

		T getValue() {
			return this->value;
		}

		friend ostream& operator<<(ostream& out, Node& node) {
			out << node.getValue() + "";
			return out;
		}
	};

	Node& head;

	int length;


public:



	LinkListWithHead() {
		this->head = *(new Node());
		this->head.setNext(nullptr);
		this->length = 0;
	}

	bool insert(T nodeValue, int index) {
		if (index >= this->length) {
			this->append(nodeValue);
			return true;
		}
		else if (index <= 0) {
			return false;
		}
		else {
			Node& preNode = this->getNodeAt(index - 1);
			Node& nextNode = preNode.getNext();
			Node& node = *(new Node());
			preNode.setNext(node);
			node.setValue(nodeValue);
			node.setNext(nextNode);
			++this->length;
			return true;
		}
	}

	void append(T nodeValue) {
		Node& n = this->head;
		while (n.getNext() != nullptr) {
			n = n.getNext();
		}
		Node& node = *(new Node());
		node.setValue(nodeValue);
		node.setNext(nullptr);
		n.setNext(node);
		++this->length;
	}

	bool remove(int index) {
		if (index <= 0) {
			return false;
		}
		Node& node = this->getNodeAt(index - 1);
		node.setNext(node.getNext().getNext());
		--this->length;
		return true;

	}

	bool update(T nodeValue, int index) {
		if (index <= 0) {
			return false;
		}

		this->getNodeAt(index).setValue(nodeValue);
		return true;

	}

	int getFirstIndexOf(T nodeValue) {
		Node& node = this->head;
		int count = 0;
		while (node.getNext != nullptr) {
			if (node.getValue() == nodeValue) {
				return count;
			}
			node = node.getNext();
			count++;
		}
		return -1;
	}

	
	void traversePrint() {

		Node& node = this->head.getNext();
		for (int i = 0; i < this->length; i++) {
			cout << node << "->" << end;
			node = node.getNext();
		}
		cout << "" << endl;
	}

	void reverseList() {
		Node& t1 = this->head.getNext();
		Node& t2 = t1.getNext();
		Node& t3 = t2.getNext();
		t1.setNext(nullptr);
		t2.setNext(t1);
		while (t2.getNext() != nullptr) {
			t1 = t2;
			t2 = t3;
			t3 = t2.getNext();
			t2.setNext(t1);
		}
		this->head.setNext(t2);
	}

	T getValueAt(int index) {
		return this->getNodeAt(index).getValue();
	}

private:
	Node& getNodeAt(int index) {
		if (index <= 1) {
			index = 1;
		}
		if (index > this->length) {
			index = this->length;
		}
		Node& node = this->head;
		for (int count = 0; count < index; count++) {
			node = node.getNext();
		}
		return node;
	}
};