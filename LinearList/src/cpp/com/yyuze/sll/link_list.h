#pragma once
#include<iostream>
using namespace std;
template<class T>
class LinkList {
private:
	class Node{
	private:
		T value;

		Node& next;
	public:
		T getValue() {
			return this->value;
		}

		Node& getNext() {
			return this->next;
		}

		void setValue(T value) {
			this->value = value;
		}

		void setNext(Node next) {
			this->next = next;
		}
	};

	Node& head;

	int length;

public:
	LinkList() {
		this->length = 0;
	}

	bool insert(T value,int index) {
		Node& node = *(new Node());
		node.setValue(value);
		if (this->head == nullptr) {
			this.head = node;
			++this->length;
			return true;
		}
		else {
			if (index >= this->length-1) {
				this->append(value);
				return true;
			}
			if (index <= 0) {
				node.setNext(this->head);
				this->head = node;
				++this->length;
				return true;
			}
			Node& preNode = this->getNodeAt(index - 1);
			Node& nextNode = preNode.getNext();
			preNode.setNext(node);
			node.setNext(nextNode);
			this->length++;
			return true;
		}
	}

	bool append(T value) {
		Node& node = *(new Node());
		node.setValue(value);
		this->getNodeAt(this->length-1).setNext(node);
		return true;
	}

	bool remove(int index) {
		if (index <= 0) {
			this->head = this->head.getNext();
			--this->length;
			return true;
		}
		if (index >= length-1) {
			index = this->length - 1;
		}
		Node& preNode = this->getNodeAt(index - 1);
		preNode.setNext(preNode.getNext().getNext());
		--this->length;
		return true;
	}

	bool update(T value, int index) {
		if (index < 0 || index >= this->length) {
			return false;
		}
		this->getNodeAt(index).setValue(value);
	}

	T getValueAt(int index) {
		return this->getNodeAt(index).getValue();
	}

	void traversePrint() {
		Node& node = this->head;
		while (node.getNext() != nullptr) {
			cout << node.getValue()<<"->"<< end;
			node = node.getNext();
		}
		cout << "" << endl;
	}

	void reverseList() {
		Node& t1 = this->head;
		Node& t2 = t1.getNext();
		Node& t3 = t2.getNext();
		t1.setNext(nullptr);
		t2.setNext(t1);
		while(t2.getNext()!=nullptr) {
			t1 = t2;
			t2 = t3;
			t3 = t2.getNext();
			t2.setNext(t1);
		}
	}

private:
	Node& getNodeAt(int index) {
		if (index < 0) {
			index = 0;
		}
		if (index >= this->length) {
			index = this->length-1;
		}
		Node& node = this->head;
		for (int i = 0; i <= index; i++) {
			node = node.getNext();
		}
		return node;
	}

};
