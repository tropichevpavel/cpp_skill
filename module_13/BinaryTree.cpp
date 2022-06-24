
#include <iostream>

class BinaryTree {
	struct Node {
		int data;
		Node* parent;

		Node* leftChild;
		Node* rightChild;

		Node(int data, Node* parent = nullptr) : data(data), parent(parent) {
			leftChild = nullptr;
			rightChild = nullptr;
		}
		~Node() {
			if (leftChild) delete leftChild;
			if (rightChild) delete rightChild;
		}
	};

	Node* root = nullptr;

public:
	BinaryTree() = default;
	~BinaryTree() {
		if (root) delete root;
	}

	void add(int data) {
		if (!root) root = new Node(data);
		else {
			Node* cur = root;
			Node* add = nullptr;

			while (!add) {
				if (cur->data >= data) {
					if (!cur->leftChild)
						add = cur->leftChild = new Node(data, cur);

					cur = cur->leftChild;
					continue;

				} else {
					if (!cur->rightChild)
						add = cur->rightChild = new Node(data, cur);

					cur = cur->rightChild;
					continue;
				}
			}
		}
	}
	
	Node* findNode(int data) {

		Node* cur = root;

		while (cur && cur->data != data) {
			if (cur->data >= data)
				cur = cur->leftChild;
			else
				cur = cur->rightChild;
		}

		return cur;
	}

	void del(int data) {
		Node* del = findNode(data);

		if (!del) return;

		if (!del->leftChild && !del->rightChild) {
			if (del->parent) {
				if (del->parent->leftChild == del) del->parent->leftChild = nullptr;
				else if (del->parent->rightChild == del) del->parent->rightChild = nullptr;
			}

		} else if (!del->leftChild || !del->rightChild) {
			if (del->parent) {
				if (del->leftChild)
					del->parent->leftChild = del->leftChild;
				else
					del->parent->rightChild = del->rightChild;
			}

		} else {

			bool isLeft = del->parent->leftChild == del;

			Node* move = isLeft ? del->rightChild : del->leftChild;

			while ((isLeft ? move->leftChild : move->rightChild) != nullptr)
				move = isLeft ? move->leftChild : move->rightChild;

			if (isLeft ? move->rightChild : move->leftChild) {
				if (isLeft)
					move->parent->rightChild = move->leftChild;
				else
					move->parent->leftChild = move->rightChild;
			} else {
				if (isLeft)
					move->parent->leftChild = nullptr;
				else
					move->parent->rightChild = nullptr;
			}
			
			if (isLeft)
				del->parent->leftChild = move;
			else
				del->parent->rightChild = move;
			
			move->parent = del->parent;

			if (del->leftChild) del->leftChild->parent = move;
			if (del->rightChild) del->rightChild->parent = move;

			move->leftChild = del->leftChild;
			move->rightChild = del->rightChild;
		}

		del->leftChild = nullptr;
		del->rightChild = nullptr;
		delete del;
	}

	void printSort(Node* node = nullptr) {
		if (!node) node = root;
		if (!node) return;

		if (node->leftChild) printSort(node->leftChild);
		std::cout << node->data << " - ";
		if (node->rightChild) printSort(node->rightChild);
	}
};

int main() {

	BinaryTree bt;

	bt.add(5);
	bt.add(4);
	bt.add(20);
	bt.add(-17);
	bt.add(13);
	bt.add(43);
	bt.add(11);
	bt.add(18);
	bt.add(15);
	bt.add(19);

	bt.printSort();

	return 0;
}
