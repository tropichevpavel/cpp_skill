
enum Color { Black, Red };

struct Node {
	int key;
	Color color = Red;
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	Node* root = nullptr;

	Node(int key) : key(key) {}

	void insert(int key) {
		insert(root, new Node(key));
	}

	void insert(Node* root, Node* node) {
		Node* curNode = root;
		Node* parNode = nullptr;

		while (curNode) {
			parNode = curNode;
			curNode = curNode->key > node->key ? curNode->left : curNode->right;
		}

		node->parent = parNode;

		if (parNode) {
			if (parNode->key > node->key)
				parNode->left = node;
			else
				parNode->right = node;
		} else
			root = node;

		colorFix(root, node);
	}

	void colorFix(Node* root, Node* node) {
		Node* parent = node->parent;

		while (node != root && parent->color == Red) {
			Node* grand = parent->parent;

			if (grand->left == parent) {
				Node* uncle = grand->right;

				if (uncle && uncle->color == Red) {
					parent->color = Black;
					uncle->color = Black;
					grand->color = Red;

					node = grand;
					parent = node->parent;

				} else {
					if (parent->right == node) {
						leftRotate(root, node);
						swap(node, parent);
					}
					rightRotate(root, grand);
					grand->color = Red;
					parent->color = Black;
					break;
				}

			} else {
				Node* uncle = grand->left;

				if (uncle && uncle->color == Red) {
					parent->color = Black;
					uncle->color = Black;
					grand->color = Red;

					node = grand;
					parent = node->parent;
				
				} else {
					if (parent->left == node) {
						rightRotate(root, parent);
						swap(parent, node);
					}
					leftRotate(root, grand);
					grand->color = Red;
					parent->color = Black;
					break;
				}
			}
		}
		root->color = Black;
	}

	void colorFix(Node* root, Node* node, Node* parent) {
		Node* tmp;

		while (!node || (node->color == Black) && node != root) {
			if (parent->left == node) {
				tmp = parent->right;

				if (tmp->color == Red) {
					tmp->color = Black;
					parent->color = Red;
					leftRotate(root, parent);
					tmp = parent->right;

				} else {
					if (!tmp->right || tmp->right->color == Black) {
						tmp->left->color = Black;
						tmp->color = Red;
						rightRotate(root, tmp);
						tmp = parent->right;
					}

					tmp->color = parent->color;
					parent->color = Black;
					tmp->right->color = Black;
					leftRotate(root, parent);
					node = root;
					break;
				}

			} else {
				tmp = parent->left;

				if (tmp->color == Red) {
					tmp->color = Black;
					parent->color = Red;
					rightRotate(root, parent);
					tmp = parent->left;

				} 
				
				if ((!tmp->left || tmp->left->color == Black) && (!tmp->right || tmp->right->color == Black)) {
					tmp->color = Red;
					node = parent;
					parent = node->parent;
				
				} else {
					if (!tmp->left || tmp->left->color == Black) {
						tmp->right->color = Black;
						tmp->color = Red;
						leftRotate(root, tmp);
						tmp = parent->left;
					}

					tmp->color = parent->color;
					parent->color = Black;
					tmp->left->color = Black;
					rightRotate(root, parent);
					node = root;
					break;					
				}
			}
		}

		if (node) node->color = Black;
	}

	void leftRotate(Node* root, Node* node) {

	}

	void rightRotate(Node* root, Node* node) {
		
	}

	void swap(Node* root, Node* node) {

	}

	auto search(int key) -> Node* {
		return search(root, key);
	}

	auto search(Node* node, int key) const -> Node* {
		if (!node || node->key) return node;
		else {
			if (key > node->key)
				return search(node->right, key);
			else
				return search(node->left, key);
		}
	}

	void remove(int key) {
		Node* del = search(root, key);
		if (del)
			remove(root, del);
	}

	void remove(Node*& root, Node* node) {
		Node* child;
		Node* parent;
		Color color;

		if (node->left && node->right) {
			Node* replace = node->right;

			while (!(replace = replace->left)) {}

			if (node->parent) {
				if (node->parent->left == node)
					node->parent->left = replace;
				else
					node->parent->right = replace;
			} else
				root = replace;
			
			child = replace->right;
			parent = replace->parent;
			color = replace->color;

			if (parent == node) parent = replace;
			else {
				if (child) child->parent = parent;
				parent->left = child;

				replace->right = node->left;
				node->right->parent = replace;
			}

			replace->parent = node->parent;
			replace->color = node->color;
			replace->left = node->left;
			node->left->parent = replace;

			if (color == Black) colorFix(root, child, parent);
			delete node;
			return;
		}

		child = node->left ? node->left : node->right;
		parent = node->parent;
		color = node->color;

		if (child) child->parent = parent;

		if (parent) {
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		
		} else root = child;

		if (color == Black && root) colorFix(root, child, parent);
		delete node;
	}
};

int main() {
	return 0;
}
