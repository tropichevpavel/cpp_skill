
#include <iostream>

class BinaryHeap {
	int type = 0;
	int* heap;
	int capacity;
	int size;

	int parentPos(int pos) { return (pos - 1) / 2; }
	int leftPos(int pos) { return 2 * pos + 1; }
	int rightPos(int pos) { return 2 * pos + 2; }

public:
	BinaryHeap(const int& type, const int& capacity) : type(type), capacity(capacity) {
		heap = new int[capacity];
	}

	void build() {

	}

	void add(const int& data) {
		if (size == capacity) {
			std::cout << "Owerflow: no place to add" << std::endl;
			return;
		}

		int curPos = size;

		heap[size++] = data;

		int pPos = parentPos(curPos);

		if (type)
			while (curPos != 0 && heap[curPos] < heap[pPos]) {
				swap(&heap[curPos], &heap[pPos]);
				curPos = pPos;
				pPos = parentPos(curPos);
			}
		else
			while (curPos != 0 && heap[curPos] > heap[pPos]) {
				swap(&heap[curPos], &heap[pPos]);
				curPos = pPos;
				pPos = parentPos(curPos);
			}
	}

	int extracRoot() {
		if (!size) return INT_MAX;
		if (size == 1) {
			--size;
			return heap[0];
		}

		int root = heap[0];
		heap[0] = heap[--size];

		fix(0);
		return root;
	}

	void sort() {
		while (size)
			std::cout << extracRoot() << " ";
		std::cout << std::endl;
	}

	void fix(const int& pos) {
		if (type == 0) fixMin(pos);
		else fixMax(pos);
	}

	void fixMin(const int& pos) {
		int lpos = leftPos(pos);
		int rpos = rightPos(pos);

		int minPos = pos;

		if (lpos < size && heap[lpos] < heap[minPos])
			minPos = lpos;

		if (rpos < size && heap[rpos] < heap[minPos])
			minPos = rpos;

		if (minPos != pos) {
			swap(&heap[pos], &heap[minPos]);
			fix(minPos);
		}
	}

	void fixMax(const int& pos) {
		int lpos = leftPos(pos);
		int rpos = rightPos(pos);

		int maxPos = pos;

		if (lpos < size && heap[lpos] > heap[maxPos])
			maxPos = lpos;

		if (rpos < size && heap[rpos] > heap[maxPos])
			maxPos = rpos;

		if (maxPos != pos) {
			swap(&heap[pos], &heap[maxPos]);
			fix(maxPos);
		}
	}

	void swap(int* a1, int* a2) {
		int* tmp = a2;
		a1 = a2;
		a2 = tmp;
	}

	~BinaryHeap() {
		delete heap;
	}
};
