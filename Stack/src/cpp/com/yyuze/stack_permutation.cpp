#include<iostream>
using namespace std;
struct Stack {
	int* buffer;
	int capacity;
	int top = -1;
};

bool push(Stack& stack, int& element) {
	if (stack.top == stack.capacity) {
		return false;
	}
	stack.top++;
	stack.buffer[stack.top] = element;
	return true;

}

bool pop(Stack& stack, int& receiver) {
	if (stack.top == -1) {
		return false;
	}
	receiver = stack.buffer[stack.top];
	stack.top--;
	return true;
}

void init(Stack& stack, int capacity) {
	stack.capacity = capacity;
	stack.buffer = (int*)malloc(capacity * sizeof(int));
	stack.top = -1;
}

bool is_stack_empty(Stack& stack) {
	return stack.top == -1;
}

int& get_top(Stack& stack) {
	return stack.buffer[stack.top];
}
/*
	note: 
	    Variable "storage" is a co-buffer for understanding the algorithm
        To judge whether a sequence is a stack-permutation of aother one,
		just do a stack-permutation begining with the origin one!

bool is_permutation_sequence(int* origin, int* seq, int size, int* storage) {
	Stack* buf = (Stack*)malloc(sizeof(Stack));
	init(*buf, size);
	bool cmp_flag = false;
	int storage_pos = -1;
	int cmp_index = 0;
	for (int i = 0; (i < size) | cmp_flag; ++i) {
		while (cmp_flag) {
			if (seq[cmp_index] == get_top(*buf)) {
				int t;
				pop(*buf, t);
				storage_pos++;
				storage[storage_pos] = t;
				cmp_index++;
			}
			else {
				cmp_flag = false;
			}
		}
		if (origin[i] == seq[cmp_index]) {
			storage_pos++;
			storage[storage_pos] = origin[i];
			cmp_index++;
			cmp_flag = true && !is_stack_empty(*buf);
		}
		else {
			push(*buf, origin[i]);
		}
	}
	return is_stack_empty(*buf);
}

*/

bool is_permutation_sequence(int* origin, int* seq, int size) {
	Stack* buf = (Stack*)malloc(sizeof(Stack));
	init(*buf, size);
	bool cmp_flag = false;
	int cmp_index = 0;
	for (int i = 0; (i < size) | cmp_flag; ++i) {
		while (cmp_flag) {
			if (seq[cmp_index] == get_top(*buf)) {
				int t;
				pop(*buf, t);
				cmp_index++;
			}
			else {
				cmp_flag = false;
			}
		}
		if (origin[i] == seq[cmp_index]) {
			cmp_index++;
			cmp_flag = true && !is_stack_empty(*buf);
		}
		else {
			push(*buf, origin[i]);
		}
	}
	return is_stack_empty(*buf);
}

int main() {
	int seq1[] = {1,2,3,4};
	int seq2[4];
	int size = 4;
	for (int i = 0; i < 4; ++i) {
		char c;
		cin >> seq2[0] >> c >> seq2[1] >> c >> seq2[2] >> c >> seq2[3];
		cout << seq2[0] << " " << seq2[1] << " " << seq2[2] << " " << seq2[3] << endl;
		cin >> seq2[0] >> c >> seq2[1] >> c >> seq2[2] >> c >> seq2[3];
		cout << seq2[0] << " " << seq2[1] << " " << seq2[2] << " " << seq2[3] << endl;
		cout << is_permutation_sequence(seq1, seq2, size) << endl;
	}
	
	return 1;
}